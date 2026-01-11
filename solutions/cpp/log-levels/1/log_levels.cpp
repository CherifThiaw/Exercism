// log_line_toolkit.cpp
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <cctype>

namespace log_line {

// ---------- helpers ----------
static std::string trim(std::string s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) start++;
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) end--;
    return s.substr(start, end - start);
}

static std::string to_lower(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

// ---------- "real project" data model ----------
struct LogEntry {
    std::string level;                 // normalized, ex: "error"
    std::string message;               // trimmed
    std::optional<std::string> time;   // optional timestamp if present before '['
};

// Supports formats like:
// "[ERROR]: Disk full"
// "2026-01-10 12:30:05 [WARN]: Low memory"
std::optional<LogEntry> parse(const std::string& line) {
    const size_t open = line.find('[');
    const size_t close = (open == std::string::npos) ? std::string::npos : line.find(']', open + 1);
    if (open == std::string::npos || close == std::string::npos || close <= open + 1) return std::nullopt;

    // Expect ":" after bracket (allow spaces like "]: " or "]:")
    size_t colon = line.find(':', close + 1);
    if (colon == std::string::npos) return std::nullopt;

    // Extract raw pieces
    std::string rawLevel = line.substr(open + 1, close - (open + 1));
    std::string rawMsg = (colon + 1 < line.size()) ? line.substr(colon + 1) : "";

    // Optional timestamp: anything before '[' (trimmed), only if non-empty
    std::string prefix = trim(line.substr(0, open));
    std::optional<std::string> t = prefix.empty() ? std::nullopt : std::optional<std::string>(prefix);

    LogEntry e;
    e.level = to_lower(trim(rawLevel));
    e.message = trim(rawMsg);
    e.time = t;
    return e;
}

bool is_valid(const std::string& line) {
    return parse(line).has_value();
}

// Severity ranking (higher = more severe)
int severity(const std::string& level) {
    const std::string lv = to_lower(trim(level));
    if (lv == "fatal")   return 50;
    if (lv == "error")   return 40;
    if (lv == "warn" || lv == "warning") return 30;
    if (lv == "info")    return 20;
    if (lv == "debug")   return 10;
    return 0; // unknown
}

// ---------- Original exercise API (now safer) ----------
std::string message(std::string line) {
    auto e = parse(line);
    if (!e) return "";               // malformed -> empty message
    return e->message;
}

std::string log_level(std::string line) {
    auto e = parse(line);
    if (!e) return "";               // malformed -> empty level
    return e->level;                 // normalized lower-case
}

std::string reformat(std::string line) {
    auto e = parse(line);
    if (!e) return "INVALID (unknown)";

    // Feature: include time if present
    if (e->time) {
        return *e->time + " | " + e->message + " (" + e->level + ")";
    }
    return e->message + " (" + e->level + ")";
}

// ---------- Extra utility: filter by minimum severity ----------
std::vector<std::string> filter_min_severity(const std::vector<std::string>& lines, int minSeverity) {
    std::vector<std::string> out;
    for (const auto& line : lines) {
        auto e = parse(line);
        if (!e) continue;
        if (severity(e->level) >= minSeverity) out.push_back(line);
    }
    return out;
}

} // namespace log_line

// ---------- Tiny CLI demo (makes it feel like a real project) ----------
// Run: type/paste log lines, Ctrl+D (Mac/Linux) or Ctrl+Z then Enter (Windows)
int main() {
    using namespace log_line;

    std::cout << "LogLine Toolkit\n";
    std::cout << "Paste log lines. Examples:\n";
    std::cout << "  [ERROR]: Disk full\n";
    std::cout << "  2026-01-10 12:30:05 [WARN]: Low memory\n";
    std::cout << "End input with Ctrl+D (Mac/Linux) or Ctrl+Z then Enter (Windows).\n\n";

    std::string line;
    std::vector<std::string> all;

    while (std::getline(std::cin, line)) {
        all.push_back(line);
    }

    std::cout << "\n--- Reformatted ---\n";
    for (const auto& l : all) {
        std::cout << reformat(l) << "\n";
    }

    std::cout << "\n--- Only WARN+ (severity >= 30) ---\n";
    auto warnPlus = filter_min_severity(all, 30);
    for (const auto& l : warnPlus) {
        std::cout << reformat(l) << "\n";
    }

    return 0;
}













/*#include <string>

namespace log_line {
std::string message(std::string line) {
    // return the message
    return line.substr(line.find("]: ") + 3);
}

std::string log_level(std::string line) {
    // return the log level
        return line.substr(1, line.find(']') - 1);

}

std::string reformat(std::string line) {
    // return the reformatted message
    return message(line) + " (" + log_level(line) + ")";
}
}  // namespace log_line 
*/
