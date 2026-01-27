#pragma once

#include <string>
#include "../../domain/model/Note.h"

class NoteFormat {
public:
    virtual ~NoteFormat() = default;

    // File extension including dot (".txt", ".md")
    virtual std::string extension() const = 0;

    // Identifier used in metadata ("txt", "md")
    virtual std::string id() const = 0;
};
