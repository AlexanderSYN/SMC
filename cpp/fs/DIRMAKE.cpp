//
// Created by AlexanderSYN on 30.03.2026.
//

//================================
// FILEDC - File Directory Create
//================================

#include "../../header/fs/DIRMAKE.h"

#include <ranges>

#include "../../header/helper/helper.h"

///
/// @param path the path to save it to
/// @param file file name and path
void DIRMAKE::create_dir(fs::path path, std::string dir) {
    fs::path dir_path = helper::resolve_existing_path(path,
        dir);

    try {

        if (fs::exists(dir_path)) {
            char choice;

            std::println("[WARNING] folder [{}] already exists!", dir_path.string());
            std::print("are you want to overwrite? <y/n>: ");

            std::cin >> choice;
            if (std::tolower(choice) == 'n') {
                std::println("[SYSTEM] operation canceled");
                helper::clear_input_buffer();
                return;
            }
        }

        if (fs::create_directory(dir_path)) {
            std::println("[SYSTEM] Directory [{}] created successfully!", dir_path.string());
        }

        helper::clear_input_buffer();
    } catch (const std::exception& e) {
        std::println(std::cerr, "[CRITICAL_ERROR_CREATE_FOLDER] {}", e.what());
    }
}

void DIRMAKE::command_mkdir(const fs::path &path,
    std::vector<std::string> args) {

    if (args.size() <= 2)
        create_dir(path, args[1]);
    else
        for (auto f : args | std::ranges::views::drop(1))
            create_dir(path, f);
}


