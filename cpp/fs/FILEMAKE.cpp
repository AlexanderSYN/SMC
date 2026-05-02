//
// Created by AlexanderSYN on 30.03.2026.
//

#include "../../header/fs/FILEMAKE.hpp"

#include "../../header/helper/helper.h"


void FILEC::create_file(fs::path path, std::string file) {
    fs::path file_path = helper::resolve_existing_path(path,
        file);

    if (fs::exists(file_path)) {
        char choice;

        std::println("[WARNING] file [{}] already exists!", file_path.string());
        std::print("are you want to overwrite? <y/n>: ");

        std::cin >> choice;
        if (std::tolower(choice) == 'n') {
            std::println("[SYSTEM] operation canceled");
            helper::clear_input_buffer();
            return;
        }
    }

    std::ofstream file_stream(file_path);

    if (file_stream.is_open()) {
        std::println("[SYSTEM] File [{}] created successfully!", file_path.string());
        file_stream.close();
        helper::clear_input_buffer();

        return;
    }

    std::println(std::cerr, "[SYSTEM][ERROR] File could not be created at {}!", file_path.string());

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



