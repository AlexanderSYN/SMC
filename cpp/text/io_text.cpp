//
// Created by AlexanderSYN on 06.04.2026.
//

#include "../../header/text/io_text.h"

/// read file -> output of information
///             from different text files
///
/// example:
/// cat (file) or just D:\t.txt>> cat
/// @param path_f path file to need read
void text::read(const fs::path &path_f) {
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
        std::cerr << "[ERROR_READ_TEXT] [CRITICAL] " << e.what() << std::endl;
    }
}

///
/// write text in file
/// @param path_f path file to need write text
/// @param text text to need to write
void text::write(const fs::path &path_f, const std::string &text) {
    try {
        std::ofstream out;
        out.open(path_f, std::ios::app);

        if (!out.is_open()) {
            std::println(std::cerr, "[ERR] Could not open file: {}", path_f.string());
            return;
        }

        if (out.is_open())
            out << text << std::endl;

        out.close();
        std::println("[SYSTEM][TEXT] Text has been written in file [{}]", path_f.string());
    } catch (const std::exception& e) {
        std::cerr << "[ERROR_WRITE_TEXT] [CRITICAL] " << e.what() << std::endl;
    }
}

///
/// rewrite text in file
/// @param path_f path file to need rewrite text
/// @param text text to need to rewrite
void text::rewrite(const fs::path &path_f, const std::string &text) {
    try {
        std::ofstream out;
        out.open(path_f);

        if (!out.is_open()) {
            std::println(std::cerr, "[ERR] Could not open file: {}", path_f.string());
            return;
        }

        if (out.is_open())
            out << text << std::endl;

        out.close();
        std::println("[SYSTEM][TEXT] Text has been rewritten in file [{}]", path_f.string());
    } catch (const std::exception& e) {
        std::cerr << "[ERROR_REWRITE_TEXT] [CRITICAL] " << e.what() << std::endl;
    }
}

///
/// like a notepad
/// @param path_f path file to need to write text
void text::write_many_lines(const fs::path &path_f) {
    try {
        std::ofstream out(path_f);

        if (!out.is_open()) {
            std::println(std::cerr, "[ERR] Could not open file: {}", path_f.string());
            return;
        }

        std::string line;
        std::println("Enter text (type 'done' or '!' on a new line to finish):");

        while (std::getline(std::cin, line)) {
            if (line == "done" || line == "!" || line == "~")
                break;

            out << line << std::endl;
        }

        out.close();
        std::println("[SYSTEM][TEXT] Text has been written in file [{}]", path_f.string());

    } catch (const std::exception& e) {
        std::cerr << "[ERROR_WRITE_MANY_LINES_TEXT] [CRITICAL] " << e.what() << std::endl;
    }
}

