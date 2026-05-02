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
    fs::path current_dir = helper::resolve_existing_path(path,
        dir);

    try {

        if (fs::create_directory(current_dir)) {
            std::println("[SYSTEM] Directory [{}] created successfully!", current_dir.string());
        }
        else
            std::println("[SYSTEM] Directory already exists or could not be created at {}!", current_dir.string());

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


