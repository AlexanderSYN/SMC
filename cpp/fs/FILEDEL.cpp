//
// Created by AlexanderSYN on 04.04.2026.
//

#include "../../header/fs/FILEDEL.h"

void FILEDEL::del(const fs::path &path) {
    try {
        char choice;

        std::print("[SYSTEM] Are you sure <y/n>? ");
        std::cin >> choice;

        if (std::tolower(choice) == 'y') {

            if (is_regular_file(path)) {
                if (fs::remove(path)) {
                    std::println("[SYSTEM] File [{}] "
                                 "deleted successfully!",
                                 path.filename().string());
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

                }
                else {
                    std::println(std::cerr, "[ERR] deleting"
                                            " file [{}]!",
                                            path.filename().string());
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
                }
            }
            else {
                if (fs::remove_all(path)) {
                    std::println("[SYSTEM] Folder [{}] "
                                 "deleted successfully!",
                                 path.filename().string());
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

                }
                else {
                    std::println(std::cerr, "[ERR] deleting "
                                            "folder [{}]!",
                                            path.filename().string());
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

                }
            }

        } else {
            std::println("[SYSTEM] operation canceled!");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
        }


    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR_DELETE] {}",
            e.what());
    }
}
