//
// Created by AlexanderSYN on 26.03.2026.
//

// FILEO - File Open

#include "../../header/fs/FILEO.h"

#include "../../header/helper/helper.h"
#include "../../header/helper/path_ff.h"
#include "../../header/helper/Hfs/HFILEF.h"

//======================
// command -> cd (path)
//
// example:
// \ >> cd D:\test
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
    if (path_from_user[0] == '.' && path_from_user[1] == '.') {
        fs::path current_path = path;
        current_path /= path_from_user;
        current_path = current_path.lexically_normal();
        path_ff::set_path(current_path.string());
        return;
    }

    if (!fs::exists(path_from_user)) {
        // check if you have written a folder or file that is
        // in the current directory, then just go to it
        if (fs::exists(tmp_path)) {
            path_ff::set_path(tmp_path);
            return;
        }

        std::println(std::cerr, "[ERROR_CD] Folder or File not found!");
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
            std::cerr << "[ERROR_READ_FILE] couldn't open the file!" << std::endl;
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

#ifdef _WIN32
    try {
        std::string command_win = "dir /a \"" + path.string() + "\"";
        system(command_win.c_str());
    } catch (const std::exception& e) {
        std::println("[CRITICAL_ERROR_DIR] {}", e.what());
    }
#endif
}

//================================================
// command open -> output all files from folder
//
// example
// D:\>> open
//================================================
void FILEO::command_open(const fs::path &path) {
    try {
        int count_files = 0, count_folder = 0;
        if (!fs::exists(path)) {
            std::println(std::cerr, "[ERROR_OPEN] Folder doesn't exists!");
            return;
        }
        std::println("Disk: {}", path.string().at(0));
        for (const auto& entry: fs::directory_iterator(path)) {
            auto ftime = std::filesystem::last_write_time(entry.path());
            auto sctp = std::chrono::clock_cast<std::chrono::system_clock>(ftime);

            if (!HFILEF::is_system(entry.path()) && fs::is_regular_file(entry.path())) {
                std::println("{:%d.%m.%Y %H:%M} {} {} \t {} {}",  sctp,
                    HFILEF::get_size_file(entry.path()), HFILEF::type(entry),
                    HFILEF::is_hidden(entry),
                    entry.path().filename().string());
                count_files++;
            } else {
                std::println("{:%d.%m.%Y %H:%M} \t {} \t {} {}", sctp,
                    HFILEF::type(entry),
                    HFILEF::is_hidden(entry),
                    entry.path().filename().string());
                count_folder++;
            }

        }

        std::println("\t\t File(s): {}\n \t\t Dir(s): {}", count_files, count_folder);

    } catch (const std::exception& e) {
        std::println(std::cerr, "[CRITICIAL_ERROR_OPEN] {}", e.what());
    }
}

//============================
// command ls -> output
// all files from folder
//
// example:
// D:\ >> ls
//============================
void FILEO::command_list(const fs::path &path_f) {
     try {
         if (!fs::exists(path_f) && fs::is_directory(path_f)) {
             std::println(std::cerr, "[ERR] Folder not found or "
                                     "change path!");
             return;
         }

         for (const auto& entry : fs::directory_iterator(path_f))
             std::cout << entry.path().filename().string() << std::endl;

     } catch (const std::exception& e) {
         std::println(std::cerr, "[CRITICIAL_ERROR_LS] {}", e.what());
     }
}

//==============================
// command ls with parameters
// output all files from folder
//
// example:
// D:\ >> ls --d
//==============================
void FILEO::command_list(const fs::path &path_f, std::string param) {
    try {
        if (!fs::exists(path_f) && std::filesystem::is_directory(path_f)) {
            std::println(std::cerr, "[ERR_LS_PARAMETERS] "
                         "Folder not found or change path!");
        }

        if (param.empty()) {
            std::println("You need to write a parametr!");
            return;
        }

        std::transform(param.begin(), param.end(), param.begin(), ::tolower);
        std::vector<std::string> for_sort_ff; // ff - file folder

        for (const auto& entry : fs::directory_iterator(path_f)) {
            std::string fdname = entry.path().filename().string(); // fdname - file directory name
            std::transform(fdname.begin(), fdname.end(), fdname.begin(), ::tolower);

            // for sort
            if (param == "--sort" || param == "-srt")
                for_sort_ff.push_back(entry.path().filename().string());

            // only files
            if (param == "--f" || param == "--files"
                || param == "--file") {
                if (is_regular_file(entry))
                    std::cout << entry.path().filename().string() << std::endl;

            }
            // only directory
            if (param == "--d" || param == "--directories"
                || param == "--directory") {
                if (entry.is_directory())
                    std::cout << entry.path().filename().string() << std::endl;

            }
            // only directory with words
            else if (param.substr(0, 3) == "-d-") {
                if (entry.is_directory()) {
                    if (!param.substr(3).empty())
                        if (fdname.starts_with(param.substr(3)))
                            std::cout << entry.path().filename().string() << std::endl;


                }
            }
            // only files with words
            else if (param.substr(0, 3) == "-f-") {
                if (is_regular_file(entry)) {
                    if (!param.substr(3).empty())
                        if (fdname.starts_with(param.substr(3)))
                            std::cout << entry.path().filename().string() << std::endl;

                }
            }
            else if (fdname.starts_with(param.substr(1))) {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }

        if (param == "--sort" || param == "-srt") {
            std::ranges::sort(for_sort_ff);
            for (std::string fd : for_sort_ff)
                std::cout << fd << std::endl;
        }

        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::println("[CRITICAL_ERROR_LS_PARAMETERS] {}", e.what());
    }
}

//==========================
// open file in explorer
//
// example
// D:\ >> explorer or exp
//==========================
void FILEO::show_in_explorer(const fs::path& path) {
    try {
        if (!fs::exists(path)) {
            std::println("Path does not exist: {}", path.string());
            return;
        }

        std::string command;

#ifdef _WIN32
        command = "explorer /select,\"" + path.string() + "\"";
#elif __APPLE__
        if (fs::is_directory(path)) {
            command = "open \"" + path.string() "\"";
        } else {
            command = "open -R \"" + path.string() + "\"";
        }
#elseif __linux__
        if (fs::is_directory(path)) {
            command = "xdg-open \"" + path.string() + "\"";
        } else {
            command = "xdg-open \"" + path.parent_path().string() + "\"";
        }
#else
        std::cout << "[ERROR] Unsupported OS" << std::endl;
        return;
#endif

        int result = std::system(command.c_str());
        bool success = (result == 1);

        if (success)
            std::cout << "[SUCCESS OPEN]" << std::endl;
        else
            std::cout << "[FAILED OPEN]" << std::endl;

    } catch (const std::exception& e) {
        std::println("[CRITICAL_ERROR_SHOW_IN_EXPLORER] {}", e.what());
    }
}



