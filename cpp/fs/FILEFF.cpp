//
// Created by AlexanderSYN on 05.04.2026.
//

#include "../../header/fs/FILEFF.h"
#include "../../header/fs/explorer.h"

void FILEFF::find(std::string search_term, std::string parametr,
                  const fs::path &path_f) {

     try {
        std::vector<std::string> paths_founded_ff; // ff - file and folder

         if (!fs::is_directory(path_f) || !fs::exists(path_f)) {
            std::println(std::cerr, "[ERR] find: the folder doesn't exist!\n");
            return;
        }

        std::println("If you are tired of waiting, press the 'Alt' key to stop!");
        std::println("Searching for: '{}' in: {}", search_term, path_f.string());

        //===================================================
        // if parametr = local then searching only in local
        // folder
        //====================================================
        if (parametr == "-l" || parametr == "--local") {
            //========================================
            // Searching so -> find (filename/folder)
            //========================================

            for (const auto &entry: fs::directory_iterator(path_f)) {
                if (GetAsyncKeyState(VK_RMENU) & 0x8000 || GetAsyncKeyState(VK_LMENU) & 0x8000) {
                    std::println("\nSearch stopped by user!");
                    break;
                }

                // check if filename contains search term (case-insensitive)
                std::string filename = entry.path().filename().string();
                std::string search_lower = search_term;
                std::string filename_lower = filename;

                std::transform(search_term.begin(), search_term.end(), search_lower.begin(), ::tolower);
                std::transform(filename_lower.begin(), filename_lower.end(), filename_lower.begin(), ::tolower);

                if (filename_lower.find(search_lower) != std::string::npos) {
                    paths_founded_ff.push_back(entry.path().string());

                    std::println("{} - Found: {}", paths_founded_ff.size(), entry.path().string());

                }
            }
        } else if (parametr == "-lf" || parametr == "--local-file") {
            //========================================
            // Searching so -> *.(extension)
            //========================================
            if (search_term.substr(0, 2) == "*.") {
                std::string target_extension = search_term.substr(1);

                std::cout << "Searching only files with extension: " << search_term.substr(2) << std::endl;
                try {
                    for (const auto &entry: fs::directory_iterator(path_f)) {
                        if (GetAsyncKeyState(VK_RMENU) & 0x8000 || GetAsyncKeyState(VK_LMENU) & 0x8000) {
                            std::println("\nSearch stopped by user!");
                            break;
                        }

                        if (entry.is_regular_file() && entry.path().extension().string() == target_extension) {
                            paths_founded_ff.push_back(entry.path().string());

                            std::println("{} - Found: {}", paths_founded_ff.size(), entry.path().string());

                        }
                    }
                } catch (const std::exception &e) {
                    std::println(std::cerr, "[ERROR_FIND_LFILE] {}", e.what());
                }
            }
            //========================================
            // Searching so -> (filename).(extension)
            //========================================
            else {
                std::string target_extension = search_term.substr(1);

                std::cout << "Searching only files with extension: " << search_term.substr(2) << std::endl;
                try {
                    for (const auto &entry: fs::directory_iterator(path_f)) {
                        if (GetAsyncKeyState(VK_RMENU) & 0x8000 || GetAsyncKeyState(VK_LMENU) & 0x8000) {
                            std::println("\nSearch stopped by user!");
                            break;
                        }
                        // if you write extension
                        if (!entry.path().filename().string().ends_with(".*") && entry.is_regular_file()
                            && entry.path().extension().string() == target_extension
                            && entry.path().filename().string() == search_term) {

                            paths_founded_ff.push_back(entry.path().string());
                            std::println("{} - Found: {}", paths_founded_ff.size(), entry.path().string());
                        }

                        // if you write (filename).*
                        else {
                            if (entry.is_regular_file() && entry.path().stem().string() == search_term.substr(
                                    0, search_term.size() - 2)) {

                                paths_founded_ff.push_back(entry.path().string());
                                std::println("{} - Found: {}",
                                    paths_founded_ff, entry.path().string());

                            }
                        }
                    }
                } catch (const std::exception &e) {
                    std::println(std::cerr, "[ERROR_FIND_FILE] {}",
                        e.what());
                }
            }
        } else if (parametr == "-ld" || parametr == "--local-dir") {
            try {
                std::println("Only folders");
                for (const auto &entry: fs::directory_iterator(path_f)) {
                    // for stop searching
                    if (GetAsyncKeyState(VK_RMENU) & 0x8000 || GetAsyncKeyState(VK_LMENU) & 0x800) {
                        std::println("\nSearch stopped by user!");
                        break;
                    }

                    if (is_directory(entry.path()) &&
                        entry.path().filename().string() == search_term) {
                        paths_founded_ff.push_back(entry.path().string());
                        std::println("{} - Found Folder: {}",
                            paths_founded_ff.size(), entry.path().string());
                    }
                }
            } catch (const std::exception &e) {
                // LD - local directory
                std::println(std::cerr, "[ERROR_FIND_LDir] {}", e.what());
            }
        }
        //
        // global searching (don't finished)
        //
        else if (parametr == "-g" || parametr == "--global"
                 || parametr == "-r" || parametr == "--recursive"
                 || parametr == "-gd" || parametr == "--global-directory"
                 || parametr == "-gf" || parametr == "--global-file") {
            recurs_search(search_term, path_f, paths_founded_ff,
                    parametr);
        }

        // Handle results
        if (!paths_founded_ff.empty())
            std::println("\nFound {} item(s)", paths_founded_ff.size());
            std::println("Enter number to open (1-{}) or -1 to exit",
                    paths_founded_ff.size());

            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

            choice--;
            if (choice >= 1 && choice < paths_founded_ff.size()) {
                explr::show_in_explorer(paths_founded_ff, choice);
            }
        else
            std::println("No files or folders found matching '{}'",
                        search_term);

    } catch (const std::exception &e) {
        std::cerr << "[ERROR_FIND] " << e.what() << std::endl;
    }

}


