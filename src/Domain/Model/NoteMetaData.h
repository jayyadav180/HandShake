#pragma once
#include <string>
#include <cstdint>

struct NoteMetaData 
{
 std::string id;
 std::string title;
 std::string folder;
 std::string formatId;
 std::uint64_t createdAt = 0;
 std::uint64_t lastModifiedAt = 0;
 std::uint64_t lastSyncedAt = 0;
};
