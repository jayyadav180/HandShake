#pragma once

#include "../Application/Ports/NoteRepository.h"

#include <filesystem>
#include <optional>
#include <vector>
#include <string>

class FileNoteRepository : public NoteRepository
{
public:
    explicit FileNoteRepository(const std::filesystem::path& basepath);

    bool create(const NoteMetaData& meta) override;
    bool save(const Note& note) override;
    std::optional<Note> load(const std::string& noteid) override;
    std::vector<NoteMetaData> loadAllMeta() override;
    bool remove(const std::string& noteid) override;

private:
    bool ensureMasterFolderExists();
    std::filesystem::path m_basepath;
};