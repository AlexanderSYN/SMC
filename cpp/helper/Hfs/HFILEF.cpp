//
// Created by AlexanderSYN on 31.03.2026.
//

#include "../../../header/helper/Helperfs/HFILEF.h"

///
/// return the file or folder type
/// [вернуть тип файла или папки]
///
/// example
/// t.txt -> [FILE]
///
/// @param path_f the path to check and find out which type
/// @return the file or folder type
std::string HFILEF::type(const fs::path& path_f) {
    if (fs::is_regular_file(path_f)) return "[FILE]";
    if (fs::is_directory(path_f)) return "[DIR]";
    if (fs::is_symlink(path_f)) return "[LINK]";
    if (fs::is_block_file(path_f)) return "[BLOCK]";
    if (fs::is_character_file(path_f)) return "[CHARACTER]";
    if (fs::is_fifo(path_f)) return "[PIPE (FIFO)]";
    if (fs::is_socket(path_f)) return "[SOCKET]";

    return "[UNKNOWN]";
}

///
/// Cross-platform verification of whether a file or folder is hidden
/// [Кроссплатформенная проверка того, скрыт ли файл или папка]
///
/// @param path_f the path to check and find out if it is hidden or not
/// @return [HIDDEN] or nothing
std::string HFILEF::is_hidden(const fs::path& path_f) {
#ifdef _WIN32 // for windows
    DWORD attributes = GetFileAttributesA(path_f.string().c_str());

    if ((attributes & FILE_ATTRIBUTE_HIDDEN) != 0)
        return "[HIDDEN]";

    return "";

#else // for MACOS / Linux
    if (path_f.filename().string()[0] == '.')
        return "[HIDDEN]"

#endif
}

///
/// checks vector of secret formats and folders that are
/// in the OS and if it finds something, then true, otherwise false
/// [проверяет вектор секретных форматов и папок, которые есть в
/// операционной системе, и если он что-то находит, то это true,
/// в противном случае false]
///
/// @param path the path to check
/// @return true - system file/folder and false - not system
bool HFILEF::is_system(const fs::path &path) {
    try {
        std::string path_str = path.string();
        std::string filename = path.filename().string();

        // Skip hidden files/folders (starting with a dot in Linux/Mac)
        if (filename[0] == '.') {
            return true;
        }

        // Skip the system directories
        for (const auto &sys_dir: SYSTEM_DIRECTORIES) {
            if (path_str.find(sys_dir) != std::string::npos) {
                return true;
            }
        }

        // Skipping files with system extensions
        if (path.has_extension()) {
            std::string ext = path.extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

            for (const auto &sys_ext: SYSTEM_EXTENSIONS) {
                if (ext == sys_ext) {
                    return true;
                }
            }
        }

        // Skipping temporary files
        if (filename.find("~") != std::string::npos ||
            filename.find(".tmp") != std::string::npos ||
            filename.find("temp") != std::string::npos) {
            return true;
            }

        return false;
    } catch (const std::exception& e) {
        std::println(std::cerr, "[CRITICAL_ERROR_CHECK_SYSTEM_FILE] {}",
            e.what());
        return false;
    }
}

std::string HFILEF::get_size_file(const fs::path &path) {
    try {
        auto size_in_byte = fs::file_size(path);

        const long KB = 1024;
        const long MB = 1024 * 1024;
        const long GB = 1024 * 1024 * 1024;

        if (size_in_byte < KB)
            return std::to_string(size_in_byte) + "bytes";
        if (size_in_byte < MB)
            return std::to_string(size_in_byte) + "kilobytes";
        if (size_in_byte < GB)
            return std::to_string(size_in_byte) + "megabytes";

        return std::to_string(size_in_byte) + "gigabytes";
    } catch (const std::exception& e) {
        return "ERR";
    }
}


