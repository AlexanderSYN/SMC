//
// Created by AlexanderSYN on 06.04.2026.
//

#ifndef IO_TEXT_H
#define IO_TEXT_H

#include "include_io_text.h"

namespace text {
    void read(const fs::path& path_f);
    void write(const fs::path& path_f, const std::string& text);
    void rewrite(const fs::path& path_f, const std::string& text);
    void write_many_lines(const fs::path& path_f);
}

#endif //IO_TEXT_H
