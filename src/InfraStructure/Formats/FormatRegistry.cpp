#include "FormatRegistry.h"
#include "TxtFormat.h"

FormatRegistry& FormatRegistry::instance()
{
    static FormatRegistry registry;
    return registry;
}

FormatRegistry::FormatRegistry()
{
    // Register default formats here
    m_formats["txt"] = std::make_unique<TxtFormat>();
}

const NoteFormat* FormatRegistry::getFormat(const std::string& id) const
{
    auto it = m_formats.find(id);
    if (it != m_formats.end()) {
        return it->second.get();
    }
    return nullptr;
}
