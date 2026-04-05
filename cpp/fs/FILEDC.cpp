//
// Created by AlexanderSYN on 30.03.2026.
//

//================================
// FILEDC - File Directory Create
//================================

#include "../../header/fs/FILEDC.hpp"

#include <ranges>

///
/// @param path the path to save it to
/// @param file file name and path
void FILEDC::create_file(fs::path path, std::string file) {
    std::string file_path = path.string() + "\\" + file;
    std::ofstream file_stream(file_path);

    if (file_stream.is_open()) {
        std::println("[SYSTEM] File created successully!");
        file_stream.close();
        return;
    }

    std::println(std::cerr, "[SYSTEM][ERROR] File could not be created at {}!", file_path);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
}

///
/// @param path the path to save it to
/// @param file file name and path
void FILEDC::create_dir(fs::path path, std::string dir) {
    std::string dir_path = path.string() + "\\" + dir;

    try {
        if (fs::create_directory(dir_path))
            std::println("[SYSTEM] Directory created successfully!");
        else
            println("[SYSTEM] Directory already exists or could not be created at {}!", dir_path);
    } catch (const std::exception& e) {
        std::println(std::cerr, "[CRITICAL_ERROR_CREATE_FOLDER] {}", e.what());
    }

}

void FILEDC::command_touch(const fs::path &path,
    std::vector<std::string> args) {

    if (args.size() <= 2)
        create_file(path, args[1]);
    else
        for (auto f : args | std::ranges::views::drop(1))
            create_file(path, f);
}


void FILEDC::command_mkdir(const fs::path &path,
    std::vector<std::string> args) {

    if (args.size() <= 2)
        create_dir(path, args[1]);
    else
        for (auto f : args | std::ranges::views::drop(1))
            create_dir(path, f);
}


