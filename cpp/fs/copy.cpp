//
// Created by Alexander on 29.04.2026.
//

#include "../../header/fs/COPY.h"
#include "../../header/helper/Helperfs/HFILEF.h"


//=======================
//  Copy Folder / File
//      local func
//=======================
void copy_file_with_overwrite(const fs::path& from, const fs::path& to,
                              const std::string parameter) {
      const fs::path path_ff = path_ff::get_path();

      fs::path source = HFILEF::get_fetch_full_path(from, path_ff);
      fs::path target = HFILEF::get_fetch_full_path(to, path_ff);

      if (fs::is_directory(target)) {
           target /= source.filename();
      }

      if (fs::is_symlink(source)) {
           std::println(std::cerr, "[WARNING] cannot overwrite symlink!");
           fs::copy_symlink(source, target);
           return;
      }

     if (parameter == "--overwrite" || parameter == "-ovr") {
          fs::copy(source, target, fs::copy_options::overwrite_existing);
          std::println("[SYSTEM] success overwritten file {} to {}",
               source.string(), target.string());
     }
     else {
          fs::copy(source, target, fs::copy_options::overwrite_existing);
          std::println("[SYSTEM] success copied file {} to {}",
               source.string(), target.string());
     }
}
void copy_folder_with_overwrite(const fs::path& from, const fs::path& to,
                              const std::string& parameter) {
     const fs::path path_ff = path_ff::get_path();

     fs::path source = HFILEF::get_fetch_full_path(from, path_ff);
     fs::path target = HFILEF::get_fetch_full_path(to, path_ff);

     if (fs::is_directory(target)) {
          target /= source.filename();
     }

     if (fs::is_symlink(source)) {
          std::println(std::cerr, "[WARNING] cannot overwrite symlink!");
          fs::copy_symlink(source, target);
          return;
     }

     if (parameter == "--overwrite" || parameter == "-ovr") {
          fs::copy(source, target, fs::copy_options::overwrite_existing |
               fs::copy_options::recursive);
          std::println("[SYSTEM] success overwritten folder {} to {}",
               source.string(), target.string());
     }
     else {
          fs::copy(source, target, fs::copy_options::recursive);
          std::println("[SYSTEM] success copied folder {} to {}",
               source.string(), target.string());
     }
}

//=======================
//  Copy Folder / File
//      global func
//=======================
// accepted parameter: overwrite
void copy::copy_file(const fs::path& from, const fs::path& to,
     const std::string& parameter) {

     try {
          copy_file_with_overwrite(from, to, parameter);

     }
     catch (const fs::filesystem_error& e) {
          if (e.code() == std::errc::file_exists) {
               std::println(std::cerr, "[CRITICAL_ERROR_COPY_FILES] the file {} already exists!\n"
                                       "you can to overwrite in parameter -> -ovr / --overwrite to overwrite file", from.string());
               return;
          }
          std::println(std::cerr, "[CRITICAL_ERROR_COPY_FILES] {}", e.what());
     }
}


// accepted parameter: overwrite
void copy::copy_folder(const fs::path& from, const fs::path& to,
     const std::string& parameter) {

     try {
          copy_folder_with_overwrite(from, to, parameter);
     }
     catch (const fs::filesystem_error& e) {
          if (e.code() == std::errc::file_exists) {
               std::println(std::cerr, "[CRITICAL_ERROR_COPY_FOLDERS] the folder {} already exists!\n"
                                       "you can to overwrite in parameter -> -ovr / --overwrite to overwrite file", from.string());
               return;
          }
          std::println(std::cerr, "[CRITICAL_ERROR_COPY_FOLDERS] {}", e.what());
     }
}

//===========================
// copying file or folder
//===========================
void copy::copy_folder_or_file(const fs::path& source, const fs::path& target,
     const std::string& parameter) {

     try {
          if (fs::is_regular_file(source))
               copy_file(source, target, parameter);
          else
               copy_folder(source, target, parameter);
     }
     catch (const std::exception& e) {
          std::println(std::cerr, "[CRITICAL_ERROR_COPY] {}", e.what());
     }
}


//=======================
// copying without log
//=======================
void copy::copy_only_for_func_move(const fs::path& from, const fs::path& to) {
     const fs::path path_ff = path_ff::get_path();

     fs::path from_path_for_copy = HFILEF::get_fetch_full_path(from, path_ff);
     fs::path to_path_for_copy = HFILEF::get_fetch_full_path(to, path_ff);

     if (fs::is_directory(to_path_for_copy)) {
          to_path_for_copy /= from_path_for_copy.filename();
     }

     if (fs::is_symlink(from_path_for_copy)) {
          std::println(std::cerr, "[WARNING] cannot overwrite symlink!");
          fs::copy_symlink(from_path_for_copy, to_path_for_copy);
          return;
     }

     fs::copy(from_path_for_copy, to_path_for_copy,
                    fs::copy_options::overwrite_existing |
                    fs::copy_options::recursive);
}
