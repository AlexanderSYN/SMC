//
// Created by AlexanderSYN on 28.03.2026.
//

#ifndef HELPER_H
#define HELPER_H

#include "include_helper.h"

namespace helper {
    void replace_chars(std::string &text,
                       const std::string &old_chars,
                       const std::string &new_chars);

    fs::path connect_path_with_spaces(
                    const std::vector<std::string>& args,
                    int drop = 1);
    std::string connect_path_with_spaces_str(
                    const std::vector<std::string>& args,
                    int drop = 1);

    fs::path connect_path(const fs::path &first_path,
                    const fs::path &second_path);
}

#endif //HELPER_H
