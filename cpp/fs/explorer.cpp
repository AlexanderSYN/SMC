//
// Created by AlexanderSYN on 06.04.2026.
//

#include "../../header/fs/EXPLORER.h"

///
/// open file in explorer
///
/// example
/// D:\ >> explorer or exp
/// @param path path folder or file to need to select in explorer
void explr::reveal_in_explorer(const fs::path& path) {
    try {
        if (!fs::exists(path)) {
            std::println("Path does not exist: {}", path.string());
            return;
        }

        std::string command;

#ifdef _WIN32
        command = "explorer /select,\"" + path.string() + "\"";
#elif __APPLE__
        if (fs::is_directory(path)) {
            command = "open \"" + path.string() "\"";
        } else {
            command = "open -R \"" + path.string() + "\"";
        }
#elseif __linux__
        if (fs::is_directory(path)) {
            command = "xdg-open \"" + path.string() + "\"";
        } else {
            command = "xdg-open \"" + path.parent_path().string() + "\"";
        }
#else
        std::cout << "[ERROR] Unsupported OS" << std::endl;
        return;
#endif

        int result = std::system(command.c_str());
        bool success = (result == 1);

        if (success)
            std::cout << "[SUCCESS OPEN]" << std::endl;
        else
            std::cout << "[FAILED OPEN]" << std::endl;

    } catch (const std::exception& e) {
        std::println("[CRITICAL_ERROR_SHOW_IN_EXPLORER] {}", e.what());
    }
}
///
/// open file in explorer when found file / folder
///
/// @param paths_founded_ff path folder or file to need to select in explorer
/// @param choice what file / folder need to select
void explr::reveal_in_explorer(
    const std::vector<std::string>& paths_founded_ff, int choice) {

    try {
        if (!fs::exists(paths_founded_ff.at(choice))) {
            std::println("Path does not exist: {}",
                paths_founded_ff.at(choice));
            return;
        }

        std::string command;

#ifdef _WIN32
        command = "explorer /select,\"" + paths_founded_ff.at(choice) + "\"";
#elif __APPLE__
        if (fs::is_directory(path)) {
            command = "open \"" + path.string() "\"";
        } else {
            command = "open -R \"" + path.string() + "\"";
        }
#elseif __linux__
        if (fs::is_directory(path)) {
            command = "xdg-open \"" + path.string() + "\"";
        } else {
            command = "xdg-open \"" + path.parent_path().string() + "\"";
        }
#else
        std::cout << "[ERROR] Unsupported OS" << std::endl;
        return;
#endif

        int result = std::system(command.c_str());
        bool success = (result == 1);

        if (success)
            std::cout << "[SUCCESS OPEN]" << std::endl;
        else
            std::cout << "[FAILED OPEN]" << std::endl;

    } catch (const std::exception& e) {
        std::println("[CRITICAL_ERROR_SHOW_IN_EXPLORER] {}", e.what());
    }
}

///
/// run file use a system application
/// @param path_f path file
void explr::run_file(const fs::path& path_f) {
    try {
        #if defined(_WIN32) //Windows
                std::string command = "start \"\" \"" + path_f.string() + "\"";
        #elif defined(__APPLE__) // MacOs
                std::string command = "open \"" + path_f.string() + "\"";
        #elif defined(__linux__) //Linux
                std::string command = "xdg-open \"" + path_f.string() + "\"";
        #else
                std::cerr << "Unsupported OS" << std::endl;
                return;
        #endif

        bool res = system(command.c_str());
        if (!res)
            std::println("[SUCCESS RUN]");
        else
            std::println(std::cerr, "[ERROR RUN]");

    } catch (const std::exception& e) {
        std::println(std::cerr, "[CRITICAL_ERROR_RUN_FILE] {}",
            e.what());
    }
}

