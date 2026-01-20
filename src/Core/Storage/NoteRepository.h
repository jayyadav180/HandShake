#pragma once
#include "../Model/Note.h"

#include <string>
#include <vector>
#include <optional>

class NoteRepository
{
public:
virtual ~NoteRepository() = default;
virtual bool create(const Note& note)=0;
virtual bool save(const Note& note)=0;
virtual std::optional<Note> load(const std::string& noteid)=0;
virtual std::vector<Note> loadAll()=0;
virtual bool remove(const std::string& noteid)=0;
};