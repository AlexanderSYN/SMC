//
// Created by AlexanderSYN on 01.05.2026.
//
#include "../../header/fs/MOVE.h"
#include "../../header/fs/COPY.h"
#include "../../header/fs/FILERMV.h"
#include "../../header/helper/Helperfs/HFILEF.h"

void move_file_or_folder(fs::path from, fs::path to) {
    const fs::path current_path = path_ff::get_path();

    fs::path source = HFILEF::get_fetch_full_path(from, current_path);
    fs::path target  = HFILEF::get_fetch_full_path(to, current_path);

    copy::copy_only_for_func_move(from, to);

    if (exists(target) && exists(source)) {
        FILERMV::remove_without_param_and_log(source);
        std::println("[SYSTEM] FILE or FOLDER successfully moved to {}",target.string());
    }
    else
        std::println(std::cerr, "[ERROR] FILE or FOLDER is not moved to {}", target.string());
}

void MOVE::move_item(fs::path source, fs::path target) {
    try {
        move_file_or_folder(source, target);
    } catch (const std::exception &e) {
        std::println(std::cerr, "[CRITICAL_ERROR_MOVE] {}", e.what());
    }
}

