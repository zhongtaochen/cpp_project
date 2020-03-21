#ifndef LINKER_H
#define LINKER_H

#include "objectfile.h"
#include "executablefile.h"
#include <vector>

class Linker {

public:

/**
 * Constructor: Linker
 * Usage: Linker linker(obj_file_list);
 * ------------------------------------
 * @brief Initilize Linker object and generate executable file.
 */
    Linker(std::vector<ObjectFile> obj_file_list);

/**
 * Method: getExecutableFile
 * Usage: ExecutableFile exe_file = linker.getExecutableFile();
 * ------------------------------------------------------------
 * @brief Return corresponding executable file.
 */
    ExecutableFile getExecutableFile() {return exe_file;};

private:

    ExecutableFile exe_file;

};

#endif // LINKER_H
