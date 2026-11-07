// Purpose: Shared string helpers (trim, case-insensitive compare, comment/blank line check,
// field split) used by the file loaders. Header-only.
// Author: Bradey Jacobs, Member B
#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <string>
#include <vector>

namespace strutil {

//Remove spaces, tabs, \r, \n, etc. from both ends.
inline std::string trim(const std::string& s) {
    const char* ws = " \t\r\n\f\v";
    std::size_t b = s.find_first_not_of(ws);
    if (b == std::string::npos) return "";
    std::size_t e = s.find_last_not_of(ws);
    return s.substr(b, e - b + 1);
}

//ASCII-only lowercase copy.
inline std::string toLower(std::string s) {
    for (char& c : s)
        if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
    return s;
}

//Case-insensitive equality.
inline bool equalsIgnoreCase(const std::string& a, const std::string& b) {
    return a.size() == b.size() && toLower(a) == toLower(b);
}

//True for blank lines and lines whose first non-whitespace char is '#'.
inline bool isSkippableLine(const std::string& line) {
    std::string t = trim(line);
    return t.empty() || t[0] == '#';
}

//Split on delim, keeping empty fields, trimming each field.
inline std::vector<std::string> splitFields(const std::string& line, char delim = '|') {
    std::vector<std::string> out;
    std::string cur;
    for (char c : line) {
        if (c == delim) { out.push_back(trim(cur)); cur.clear(); }
        else cur += c;
    }
    out.push_back(trim(cur));
    return out;
}

}

#endif
