//
// Created by AlexanderSYN on 13.04.2026.
//

#ifndef SPACE_H
#define SPACE_H

#include "include_fs.h"

namespace space {
    inline constexpr double KiB = 1024.0;
    inline constexpr double MiB = KiB * 1024.0;
    inline constexpr double GiB = MiB * 1024.0;
    inline constexpr double TiB = GiB * 1024.0;

    std::string free_disk(const fs::path& path);
    std::string available_in_disk(const fs::path& path);
    std::string occupied_dir(const fs::path& path);
    std::string total_capacity(const fs::path& path);
    std::string format_bytes(uintmax_t size);
}

#endif //SPACE_H
