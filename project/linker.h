/**
 * @file linker.h
 * @brief <code>Linker</code> class.
 * @details This file exports <code>Linker</code> class, which takes multiple
 * <code>ObjectFile</code> objects as input and produces <code>ExecutableFile</code>
 * with static linking scheme.
 */

#ifndef LINKER_H
#define LINKER_H

#include "objectfile.h"
#include "executablefile.h"
#include <vector>

/**
 * @brief Staticly links several object files and produces executable files for
 * further simulation or debugging.
 */
class Linker {

public:

/**
 * @brief Initilizer for <code>Linker</code> class.
 */

    Linker(){};
	Linker(std::vector<ObjectFile>& obj_file_list);

/**
 * @brief Return corresponding executable file.
 */

	ExecutableFile getExecutableFile() { return exe_file; };

/**
 * @brief Link <code>ObjectFile</code> objects and produce
 * <code>ExecutableFile</code>.
 */

	void link(std::vector<ObjectFile>& obj_file_list);

private:

	ExecutableFile exe_file;

};

#endif // LINKER_H
