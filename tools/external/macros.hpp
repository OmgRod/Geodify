#include <regex>
#ifndef SOURCE_DIRECTORY
#define SOURCE_DIRECTORY "src"
#endif
#ifndef PREVIEWS_DIRECTORY
#define PREVIEWS_DIRECTORY "previews"
#endif
#ifndef SAPPHIRE_DIRECTORY
#define SAPPHIRE_DIRECTORY "previews/sapphire"
#endif
const std::regex commentPattern(R"REGEX(//\[\[omgrod\.geodify/TAG\]\]\s*([^\s:]+))REGEX");
const std::regex macroPattern(R"REGEX(ADD_TAG\s*\(\s*"([^"]*)"(?:\s*,\s*"([^"]*)")?\s*\))REGEX");
