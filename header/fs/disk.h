//
// Created by AlexanderSYN on 13.04.2026.
//

#ifndef DISK_H
#define DISK_H

#include "include_fs.h"

namespace disk {
    void free_in_disk(const fs::path& path_f);
    void ocuppied_in_folders(const fs::path& path_f);
}

#endif //DISK_H
