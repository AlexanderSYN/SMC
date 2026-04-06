//
// Created by AlexanderSYN on 06.04.2026.
//

#ifndef IO_TEXT_H
#define IO_TEXT_H

#include "include_io_text.h"
#include "../helper/path_ff.h"



namespace text {
    void read(const fs::path& path_f);
    void write(const fs::path& path_f, const std::string& text);
    void writeln(const fs::path& path_f, const std::string& text);

    void rewrite(const fs::path& path_f, const std::string& text);
    void rewriteln(const fs::path& path_f, const std::string& text);

    void write_many_lines(const fs::path& path_f);
    void rewrite_many_lines(const fs::path &path_f);

    fs::path resolve_file_path_for_echolnrw(
                                const std::vector<std::string>& args,
                                const fs::path& default_path);

    void full_functional_echo( const std::vector<std::string>& args,
                                fs::path default_path);
}

#endif //IO_TEXT_H
