//
// Created by AlexanderSYN on 30.03.2026.
//

#ifndef FILEC_H
#define FILEC_H

#include "include_fs.h"

//
// FILEC - File Create
//
namespace FILEC {
    void create_file(fs::path path, std::string file);
    void command_touch(const fs::path &path,
                std::vector<std::string> args);

    ///
    ///create file and record text there
    /// @param path the path to save it to
    /// @param file file name and path
    /// @param text which text should I write
    template<typename T>
    void create_file_and_record(fs::path path,
                                       std::string file, T text) {
        std::string file_path = path.string() + "\\" + file;
        std::ofstream outFile(file_path);

        if (outFile.is_open()) {
            // check for vector
            if constexpr (requires {text.begin(), text.end();} &&
                !std::is_convertible_v<decltype(text), std::string>) {
                for (auto const& line : text)
                    outFile << line << "\n";
                }
            else
                outFile << text;

            outFile.close();
            std::println("[SYSTEM] file created and written successfully!");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
            return;
        }

        std::println(std::cerr, "[SYSTEM][ERROR] Could not create file at {}!", file_path);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
    }
}

#endif //FILEC_H
