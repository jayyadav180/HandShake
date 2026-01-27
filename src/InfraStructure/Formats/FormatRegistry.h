#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "NoteFormat.h"


class FormatRegistry {
public:
    static FormatRegistry& instance();

    // Returns nullptr if format is not registered
    const NoteFormat* getFormat(const std::string& id) const;

private:
    FormatRegistry(); // private constructor

    std::unordered_map<std::string, std::unique_ptr<NoteFormat>> m_formats;
};
