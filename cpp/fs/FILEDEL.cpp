//
// Created by AlexanderSYN on 04.04.2026.
//

#include "../../header/fs/FILEDEL.h"

void FILEDEL::del(const fs::path &path) {
    try {
        if (is_regular_file(path))
            if (fs::remove(path))
                std::println("[SYSTEM] File [{}] "
                             "deleted successfully!", path.filename().string());
            else
                std::println(std::cerr, "[ERR] deleting file [{}]!", path.filename().string());

            else
                if (fs::remove_all(path))
                    std::println("[SYSTEM] Folder [{}] deleted successfully!", path.filename().string());

                else
                    std::println(std::cerr, "[ERR] deleting folder [{}]!", path.filename().string());

    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR_DELETE] {}", e.what());
    }
}
