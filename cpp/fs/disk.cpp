//
// Created by AlexanderSYN on 13.04.2026.
//
#include "../../header/fs/disk.h"
#include "../../header/fs/space.h"

///
/// output free disk space
/// @param path_f path for get free disk space
/// or just disk
void disk::free_in_disk(const fs::path& path_f) {
    try {
        std::println("Disk space info for: {}\n"
                     "Total capacity: {}\n"
                     "Available space: {}\n",
                     path_f.root_name().string(),
                     space::total_capacity(path_f),
                     space::available_in_disk(path_f));

    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR_FREE_DISK_SPACE] {}", e.what());
    }
}

///
/// occuiped space in folders
/// @param path_f
void disk::ocuppied_in_folders(const fs::path& path_f) {
    try {
        std::println("Path: {}\n"
                     "Occupied space: {}",
                     path_f.string(),
                     space::occupied_dir(path_f));
    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR_FREE_DISK_SPACE] {}", e.what());
    }
}
