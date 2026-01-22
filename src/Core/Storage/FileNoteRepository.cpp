#include <filesystem>
#include "../Storage/FileNoteRepository.h"
#include <fstream>

namespace fs = std::filesystem;

FileNoteRepository::FileNoteRepository(const fs::path& basepath): m_basepath(basepath)
{

}

bool FileNoteRepository::ensuremasterfolderexists()
{
    try 
    {
        fs::create_directories(m_basepath);
        return true;
    }
    catch (const fs::filesystem_error&) 
    {
        return false;
    }
}

bool FileNoteRepository::create(const Note& note)
{
    
}