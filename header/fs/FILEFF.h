//
// Created by AlexanderSYN on 05.04.2026.
//

//==================================
// FILEFF - File Find File / Folder
//==================================

#ifndef FINDFF_H
#define FINDFF_H

#include "include_fs.h"
#include "../helper/Helperfs/HFILEF.h"

class FILEFF {
public:
    //==========================================================
    // find - find File or Folder
    //==========================================================
    static void find(std::string search_term, std::string parametr,
                    const fs::path& path_f);

private:
    //==========================================================
    // for global searching
    //==========================================================
    static void recurs_search(std::string search_term, const fs::path& path_f,
                                std::vector<std::string>& paths_founded_ff,
                                std::string param);

    static void search(const fs::path& dir,const std::string& search_term,
                        std::vector<std::string>& results);

};

#endif //FINDFF_H
