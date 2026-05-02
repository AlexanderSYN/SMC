//
// Created by AlexanderSYN on 30.03.2026.
//

#include "../../header/fs/FILEC.hpp"

#include "../../header/helper/helper.h"

/// create file in path
/// @param path the path to save it to
/// @param file file name and path
void FILEC::create_file(fs::path path, std::string file) {
    std::string file_path = path.string() + "\\" + file;
    std::ofstream file_stream(file_path);

    if (file_stream.is_open()) {
        std::println("[SYSTEM] File created successfully!");
        file_stream.close();
        return;
    }

    std::println(std::cerr, "[SYSTEM][ERROR] File could not be created at {}!", file_path);

    helper::clear_input_buffer();
}

/// command for create files
/// @param path the path to save it to
/// @param args how much to create files
void FILEC::command_touch(const fs::path &path,
                           std::vector<std::string> args) {

    if (args.size() <= 2)
        create_file(path, args[1]);
    else
        for (auto f : args | std::ranges::views::drop(1))
            create_file(path, f);
}



