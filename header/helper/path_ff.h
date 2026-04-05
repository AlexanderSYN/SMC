//
// Created by AlexanderSYN on 28.03.2026.
//

#ifndef PATH_H
#define PATH_H

#include "include_helper.h"

//=====================================================
// to avoid wasting time setting two path and OPath
// variables with the same value
//=====================================================
class path_ff {
public:
    static std::string get_OPath(); // OPath - output path
    static fs::path get_path();
    static std::string filename();

    static void set_path(const std::string& new_path);

private:
    static fs::path path_f; // path_f - path file / folder
    static std::string OPath; // OPath - Output File

};

#endif //PATH_H
