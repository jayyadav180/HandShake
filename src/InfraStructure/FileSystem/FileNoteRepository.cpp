#include <filesystem>
#include "../FileSystem/FileNoteRepository.h"
#include <fstream>
#include "../model/NoteMetaData.h"
#include "../Formats/FormatRegistry.h"
#include <optional>

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
        metafile <<  "{\n"; // Schema
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
  std::vector<NoteMetaData> result;
  if(!ensureMasterFolderExists()) { return result;}

  try
  {
        for (const auto& entry : std::filesystem::directory_iterator(m_basepath))
        { 
          if(!entry.is_regular_file())
          {        continue;         }

          if(entry.path().filename().string().find("meta.json") == std::string::npos)
          {        continue;         }

          std::ifstream metafile(entry.path());
          if(!metafile.is_open())
          {      continue;      }

          std::string json(
                           (std::istreambuf_iterator<char>(metafile)),
                            std::istreambuf_iterator<char>()
                                                                       );
          metafile.close();

          NoteMetaData meta;

          auto extractstring = [&] (const std::string& key) -> std::string
          {
            auto pos = json.find("\"" + key + "\"");
            if(pos == std::string::npos) { return "";}
                 pos = json.find(":",pos);
                 pos = json.find("\"",pos);
                 auto endpos = json.find("\"",pos + 1);
                 return json.substr(pos + 1, endpos - pos - 1);
          };

          auto extractuint64 = [&] (const std::string& key) -> std::uint64_t
          {
            auto pos = json.find("\""+key+"\"");
            if(pos == std::string::npos) { return 0; }
            pos =json.find(":",pos);
            auto endpos = json.find_first_of(",}",pos);
            return std::stoull(json.substr(pos + 1, endpos - pos - 1));
          };
          
          meta.id = extractstring("id");
          meta.title = extractstring("title");
          meta.folder = extractstring("folder");
          meta.formatId = extractstring("formatID");
          meta.createdAt = extractuint64("createdAt");
          meta.lastModifiedAt = extractuint64("lastModifiedAt");
          meta.lastSyncedAt = extractuint64("lastSyncedAt");

          if(!meta.id.empty())  {    result.push_back(meta);   }
          
        }
  }
 catch ( const fs::filesystem_error&) {}
 return result;
}

//---------------------------------------------------------------------------------------

std::optional<Note> FileNoteRepository::load(const std::string& noteid)
{
  if(!ensureMasterFolderExists())  {      return std::nullopt;        }
  
  namespace fs = std::filesystem;

  try
  {
    fs:: path metapath = m_basepath / (noteid + ".meta.json");
    if(!fs::exists(metapath)) {    return std::nullopt;      }
    
    std::ifstream metafile(metapath);
    if(!metafile.is_open())   {    return std::nullopt;      }
    
    std::string json(
                    (std::istreambuf_iterator<char>(metafile)),
                     std::istreambuf_iterator<char>()
                      );
                      metafile.close();
    
   NoteMetaData meta;
    auto extractstring = [&] (const std::string& key) -> std::string
     {
        auto pos = json .find("\"" + key + "\"");
        if(pos == std::string::npos) {  return "";}
        pos = json.find(":",pos);
        pos = json.find("\"",pos);
        auto endpos = json.find("\"",pos+1);
        return json.substr(pos+1,endpos - pos - 1);
     };
    auto extractuint64 = [&] (const std::string& key) -> std::uint64_t
    {
        auto pos = json.find("\"" + key + "\"");
        if(pos == std::string::npos){ return 0;}
        pos = json.find(":", pos);
        auto endpos = json.find_first_of(",}",pos);
        return std::stoull(json.substr(pos + 1 , endpos - pos - 1));
    };

       meta.id = extractstring("id");
       meta.title = extractstring("title");
       meta.folder = extractstring("folder");
       meta.formatId = extractstring("formatID");
       meta.createdAt = extractuint64("createdAt");   
       meta.lastModifiedAt = extractuint64("lastModifiedAt");
       meta.lastSyncedAt = extractuint64("lastSyncedAt");

       if(meta.id.empty())  {     return std::nullopt;    }

         const NoteFormat* format =
            FormatRegistry::instance().getFormat(meta.formatId);

        if (!format) {
            return std::nullopt;
        }

        fs::path notepath = m_basepath / ( meta.id + format -> extension() );
        if(!fs::exists(notepath)) {      return std::nullopt;       }

        std::ifstream contentfile(notepath);
        if(!contentfile.is_open()){ return std::nullopt; }

        std::string content(
                           (std::istreambuf_iterator<char>(contentfile)),
                            std::istreambuf_iterator<char>()
                                                                        );
                            contentfile.close();
        
        Note note;
        note.id = meta.id;
        note.title = meta.title;
        note.folder = meta.folder;
        note.representation = meta.formatId;
        note.content = content;
        note.createdAt = meta.createdAt;
        note.lastModifiedAt = meta.lastModifiedAt;
        note.lastSyncedAt = meta.lastSyncedAt;  
        
        return note;
      
  }
  catch(const fs::filesystem_error&)
  {    return std::nullopt;        }
  
}