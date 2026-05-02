//
// Created by AlexanderSYN on 04.04.2026.
//

#ifndef FILERMV_H
#define FILERMV_H

#include "include_fs.h"

namespace FILERMV {
    void remove(const fs::path& path);
    void remove_multiple(const fs::path& path,
        const std::vector<std::string>& args);

    void remove_without_param_and_log(const fs::path& path);
}

#endif //FILERMV_H
