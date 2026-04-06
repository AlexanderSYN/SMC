//
// Created by AlexanderSYN on 31.03.2026.
//

#ifndef HFILE_H
#define HFILE_H

#include "../include_helper.h"

//
// Helper Files / Folders
//
namespace HFILEF {
    //==========================================================
    // The list of system directories to skip (can be expanded)
    //==========================================================
    const std::vector<std::string> SYSTEM_DIRECTORIES = {
        "System32", "System64", "Windows", "Program Files", "ProgramData",
        "AppData", "Temp", "tmp", "Recycle.Bin", "Recovery",
        "$Recycle.Bin", "System Volume Information", "Windows.old",
        "$RECYCLE.BIN", "DrWeb Quarantine"
    };

    //==========================================================
    // List of system file extensions (can be expanded)
    //==========================================================
    const std::vector<std::string> SYSTEM_EXTENSIONS = {
        ".drv", ".vxd", ".386", ".ocx", ".cpl", ".msc", ".scr",
        ".com", ".tmp", ".inf", ".cat", ".mui"
    };

    std::string type(const fs::path& path_f);
    std::string is_hidden(const fs::path& path_f);
    bool is_system(const fs::path& path);
    std::string get_size_file(const fs::path& path);
}

#endif //HFILE_H
