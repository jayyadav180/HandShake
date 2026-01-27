#pragma once

#include <string>
#include <vector>
#include <optional>

#include "../Model/Note.h"
#include "../Model/NoteMetadata.h"

class NoteRepository
{
public:
    virtual ~NoteRepository() = default;

    // creation is metadata-only
    virtual bool create(const NoteMetaData& meta) = 0;

    // saving persists content + metadata
    virtual bool save(const Note& note) = 0;

    // load full note
    virtual std::optional<Note> load(const std::string& noteid) = 0;

    // list for home screen
    virtual std::vector<NoteMetaData> loadAllMeta() = 0;

    virtual bool remove(const std::string& noteid) = 0;
};
