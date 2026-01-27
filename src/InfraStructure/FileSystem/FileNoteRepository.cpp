#include <filesystem>
#include "../FileSystem/FileNoteRepository.h"
#include <fstream>
#include "../model/NoteMetaData.h"
#include "../Formats/FormatRegistry.h"

namespace fs = std::filesystem;
FileNoteRepository::FileNoteRepository(const fs::path& basepath): m_basepath(basepath) {}

//---------------------------------------------------------------------------------------

//namespace fs = std::filesystem;
bool FileNoteRepository::ensureMasterFolderExists()
{
    try 
    {
        fs::create_directories(m_basepath);
        return true;
    }
    catch (const fs::filesystem_error&) 
    {         return false;           }
}

bool FileNoteRepository::create(const NoteMetaData& meta)
{
 if(!ensureMasterFolderExists()) {   return false;     }

 const NoteFormat* format = FormatRegistry::instance().getFormat(meta.formatId);
 if (!format) {  return false; }

 namespace fs = std::filesystem;
 try
 {
   fs::path notepath = m_basepath / (meta.id + format->extension());
   fs::path metapath = m_basepath / (meta.id + ".meta.json");

   if(fs::exists(notepath) || fs::exists(metapath)) {  return false;  }

   std::ofstream metafile(metapath);
   if(!metafile.is_open())
   {    return false;    }
        metafile <<  "{\n";
        metafile << "  \"id\": \"" << meta.id << "\",\n";
        metafile << "  \"title\": \"" << meta.title << "\",\n";
        metafile << "  \"folder\": \"" << meta.folder << "\",\n";
        metafile << "  \"formatId\": \"" << meta.formatId << "\",\n";
        metafile << "  \"createdAt\": " << meta.createdAt << ",\n";
        metafile << "  \"lastModifiedAt\": " << meta.lastModifiedAt << ",\n";
        metafile << "  \"lastSyncedAt\": " << meta.lastSyncedAt << "\n";
        metafile << "}\n";

        metafile.close();

   std::ofstream contentfile(notepath);
   if(!contentfile.is_open())
   {      return false;     }
   contentfile.close();
   return true;
 }

 catch (const fs::filesystem_error&)
 { return false; }
}

//---------------------------------------------------------------------------------------

std::vector<NoteMetaData> FileNoteRepository::loadAllMeta()
{

}
