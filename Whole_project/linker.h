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
	Linker() {};
	Linker(std::vector<ObjectFile>& obj_file_list);
	/**
	 * Method: getExecutableFile
	 * Usage: ExecutableFile exe_file = linker.getExecutableFile();
	 * ------------------------------------------------------------
	 * @brief Return corresponding executable file.
	 */
	ExecutableFile getExecutableFile() { return exe_file; };
	/**
	 * Method: link
	 * Usage: linker.link(obj_file_list)
	 * ------------------------------------------------------------
	 * @brief Set the linker object and generate executable file
	 */
	void link(std::vector<ObjectFile>& obj_file_list);

private:

	ExecutableFile exe_file;

};


#endif // LINKER_H





