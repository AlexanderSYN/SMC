#include <iostream>
#include <chrono>
#include <format>
#include <print>
#include <filesystem>
#include <string>
#include <complex>
#include <unordered_map>
#include <functional>
#include <windows.h>

//
// fs
//
#include "header/fs/FILEO.h"
#include "header/fs/FILEDC.hpp"
#include "header/fs/FILEDEL.h"
#include "header/fs/FILEFF.h"
#include "header/fs/explorer.h"

//
// text
//
#include "header/text/io_text.h"

//
// console
//
#include "header/console/cmd.h"
#include "header/console/color_console.h"

//
// time and date
//
#include"header/date/date.h"

//
// helper
//
#include "header/helper/helper.h"
#include "header/helper/path_ff.h"



namespace fs = std::filesystem;

//
// C++ 26
// MCCommander - Mini Console Commander
//

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // hello
#ifdef _WIN32 // for windows
    std::println("Hello Windows");
#elif __APPLE__
    std::println("Hello MAC-OS");
#else
    std::println("Hello LINUX");
#endif

    // history all
    std::vector<std::string> history {};
    std::vector<std::string> hist_search {}; // history of found files

    std::string user_input;

    bool isRun = true;
    bool isShowPathWhenStartLoop = true;

    std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> commands;

    // commands
    //============
    // console
    //============
    commands["help"] = [&](const std::vector<std::string>&) {
        std::print("HELP");
    };

    commands["color"] = [&](const std::vector<std::string>& args) {
        if (args.size() <= 1) {
            std::println("[HINT] you need to write like this -> color ... <- (color name)");
            return;
        }

        std::println("{}", ColorConsole::choice_color(args[1]));
    };
    commands["col"] = commands["color"];

    //================
    //time and date
    //================
    commands["time"] = [&](const std::vector<std::string>&) {
        println("{}", date::local_time());
    };

    commands["date"] = [&](const std::vector<std::string>&) {
        println("{}", date::local_date_and_time());
    };

    commands["cmd"] = [&](const std::vector<std::string>& args) {
        if (args.size() == 1 || args[1] == "run") {
            std::println("You just to run the cmd by Windows!");
            std::println("To exit type exit!");
            cmd::run("cmd");
            return;
        }

        cmd::run(args[1]);
    };

    commands["path"] = [&](const std::vector<std::string>& args) {
        if (args.size() == 1) {
            if (isShowPathWhenStartLoop)
                std::println("[HINT] maybe you mean -> path --hide?");
            else
                std::println("[HINT] maybe you mean -> path --show?");
            return;
        }

        if (args[1] == "--hide" || args[1] == "-h" || args[1] == "hide")
            isShowPathWhenStartLoop = false;

        else if (args[1] == "--show" || args[1] == "-s" || args[1] == "show")
            isShowPathWhenStartLoop = true;
        else {
            std::println("[ERR] Unknown parameter!");
            std::println("[HINT] maybe you mean -> path --hide"
                                                     " or path --show?");
        }
    };

    commands["history"] = [&](const std::vector<std::string>& args) {
        if (args.size() > 1) {

            if (args[1] == "search" || args[1] == "-s" || args[1] == "--search")
                if (!hist_search.empty())
                    for (int i = 1; i < hist_search.size(); i++)
                        std::println("{}) {}", i, hist_search[i]);
                else
                    std::println("[HINT] history search empty");

            else if (args[1] == "save" || args[1] == "-sv" || args[1] == "--save") {
                if (args.size() < 4) {
                    std::println("[HINT] you can to specify the path to"
                                 " the txt file to save the console histor, example:"
                                 "hist save name.txt -h or -h_s path");
                    std::print("maybe create a text file and record the"
                               " history in the current path? <y/n>: ");
                    char choice;
                    std::cin >> choice;
                    if (std::tolower(choice) == 'y')
                        FILEDC::create_file_and_record(path_ff::get_path(), "history.txt", history);
                }
                else {
                    if (args[3] == "hist" or args[3] == "history"
                        || args[3] == "-h" || args[3] == "--history")
                        FILEDC::create_file_and_record(args[4], args[2], history);

                    else if (args[3] == "hist_srh" or args[3] == "history_search"
                        || args[3] == "-h-s" || args[3] == "--history_search")
                        FILEDC::create_file_and_record(args[4], args[2], hist_search);
                }
            }

        } else
            for (int i = 1; i < history.size(); i++)
                std::println("{}) {}", i, history[i]);

    };
    commands["hist"] = commands["history"];


    commands["clear"] = [&](const std::vector<std::string>& args) {
        #ifdef _WIN32 // for windows
                system("cls");
        #else // for Mac OS / Linux
                system("clear");
        #endif
    };
    commands["cls"] = commands["clear"];

    commands["exit"] = [&](const std::vector<std::string>&) {
        isRun = false;
    };
    commands["ex"] = commands["exit"];


    //=================
    // work with text
    //=================
    commands["cat"] = [&](const std::vector<std::string>& args) {
        if (args.size() > 1) {
            fs::path path = helper::connect_path(path_ff::get_path(), args[1]);
            if (fs::exists(path) & fs::is_regular_file(path))
                text::read(path.string());
            else
                text::read(args[1]);
        }
        else
            text::read(path_ff::get_path());
    };
    commands["read"] = commands["cat"];

    // echo (param) (path / text) (text)
    commands["echo"] = [&](const std::vector<std::string>& args) {
        text::full_functional_echo(args, path_ff::get_path());
    };
    // write many lines
    // echoln (path / nothing)
    commands["echoln"] = [&](const std::vector<std::string>& args) {
        fs::path path_f = text::resolve_file_path_for_echolnrw(args,
                                            path_ff::get_path());
        text::write_many_lines(path_f);
    };
    // rewrite text
    commands["echolnrw"] = [&](const std::vector<std::string>& args) {
        fs::path path_f = text::resolve_file_path_for_echolnrw(args,
                                        path_ff::get_path());
        text::rewrite_many_lines(path_f);
    };


    //============================
    // work with files / folders
    //============================
    commands["cd"] = [&](const std::vector<std::string>& args) {
        if (args.size() <= 1)
            std::println("{}", path_ff::get_OPath());

        else if (args.size() == 2)
            FILEO::set_path_in_cd(args[1], path_ff::get_OPath(),
                path_ff::get_path());

        else {
            FILEO::set_path_in_cd(
                helper::connect_path_with_spaces_str(args),
                path_ff::get_OPath(),
                path_ff::get_path());
        }
    };
    commands["pwd"] = [&](const std::vector<std::string>&) {
        std::println("{}", path_ff::get_OPath());
    };

    commands["explorer"] = [&](const std::vector<std::string>& args) {
        if (args.size() <= 1) {
            explr::show_in_explorer(path_ff::get_path());
            return;
        }

        if (args.size() > 2) {
            explr::show_in_explorer(helper::connect_path_with_spaces(args));
        }

        explr::show_in_explorer(args[1]);
    };
    commands["exp"] = commands["explorer"];
    commands["openf"] = commands["explorer"];

    commands["run"] = [&](const std::vector<std::string>& args) {
        if (args.size() <= 1)
            explr::run_file(path_ff::get_path());

        else {
            if (fs::exists(args[1])) {
                explr::run_file(args[1]);
            }
            else {
                fs::path fll_path = helper::connect_path(path_ff::get_path(),
                                                        args[1]);
                explr::run_file(fll_path);
            }
        }
    };

    commands["open"] = [&](const std::vector<std::string>& args) {
        FILEO::command_open(path_ff::get_path());
    };
    commands["dir"] = [&](const std::vector<std::string>&) {
        FILEO::command_dir_windows(path_ff::get_path());
    };
    commands["ls"] = [&](const std::vector<std::string>& args) {
        if (args.size() <= 1)
            FILEO::command_list(path_ff::get_path());
        else {
            fs::path tmp_path = helper::connect_path(path_ff::get_path(), args[1]);
            if (fs::exists(tmp_path))
                FILEO::command_list(tmp_path);
            else
                FILEO::command_list(helper::connect_path_with_spaces_str(args, 2));
        }
    };

    //========================
    // find
    //========================
    commands["find"] = [&](const std::vector<std::string>& args) {
        if (args.size() == 1) {
            std::println("[HINT] You need to write like so: "
                         "find <param> <file or folder>");
            return;
        }
        if (args.size() <= 2) {
            FILEFF::find(args[1], "-g", path_ff::get_path());
            return;
        }

        FILEFF::find(args[2], args[1], path_ff::get_path());
    };

    //========================
    // create file or folder
    //========================
    commands["touch"] = [&](const std::vector<std::string>& args) {
      FILEDC::command_touch(path_ff::get_path(), args);
    };
    commands["mkdir"] = [&](const std::vector<std::string>& args) {
        FILEDC::command_mkdir(path_ff::get_path(), args);
    };
    //========================
    // delete file or folder
    //========================
    commands["delete"] = [&](const std::vector<std::string>& args) {
        if (args.size() == 2)
            FILEDEL::del(helper::connect_path(path_ff::get_path(), args[1]));
        else if (args.size() >= 3) {

        }
        else
            FILEDEL::del(path_ff::get_path());
    };
    commands["del"] = commands["delete"];
    commands["remove"] = commands["delete"];
    commands["rmv"] = commands["delete"];

    std::println("for help type help!");

    while (isRun) {
        try {
            if (isShowPathWhenStartLoop)
                std::print("{} >>", path_ff::get_OPath());
            else
                std::print("$ ");

            std::getline(std::cin, user_input);
            history.push_back(user_input);

            std::vector<std::string> args;
            std::istringstream iss(user_input);
            std::string word;

            while (iss >> word)
                args.push_back(word);

            if (!args.empty() && commands.contains(args[0]))
                commands[args[0]](args);
            else {
                std::println("Unknown command!");
                std::println("for help type help!");
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERROR_CONSOLE] " << e.what() << std::endl;
        }
    }

}


