#pragma once

#include <string>
#include <cstdint>

enum class Note_Representation 
{
    simpleText,   // Default format
    markdown     // (.md)
}; 

enum class Note_State 
{
    Unnamed,
    Created,
    Editable,
    readonly,
    Dirty,
    Saved,
    Syncing
};

/*
 * Core domain entity: Note
 */
struct Note 
{
    // Stable identity (never changes)
    std::string id;

    // User-defined name/title (can change)
    std::string title;

    //for folder
    std::string folder;

    // The actual text content
    std::string content;

    // How the content should be interpreted
    Note_Representation representation = Note_Representation::simpleText;

    // Lifecycle state (controlled by app logic)
    Note_State state = Note_State::Unnamed;

    // Timestamps (epoch milliseconds or seconds)
    std::uint64_t createdAt = 0;
    std::uint64_t lastModifiedAt = 0;
    std::uint64_t lastSyncedAt = 0;
};
