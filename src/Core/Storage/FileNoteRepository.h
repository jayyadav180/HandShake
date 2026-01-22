#pragma once

#include "../Storage/NoteRepository.h"

#include <filesystem>
#include <optional>
#include <vector>
#include <string>
class FileNoteRepository : public NoteRepository
{
    public:
explicit FileNoteRepository(const std::filesystem::path& basepath);
bool create(const Note& note) override;
bool save(const Note& note) override;
std::optional<Note> load(const std::string& noteid) override;
std::vector<Note> loadAll() override;
bool remove(const std::string& noteid) override;
private:
bool ensuremasterfolderexists();
private:
std::filesystem::path m_basepath;
};