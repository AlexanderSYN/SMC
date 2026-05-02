//
// Created by AlexanderSYN on 06.04.2026.
//

#include "../../header/text/io_text.h"

#include "../../header/fs/DIRMAKE.h"
#include "../../header/helper/helper.h"


//===============================
//    Read text or other files
//===============================

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

//===============================
//             write
//===============================
///
/// write without new line text in file
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
            out << text;

        out.close();
        std::println("[SYSTEM][TEXT] Text has been written in file [{}]", path_f.string());
    } catch (const std::exception& e) {
        std::cerr << "[ERROR_WRITE_TEXT] [CRITICAL] " << e.what() << std::endl;
    }
}

///
/// writing lines from each new line after each space
/// text in file
/// @param path_f path file to need write text
/// @param text text to need to write
void text::writeln(const fs::path &path_f, const std::string &text) {
    try {
        std::ofstream out;
        out.open(path_f, std::ios::app);

        if (!out.is_open()) {
            std::println(std::cerr, "[ERR] Could not open file: {}", path_f.string());
            return;
        }

        if (out.is_open())
            out << text;

        out.close();
        std::println("[SYSTEM][TEXT] Text has been written in file [{}]", path_f.string());
    } catch (const std::exception& e) {
        std::cerr << "[ERROR_WRITE_TEXT] [CRITICAL] " << e.what() << std::endl;
    }
}


void write_lines(const fs::path &path_f) {
    std::ofstream out(path_f,std::ios::app);

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
}
///
/// like a notepad
/// @param path_f path file to need to write text
void text::write_many_lines(const fs::path &path_f) {
    try {
        write_lines(path_f);
    } catch (const std::exception& e) {
        std::cerr << "[ERROR_WRITE_MANY_LINES_TEXT] [CRITICAL] " << e.what() << std::endl;
    }
}

//===============================
//           rewrite
//===============================

///
/// rewriting lines from each new line after each space
/// text in file
/// @param path_f path file to need rewrite text
/// @param text text to need to rewrite
void text::rewriteln(const fs::path &path_f, const std::string &text) {
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

void rewrite_lines_for_func_rewrite_many_lines(const fs::path &path_f) {
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
}
///
/// like a notepad
/// @param path_f path file to need to write text
void text::rewrite_many_lines(const fs::path &path_f) {
    try {
        rewrite_lines_for_func_rewrite_many_lines(path_f);
    } catch (const std::exception& e) {
        std::cerr << "[ERROR_WRITE_MANY_LINES_TEXT] [CRITICAL] " << e.what() << std::endl;
    }
}

//===============================
//             echo
//===============================
void func_echo(const std::vector<std::string>& args,
                fs::path default_path) {
    fs::path tmp_path = helper::connect_path(path_ff::get_path(),
                                            default_path);

    if (!fs::exists(default_path) && !fs::is_regular_file(default_path)) {
        if (fs::exists(tmp_path)) {
            default_path = tmp_path;
        }
    }

    // Minimum: command + parameter + at least one word + optional path
    if (args.size() < 3) {
        std::println("[HINT] Usage: echo (-w | --write | -rw | --rewrite) <text> [file_path]");
        return;
    }

    // Parse parameter
    bool is_append = (args[1] == "-rw" || args[1] == "--rewrite");
    bool is_write = (args[1] == "-w" || args[1] == "--write");

    if (!is_write && !is_append) {
        std::println("[ERR] Unknown parameter: {}", args[1]);
        std::println("[HINT] Use -w (write) or -rw (rewrite/append)");
        return;
    }

    // Determine file path (last argument or default)
    fs::path target_path = default_path;
    size_t text_start_index = 2;  // start from first word after parameter

    // Check if last argument looks like a path (has extension or slashes)
    const std::string& last_arg = args.back();
    bool has_path_specified = (last_arg.find('/') != std::string::npos ||
                               last_arg.find('\\') != std::string::npos ||
                               last_arg.find('.') != std::string::npos);

    if (has_path_specified && args.size() > 3) {
        target_path = helper::connect_path(default_path, last_arg);
        text_start_index = 2;  // words before the path are the text
    }

    // Combine all text arguments into one string
    std::string full_text;
    for (size_t i = text_start_index; i < args.size() - (has_path_specified ? 1 : 0); ++i) {
        if (!full_text.empty()) full_text += " ";
        full_text += args[i];
    }

    // Write to file
    if (is_write)
        text::write(target_path, full_text);
    else
        text::rewrite(target_path, full_text);  // or append
}

///
/// Executes a full-featured `echo` command.
/// @param args         Vector of args passed from main.cpp
/// @param default_path Path obtained from path_ff::get_path()
void text::full_functional_echo(const std::vector<std::string>& args,
                                fs::path default_path) {

    try {
        func_echo(args, default_path);
    }
    catch (const std::exception& e) {
        std::println(std::cerr, "[CRITICAL_ERROR_ECHO] {}", e.what());
    }
}

//===================================
// resolve file path and other func
//===================================
///
/// Resolves a file path from command arguments
///
/// Returns an existing path if provided, otherwise connects the argument
/// with the default path. Returns default path when no argument is given.
///
/// @param args         command arguments (args[1] is the file path)
/// @param default_path fallback path when args are empty
/// @return fs::path    resolved file path
///
fs::path text::resolve_file_path_for_echolnrw(const std::vector<std::string>& args,
                           const fs::path& default_path) {

    if (args.size() == 1)
        return default_path;

    if (fs::exists(args[1]))
        return fs::path(args[1]);

    return helper::connect_path(default_path, args[1]);
}

