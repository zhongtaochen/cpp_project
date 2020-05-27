/**
 * @file executablefile.h
 * @brief <code>ExecutableFile</code> class.
 * @details This file exports an <code>ExecutableFile</code> class,
 * adapting from the descriptions in Patterson and Henessy's book section 2.12.
 */

#ifndef EXECUTABLEFILE_H
#define EXECUTABLEFILE_H

#include "objectfile.h"
#include <vector>

/**
 * @brief Output of designed <code>Linker</code> in this project.
 * Records neccessary information for further simulating and debugging.
 */
class ExecutableFile {

public:

/**
 * @brief Void initilizer for the <code>ExecutableFile</code> class.
 * All attributes are public.
 */
    ExecutableFile(){};

    unsigned int text_size=0;
    unsigned int data_size=0;
    std::vector<TextCell> text_segment;
    std::vector<DataCell> data_segment;
};

#endif // EXECUTABLEFILE_H
