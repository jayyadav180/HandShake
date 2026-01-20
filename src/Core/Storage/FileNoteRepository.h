#pragma once

#include "../Storage/NoteRepository.h"

class FileNoteRepository : public NoteRepository
{
bool create(const Note& note) override;
bool save(const Note& note) override;
std::optional<Note> load(const std::string& noteid) override;
std::vector<Note> loadAll() override;
bool remove(const std::string& noteid) override;
};