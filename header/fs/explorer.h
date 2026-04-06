//
// Created by AlexanderSYN on 06.04.2026.
//

#ifndef EXPLORER_H
#define EXPLORER_H

#include "include_fs.h"

namespace explr {
    void show_in_explorer(const fs::path& path);
    void show_in_explorer(const std::vector<std::string>& paths_founded_ff,
                        int choice);
    void run_file(const fs::path& path_f);
}

#endif //EXPLORER_H
