#pragma once

#include <string>
#include <cstdint>

enum class Note_State 
{
    Unnamed,
    Created,
    Editable,
    ReadOnly,
    Dirty,
    Saved,
    Syncing
};

struct Note
{
    std::string id;
    std::string title;
    std::string folder;

    // content is runtime
    std::string content;

    // runtime-only state
    Note_State state = Note_State::Unnamed;

    std::uint64_t createdAt = 0;
    std::uint64_t lastModifiedAt = 0;
    std::uint64_t lastSyncedAt = 0;
};
