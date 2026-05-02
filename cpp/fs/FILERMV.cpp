//
// Created by AlexanderSYN on 04.04.2026.
//

#include "../../header/fs/FILERMV.h"

#include "../../header/helper/helper.h"

void delete_folder(const fs::path &path);
void delete_file(const fs::path &path);

void FILERMV::remove(const fs::path &path) {
    try {
        char choice;

        std::print("[SYSTEM] Are you sure <y/n>? ");
        std::cin >> choice;

        if (std::tolower(choice) == 'y') {
            if (is_regular_file(path))
                delete_file(path);
            else
                delete_folder(path);

        } else {
            std::println("[SYSTEM] operation canceled!");
            helper::clear_input_buffer();
        }

    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR_DELETE] {}",
            e.what());
    }
}

// remove many files / folders
void FILERMV::remove_multiple(const fs::path& path,
        const std::vector<std::string>& args) {

    try {
        for (fs::path item : args | std::ranges::views::drop(1)) {
            fs::path current_path = helper::resolve_existing_path(path,
                item);

            if (fs::is_regular_file(current_path))
                delete_file(current_path);
            else
                delete_folder(current_path);
        }

    }
    catch (const std::exception& e) {
        std::println(std::cerr, "[CRITICAL_ERROR_MANY_ITEMS] {}", e.what());
    }

}

///
/// better use it in func where need only delete without output
/// about operation, e.g. in func move
/// (critical_err outputing)
/// @param path path file or folder to delete
void FILERMV::remove_without_param_and_log(const fs::path& path) {
    try {
        if (is_regular_file(path))
            fs::remove(path);
        else
            fs::remove_all(path);
    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR] {}",
            e.what());

    }

}

void delete_file(const fs::path &path) {
    if (fs::remove(path)) {
        std::println("[SYSTEM] File [{}] deleted successfully!",
                     path.filename().string());

    }
    else {
        std::println(std::cerr, "[ERROR] file [{}] do not deleted !",
                                path.filename().string());

    }
}

void delete_folder(const fs::path &path) {
    if (fs::remove_all(path)) {
        std::println("[SYSTEM] Folder [{}] deleted successfully!",
                     path.filename().string());

    }
    else {
        std::println(std::cerr, "[ERROR] folder [{}] do not deleted !",
                                path.filename().string());

    }
}
