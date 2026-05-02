//
// Created by AlexanderSYN on 26.03.2026.
//

// FILEO - File Open

#ifndef FILEO_H
#define FILEO_H

#include "include_fs.h"

//=====================
// FILEO - File Open
//=====================

namespace FILEO {
    void set_path_in_cd(std::string path_by_user,
        std::string OPath, fs::path path);

    void command_dir_windows(const fs::path& path);

    void output_for_command_open(const auto& entry, auto sctp,
                            boolean isSystemAndThisFile);
    void command_open(const fs::path& path);

    void command_list(const fs::path& path_f);
    void command_list(const fs::path& path_f, std::string param);


}

#endif //FILEO_H
