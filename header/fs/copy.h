//
// Created by AlexanderSYN on 29.04.2026.
//

#ifndef COPY_H
#define COPY_H

#include "include_fs.h"

namespace copy {
    void copy_file(const fs::path& from, const fs::path& to,
        const fs::path& path_ff, const std::string& parameter);
    void copy_folder(const fs::path& from, const fs::path& to,
        const fs::path& path_ff, const std::string& parameter);
    void copy_folder_or_file(const fs::path& from, const fs::path& to,
        const fs::path& path_ff, const std::string& parameter);

    void copy_only_for_func_move(const fs::path& from, const fs::path& to,
        const fs::path& path_ff);
}

#endif //COPY_H