void FILEFF::recurs_search(std::string search_term,
    const fs::path &path_f, std::vector<std::string> &paths_founded_ff,
    std::string param) {

     std::error_code ec;

    fs::recursive_directory_iterator it(path_f, ec);
    fs::recursive_directory_iterator end;

    std::string search_lower = search_term;
    std::transform(search_lower.begin(), search_lower.end(),
        search_lower.begin(), ::tolower);

    const bool only_files = (param == "-gf" || param == "--global-file");
    const bool only_dirs = (param == "-gd" || param == "-Flobal-directory");
    // search only extension file
    const bool special_search_file_ext = search_term.substr(0, 2) == "*.";
    // search only name file
    const bool special_search_file_name = search_term.ends_with(".*");

    for (; it != end; it.increment(ec)) {

        if (GetAsyncKeyState(VK_RMENU) & 0x8000 ||
            GetAsyncKeyState(VK_LMENU) & 0x8000) {
            std::cout << "\n Search stopped by user!\n";
            break;
        }

        const auto& entry = *it;

        if (entry.is_symlink()) {
            it.disable_recursion_pending();
            continue;
        }

        if (HFILEF::is_system(entry.path())) {
            it.disable_recursion_pending();
            continue;
        }

        std::string filename = entry.path().filename().string();
        std::transform(filename.begin(), filename.end(),
                    filename.begin(), ::tolower);

        if (filename.find(search_lower) == std::string::npos
            && !special_search_file_name
            && !special_search_file_ext) continue;

        // check only files (without special search)
        if (only_files && !fs::is_regular_file(entry.path())
            && !special_search_file_ext && !special_search_file_name) {
            continue;
        }

        if (only_dirs && !fs::is_directory(entry.path()))
            continue; // check only dirs

        // special search
        // only for extension
        if (special_search_file_ext) {
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(),
                            ::tolower);

            std::string target_ext = search_term.substr(1);
            std::transform(target_ext.begin(), target_ext.end(),
                                target_ext.begin(), ::tolower);


            if (ext != target_ext) continue;
            else  {
                paths_founded_ff.push_back(entry.path().string());
                std::println("{} - Found: {}", paths_founded_ff.size(),
                                                entry.path().string());
            }
        }
        // only for name
        if (special_search_file_name) {
            std::string name = entry.path().stem().string();
            std::transform(name.begin(), name.end(), name.begin(), ::tolower);

            std::string target_name = search_term.substr(0, search_term.size() - 2);
            std::transform(target_name.begin(), target_name.end(), target_name.begin(), ::tolower);

            if (name != target_name || fs::is_directory(entry.path()))
                continue;
            else  {
                paths_founded_ff.push_back(entry.path().string());
                std::println("{} - Found: {}", paths_founded_ff.size(),
                                                entry.path().string());
            }
        }

        paths_founded_ff.push_back(entry.path().string());
        std::println("{} - Found: {}", paths_founded_ff.size(),
                                            entry.path().string());
    }

}




