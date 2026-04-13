//
// Created by AlexanderSYN on 13.04.2026.
//
#include "../../header/fs/space.h"

///
/// @param size size in bytes
/// @return converts from bytes to
///         the desired unit of measurement
std::string space::format_bytes(uintmax_t size) {
    double bytes = static_cast<double>(size);

    if (bytes >= TiB) return std::format("{:.2f} TB", bytes / TiB);
    if (bytes >= GiB) return std::format("{:.2f} GB", bytes / GiB);
    if (bytes >= MiB) return std::format("{:.2f} MB", bytes / MiB);
    if (bytes >= KiB) return std::format("{:.2f} KB", bytes / KiB);

    return std::format("{} B", size);
}

///
/// @param path path
/// @return (string) available disk space
std::string space::available_in_disk(const fs::path &path) {
    try {
        return format_bytes(fs::space(path).available);
    } catch (const std::exception& e) {
        return std::format("[CRITICAL_ERROR_AVAILABLE_IN_DISK] {}", e.what());
    }
}

///
/// @param path path
/// @return (string) total capacity in disk
std::string space::total_capacity(const fs::path &path) {
    try {
        return format_bytes(fs::space(path).capacity);
    } catch (const std::exception& e) {
        return std::format("[CRITICAL_ERROR_TOTAL_CAPACITY] {}", e.what());
    }
}



///
/// get total occupied space in dir
/// @param path path
/// @return (string) total space occupied in dir
std::string space::occupied_dir(const fs::path &path) {
    try {
        std::uintmax_t size = 0;

        std::error_code error_code;
        if (fs::exists(path) && fs::is_directory(path)) {

            auto it = fs::recursive_directory_iterator(
                path, fs::directory_options::skip_permission_denied,
                error_code);

            // Recursive traversal of all files and subfolders
            for (const auto& entry : it) {
                // file_size can also throw an exception
                // if the file has disappeared during the crawl.

                // We add the size only if it is a regular file
                // (not a folder or a link)
                std::error_code err_cde;
                if (fs::is_regular_file(entry)) {
                    auto fsize = fs::file_size(entry, err_cde);
                    if (!err_cde) size += fsize;
                }
            }
        }

        return std::format("total space occupied: {}",
                                format_bytes(size));
    } catch (const std::exception& e) {
        return std::format("[CRITICAL_ERROR_OCCUPIED] {}", e.what());
    }
}
