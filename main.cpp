#include <iostream>
#include <chrono>
#include <format>
#include <print>
#include <filesystem>
#include <string>
#include <complex>
#include <unordered_map>
#include <functional>

//
// fs
//
#include "header/fs/FILEO.h"
#include "header/fs/FILEC.hpp"

//
// console
//
#include "header/console/cmd.h"

//
// helper
//
#include <bits/regex_constants.h>

#include "header/console/color_console.h"
#include "header/helper/path_ff.h"


namespace fs = std::filesystem;

//
// C++ 26
// MCCommander - Mini Console Commander
//

int main() {
    setlocale(LC_ALL, "ru");

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
        if (args.empty()) {
            std::println("you need to write like this -> color ... <- (color name)");
            return;
        }

        std::println("{}", ColorConsole::choice_color(args[1]));
    };
    commands["col"] = commands["color"];

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
                        FILEC::create_file_and_record(path_ff::get_path(), "history.txt", history);
                }
                else {
                    if (args[3] == "hist" or args[3] == "history"
                        || args[3] == "-h" || args[3] == "--history")
                        FILEC::create_file_and_record(args[4], args[2], history);

                    else if (args[3] == "hist_srh" or args[3] == "history_search"
                        || args[3] == "-h-s" || args[3] == "--history_search")
                        FILEC::create_file_and_record(args[4], args[2], hist_search);
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
        FILEO::read_file(args[0]);
    };

    //============================
    // work with files / folders
    //============================
    commands["cd"] = [&](const std::vector<std::string>& args) {
        if (args.size() <= 1) {
            std::println("{}", path_ff::get_OPath());
            return;
        }
        else if (args.size() == 2)
            FILEO::set_path_in_cd(args[1], path_ff::get_OPath(),
                path_ff::get_path());
        else {
            std::string path_with_spaces;
            for (int i = 1; i <= args.size() - 1; i++) {
                if (i != args.size() - 1)
                    path_with_spaces += args[i] + " ";
                else
                    path_with_spaces += args[i];
            }

            std::println("{}", path_with_spaces);

            FILEO::set_path_in_cd(path_with_spaces, path_ff::get_OPath(),
                path_ff::get_path());
        }
    };
    commands["pwd"] = [&](const std::vector<std::string>&) {
        std::println("{}", path_ff::get_OPath());
    };

    commands["open"] = [&](const std::vector<std::string>& args) {
        FILEO::command_open(path_ff::get_path());
    };



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


