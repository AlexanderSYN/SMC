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

//
// console
//
#include "header/console/cmd.h"

//
// helper
//
#include "header/console/color_console.h"
#include "header/helper/path_ff.h"


namespace fs = std::filesystem;

//
// MCCommander - Mini Console Commander
//

int main() {
    setlocale(LC_ALL, "ru");

    std::vector<std::string> history {};

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
        if (args.size() < 1) {
            std::println("you need to write like this -> color ... <- (color name)");
            return;
        }

        std::println("{}", ColorConsole::choice_color(args[1]));
    };

    commands["cmd"] = [&](const std::vector<std::string>& args) {
        if (args.size() == 1 || args[1] == "run") {
            std::println("You just run cmd by Windows!");
            std::println("To exit type exit!");
            cmd::run("cmd");
            return;
        }

        cmd::run(args[1]);
    };

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

        FILEO::set_path_in_cd(args[1], path_ff::get_OPath(),
            path_ff::get_path());
    };
    commands["pwd"] = [&](const std::vector<std::string>&) {
        std::println("{}", path_ff::get_OPath());
    };



    while (isRun) {
        try {
            if (isShowPathWhenStartLoop)
                std::print("{} >>", path_ff::get_OPath());
            else
                std::print("$ ");

            std::getline(std::cin, user_input);

            std::vector<std::string> args;
            std::istringstream iss(user_input);
            std::string word;

            while (iss >> word)
                args.push_back(word);

            if (!args.empty() && commands.contains(args[0]))
                commands[args[0]](args);
            else
                std::println("Uknown command!");

        } catch (const std::exception& e) {
            std::cerr << "[ERROR_CONSOLE] " << e.what() << std::endl;
        }
    }

}


