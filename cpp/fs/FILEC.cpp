//
// Created by AlexanderSYN on 30.03.2026.
//

#include "../../header/fs/FILEC.hpp"

///
/// @param path the path to save it to
/// @param file file name and path
void FILEC::create_file(fs::path path, std::string file) {
    std::string file_path = path.string() + "\\" + file;
    std::ofstream file_stream(file_path);

    if (file_stream.is_open()) {
        std::println("[SYSTEM] File created successully!");
        file_stream.close();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
        return;
    } else
        std::println(std::cerr, "[SYSTEM][ERROR] File could not be created at {}!", file_path);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

}



