//
// Created by AlexanderSYN on 04.04.2026.
//

#ifndef FILEDEL_H
#define FILEDEL_H

#include "include_fs.h"

namespace FILEDEL {
    void del(const fs::path& path);
    void del(const fs::path& path,
        const std::vector<fs::path>& path_ff);
}

#endif //FILEDEL_H
