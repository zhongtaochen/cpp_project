//#ifndef LOADER_H
//#define LOADER_H

//#include "executablefile.h"
//#include "memory_simulator.h"
//#include "registers_simulator.h"
//#include "utils.h"
//class Loader {
//public:

///**
// * Constructor: Loader
// * Usage: Loader loader(exe_file);
// * -------------------------------
// * @brief Initialize Loader object and generate memory and register file.
// */
//    Loader(ExecutableFile exe_file);

///**
// * Method: getMemorySimulator
// * Usage: Memory_Simulator mem_sim = loader.getMemorySimulator();
// * --------------------------------------------------------------
// * @brief Return corresponding memory simulator.
// */
//    Memory_Simulator getMemorySimulator() {return mem_sim;};

///**
// * Method: getRegistersSimulator
// * Usage: Registers_Simulator regs_sim = loader.getRegistersSimulator();
// * ---------------------------------------------------------------------
// * @brief Return corresponding registers simulator.
// */
//    Registers_Simulator getRegistersSimulator() {return regs_sim;};

//private:

//    Memory_Simulator mem_sim;
//    Registers_Simulator regs_sim;

//};
//Loader::Loader(ExecutableFile exe_file) : mem_sim(0x00a00000), regs_sim(){
//    for (ExecutableFile::segment_cell cell : exe_file.text_segment) {
//        mem_sim.writeWord(cell.address, cell.data);
//    }
//    for (ExecutableFile::segment_cell cell : exe_file.data_segment) {
//        mem_sim.writeWord(cell.address, cell.data);
//    }
//    regs_sim.writeReg(28, intToBinaryString(exe_file.__data_addr)); // $gp
//    regs_sim.writeReg(29, intToBinaryString(mem_sim.getEndAddress())); // $fp
//}


//#endif // LOADER_H
