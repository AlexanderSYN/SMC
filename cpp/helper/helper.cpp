//
// Created by AlexanderSYN on 28.03.2026.
//

#include "../../header/helper/helper.h"

///
/// @param text the text that needs to be changed
/// @param old_chars The value to be replaced.
/// @param new_chars The replacement value.
void helper::replace_chars(std::string &text,
                           const std::string &old_chars,
                           const std::string &new_chars) {

    size_t pos = 0;
    while ((pos = text.find(old_chars, pos)) != std::string::npos)
        text.replace(pos, 2, new_chars);
}

///
/// @param args the vector in main.cpp
/// @param drop the number of items to skip (default = 1)
/// @return path full path
fs::path helper::connect_path_with_spaces(
        const std::vector<std::string>& args,
        int drop) {

    std::string full_path;
    for (auto p : args | std::views::drop(drop))
        full_path += p + " ";

    return fs::path(full_path);
}

std::string helper::connect_path_with_spaces_str(
        const std::vector<std::string>& args,
        int drop) {

    std::string full_path;
    int indx = 1;
    for (const std::string& p : args | std::views::drop(drop)) {
        indx++;
        if (args.size() <= indx) {
            full_path += p;
        }
        else {
            full_path += p + " ";
        }
    }

    return full_path;
}

fs::path helper::connect_path(const fs::path &first_path, const fs::path &second_path) {
    return first_path / second_path;
}

fs::path helper::resolve_existing_path(const fs::path &base_path, const fs::path &input_path) {
    return fs::exists(input_path) ? input_path : base_path / input_path;
}


void helper::clear_input_buffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
}

