//
// Created by AlexanderSYN on 26.03.2026.
//

// FILEO - File Open

#include "../../header/fs/FILEO.h"

#include <chrono>

#include "../../header/helper/helper.h"
#include "../../header/helper/path_ff.h"
#include "../../header/helper/Hfs/HFILEF.h"

//======================
// command -> cd (path)
//======================
void FILEO::set_path_in_cd(std::string path_by_user,
        std::string OPath, fs::path path) {

    std::string tmp_path; // for split path
    std::string path_from_user = path_by_user;

    // if you entered a path earlier, then just add it and before it \
    // otherwise just add the path
    if (!path_by_user.ends_with("\\") && !OPath.ends_with("\\"))
        tmp_path = OPath + "\\" + path_from_user;
    else
        tmp_path = OPath + path_from_user;

    if (path_from_user == "..") {
        if (!OPath.empty() && OPath != "/" && OPath != "\\") {
            path_ff::set_path(path.parent_path().string());
            return;
        }
        return;
    }

    if (!fs::exists(path_from_user)) {
        // check if you have written a folder or file that is
        // in the current directory, then just go to it
        if (fs::exists(tmp_path)) {
            path_ff::set_path(tmp_path);
            return;
        }

        std::cerr << "[ERROR_CD] Folder or File not found!" << std::endl;
        return;
    }

    // changing '/' -> '\'
    std::replace(path_from_user.begin(), path_from_user.end(),
        '/', '\\');
    // changin '\\\' or '\\\\' to '\\'
    helper::replace_chars(path_from_user,
        "\\\\", "\\");

    path_ff::set_path(path_from_user);
}


//=======================================
// read file -> output of information
//             from different text files
//
// example:
// cat (file) or just D:\t.txt>> cat
//=======================================
void FILEO::read_file(const fs::path& path_f) {
    try {
        std::ifstream file(path_f);

        if (file.is_open()) {
            std::string line;
            while (std::getline(file,line)) {
                std::cout << line << std::endl;
            }
            file.close();
        } else {
            std::cerr << "[ERROR_READ_FILE] couldn't open the file" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR_READ_FILE] [CRITICAL] " << e.what() << std::endl;
    }
}

//======================================
// command dir -> command by windows
//
// example
// D:\test>> dir
//======================================
void FILEO::command_dir_windows(const fs::path &path) {
    if (!fs::exists(path)) {
        std::println(std::cerr, "[ERROR_DIR] Folder is not found!");
        return;
    }

    try {
        std::string command_win = "dir /a \"" + path.string() + "\"";
        system(command_win.c_str());
    } catch (const std::exception& e) {
        std::println("[CRITICAL_ERROR_DIR] {}", e.what());
    }
}

//================================================
// command open -> output all files from folder
//
// example
// D:\>> open
//================================================
void FILEO::command_open(const fs::path &path) {
    try {
        if (!fs::exists(path)) {
            std::println(std::cerr, "[ERROR_OPEN] Folder doesn't exists!");
            return;
        }

        for (const auto& entry: fs::directory_iterator(path)) {
            auto ftime = std::filesystem::last_write_time(entry.path());
            auto sctp = std::chrono::clock_cast<std::chrono::system_clock>(ftime);

            if (!HFILEF::is_system(entry.path()) && fs::is_regular_file(entry.path())) {
                std::println("{:%d.%m.%Y %H:%M} {} {} {} {}",  sctp,
                    HFILEF::get_size_file(entry.path()), HFILEF::type(entry),
                    HFILEF::is_hidden(entry),
                    entry.path().filename().string());
            } else {
                std::println("{:%d.%m.%Y %H:%M} {} {} {}", sctp,
                    HFILEF::type(entry),
                    HFILEF::is_hidden(entry),
                    entry.path().filename().string());
            }

        }

    } catch (const std::exception& e) {
        std::println(std::cerr, "[CRITICIAL_ERROR_OPEN] {}", e.what());
    }
}




