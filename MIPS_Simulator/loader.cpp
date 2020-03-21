#include "loader.h"
#include "utils.h"

Loader::Loader(ExecutableFile exe_file) : mem_sim(0x00a00000), regs_sim(){
    for (ExecutableFile::segment_cell cell : exe_file.text_segment) {
        mem_sim.writeWord(cell.address, cell.data);
    }
    for (ExecutableFile::segment_cell cell : exe_file.data_segment) {
        mem_sim.writeWord(cell.address, cell.data);
    }
    regs_sim.writeReg(28, intToBinaryString(exe_file.__data_addr)); // $gp
    regs_sim.writeReg(29, intToBinaryString(mem_sim.getEndAddress())); // $fp
}
