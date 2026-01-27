#pragma once

#include "NoteFormat.h"

class TxtFormat : public NoteFormat {
public:
    std::string extension() const override { return ".txt"; }
    std::string id() const override { return "txt"; }
};
