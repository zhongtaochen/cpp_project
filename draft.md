## **Introduction**

In this programming project, an integrated development environment (IDE) is designed and implemented for users to edit and run simple MIPS32 programs. To follow the real process of transforming an assembly program in a file on disk into a program running on a computer, the IDE embeds **assembler**, **linker**, **loader** and **simulator**. Furthermore, to provide users ease of programming, graphical user interface (GUI) **editor** and **debugger** are designed.

The proposal is organized the following: the related work we referred to is introduced in section 2; section 3 elaborates our solution; finally, are specified in section 4 and 5. No major modification needs to be specifically illustrated compared with the proposal.

------



## **Related Work**

Most knowledge about assembler, linker, loader and simulator are obtained from the well-known *Patterson and Hennessy*'s book [1]. Additionally, pseudo code conversion refers to online resources [8]. Furthermore, lexical analysis from the theories of compilers [2] may be incorporated in the implementation of the assembler. Moreover, systematic knowledge about GUI programming mainly comes from tutorials on Qt [3]. Additionally, contents from the Internet have been of great help [4] [5] [6] [7]. We consider the current resources to be sufficient for implementing the whole project, therefore the illustration of accessing further resources is omitted here.

------



## Our Work

### Highlights

Compared with the naive version of MIPS assembler and simulator project implemented in the course CSC3050, our project improves in the following aspects:

- Integrated graphical interface

  For the purpose of focusing on writing assembly code rather than interacting with the console, a user-friendly graphical interface is designed to integrate all key components.

- Pseudo instructions support

  Supporting pseudo instructions rescues assembly programmers from troublesome address calculations, and improves the readability of the assembly code significantly.

- Linking multiple files support

  In order to prevent single tediously lengthy script, we introduce the static linking stage to support writing an assembly project.

- Assembly debugger

  A simple assembly debugger is implemented for users to work around with specific lines of code and watch values of registers.

Aside from these functions, the implementing process follows strict unit testing scheme (test files provided). Furthermore, we commit to formatted code style and generate detailed document with the help of software Doxygen.



### Implementation

#### Editor

- Open , Remove and Save

- Find  

- Run and Debug


When `Run ` or `Debug ` button is clicked, corresponding functions in `Assembler`, `Linker`, `Loader`, `Simulator` or `Debugger` class, such as  `assemble()`,  `simulate()`, `debug()` will be called to set the classes with the opened files.

Our GUI is connected the terminal of Qt, and `QTextStream`  is used so that the output and input of the program will be accomplished in the terminal of Qt.

When debugging the files, we create another block named `TextSegment` and utilize `QTableWidget`  to display the final MIPS instructions. Checkbox of `QTableWidget` is used to represent breakpoints, which makes our implementation much easier than doing real breakpoints. After this, users need to click `step` or `to_next_breakpoint` button, and then the corresponding information of `Registers` will be shown in `Autos`.

As illustrated in our highlights, our project supports static linking, so that users can run and debug multiple assembly files and write a project, given that these files are already opened.



#### Assembler

- Data Section

In this project, the assembler supports the following keywords: `.ascii`, `.asciiz`, `.byte`, `.half`, `.word`, `.space`. The basic idea is to utilize regular expression to split code into tokens and then perform further operations. For example, `str: .asciiz "Hello World"` will be converted into `{"str", ".asciiz", "Hello World"}`. Then, update the symbol table. Afterwards, identify the keyword and read char or number respectively into the `ObejctFile`.

- Pseudo Code Conversion

Supported pseudo instructions are attached in Appendix.

The conversion is based on the integration of external references and our understanding of MIPS instructions. It is mainly implemented in text processing scheme. For example, pseudo code "`mul $d, $s, $t`" is replaced by two real instructions "`mult $s, $t`" and "`mflo $d`". After the conversion, the assembler processes real instructions exactly the same as before. Thus, the pseudo code conversion can be viewed as part of the preprocessing on input files.

Pseudo instruction `la` is a troublemaker as it involves absolute address. Here follows our solution. Firstly, convert `la $t, A` to `lui $t, A` and `ori $t, $t, A`. Notice that the immediate part in original I-type instruction is now a label. Then `LineAssembler` would update relocation information and linker completes solving the issue.

- Text Section

Supported instructions are attached in Appendix.

Handling text section requires preprocessing, catching labels and converting pseudo code in advance. After that, we have obtained comment-free instructions indexed by relative addresses. Then we assembles instructions line by line. Here we encapsulates line assembling by `LineAssembler` class. The `LineAssembler` object further calls `R_LineAssembler`, `I_LineAssembler` or `J_LineAssembler` according to the instruction type. The purpose of designing the super class `LineAssembler` is to provide common toolkits like returning the index of the register. Additionally, three subclasses overwrites the assemble function according to the format of the instruction. Here follows the UML diagram illustrating the hierarchy.

<img src="C:\Users\40455\Desktop\test\Inheritance.jpg" alt="Inheritance" style="zoom: 50%;" />



#### Linker

Linker takes multiple `ObjectFile` objects as input and handles unresolved references to produce one `ExecutableFile` in static linking scheme. When linker goes through each `ObjectFile`,  `curr_text_addr` is recalculated by adding up the starting address of the text section and current `text_size` of the `ExecutableFile`. In this way, the starting address for saving text segment of each `ObjectFile` is tracked, and then the absolute address of the text segment can be calculated by adding up `curr_text_addr` and the relative address saved in `ObjectFile`. Calculating the absolute address of data segment follows a similar procedure. After that, we are ready to go through the `relocation_info` in each `ObjectFile` and handle unresolved references, as the symbol table is now updated with absolute addresses. When dealing with J-type instructions, the relative address of the target instruction with respect to program counter (PC) is calculated and saved. When dealing with I-type instructions, the relative address of the target data with respect to the starting address of the data section is calculated and saved.



#### Loader

Loader takes an `ExecutableFile` as input. Loader firstly copies instruction and data to the memory simulator. Then loader initializes register file `$gp` to the starting point of data segment in the memory, and register file `$fp` to the end address of the memory. Later loader provides the starting reference of the text section to the program counter, and transfers the control for executing.



#### Simulator

- Memory Simulator

Memory in a computer stores information in binary format. The structure of the memory could be seen as either sequential blocks of data or address-indexed table. Considering that addresses take consecutive integer values, map is no longer superior in accessing values in this case, thus array data structure would be more appropriate. More specifically, bytes are the minimal units in MIPS instruction set architecture, thus memory could be characterized as an 8-digit-binary array.

To represent such a binary, both `uint8_t` and `string` object would work. Although `string` object may be advantageous in displaying value while debugging and segmenting, `uint8_t` object occupies much less space and supports direct arithmetic and logical operation, which is therefore closer to the hardware interpretations. Thus, in the project, the `MemorySimulator` class encapsulates a fixed-size (6 MB in default setting would be enough, wherein 1 MB for the text section) `uint8_t` array and provides I/O interface for clients like `writeWord` and `readWord`.

- Processor Simulator

In the project, we only implement part of the central processor unit (CPU) in a naive scheme. Different from the implementation from the hardware perspective, our implementation may be concluded as a single cycle processor and only focuses on the top level abstractions like fetching instructions and performing operations with register files and memory, i.e., low level components like adder is not considered but is rather implemented with direct calling of the adder in C++.

More specifically, to simulate the behaviors of CPU, in one machine cycle, `Simulator` object interprets the binary code as a MIPS assembly instruction at the address specified by PC, and executes the instruction. It supports all instructions excluding those related to FPU (see Appendix), and a minimal set of operating system services (called by `syscall` instruction, see Appendix) to communicate with users. Additionally, for trap, simulator would simply print the exception information with current PC address.

Regarding the simulator for register files in CPU, the `RegisterFilesSimulator` class encapsulates an `uint8_t` array of fixed size 34 (32 register files, `LO` and `HI` in multiply/divide unit) to keep track of values in register files and provides I/O interface for clients similar to `MemorySimulator`.



#### Debugger

A simple debugger is implemented in this IDE. The debugger graphical interface displays MIPS assembly instruction associated with corresponding address in the text section, and receives information of breakpoints specified by users through the interface. It also supports `step` (goto the next line) and `run` (goto the next breakpoint) function (`step into` or `step out` is not necessary for assembly language). Furthermore, the values of register files would be shown aside as well.

What worth noticing is that in implementing `Debugger` and `Simulator` class, the common behavior, executing the binary code, is designed to be handled by a super class `Executor`. The `Executor` class could be interpreted as an one-line executor interface, while `Debugger` and `Simulator` class extends the super class in the following way: a `Debugger` object maintains a set recording breakpoints and executing one single line (`step`) or until a breakpoint is met (`run`), according to the client's need; a `Simulator` simply executes line by line until the program exits. Additionally, adding or removing breakpoints requires only trivial set manipulation.

---



## Contribution

| Work                                           | Team Members                                     |
| ---------------------------------------------- | ------------------------------------------------ |
| Graphical Interface                            | Xiao Jie, Shu Ningyi, Qu Yahui                   |
| Assembler, Linker, Loader, Simulator, Debugger | Shen Kunshuo, Ma Ruofei, Qu Yahui, Chen Zhongtao |

---





## Reflections





---





## **Reference**

> [1] Patterson, D. A., & Hennessy, J. L. (2019). *Computer organization and design: the hardware/software interface*. Brantford, Ontario: W. Ross MacDonald School Resource Services Library.
>
> [2] Aho, A. V., Lam, M. S., Sethi, R., & Ullman, J. D. (2015). *Compilers: principles, techniques, and tools*. India: Pearson India Education Services.
>
> [3] Blanchette, J., Summerfield, M., & Ettrich, M. (2008). *C++ Gui Programming with Qt4*. Upper Saddle River: Prentice Hall in association with Trolltech Press.
>
> [4] Real Python. (2018, December 15). Thonny: The Beginner-Friendly Python Editor. Retrieved from https://realpython.com/python-thonny/#the-user-interface.
>
> [5] Tomassetti, F. (2019, July 22). How to create an editor with syntax highlighting for your language using ANTLR and Kotlin. Retrieved from https://tomassetti.me/how-to-create-an-editor-with-syntax-highlighting-dsl/.
>
> [6] Qscitinlla. Retrieved from https://www.cnblogs.com/pinking/p/7788447.html.
>
> [7] Syntax Highlight Guide. Retrieved from https://code.visualstudio.com/api/language-extensions/syntax-highlight-guide.
>
> [8] MIPS pseudo instructions-abs. Retrieved from https://blog.csdn.net/wzb56_earl/article/details/6798791.



<div STYLE="page-break-after: always;"></div>

## Appendix

Table of supported instructions (63 instructions):

| Assembly          | Instruction                                      |
| ----------------- | ------------------------------------------------ |
| add rd, rs, rt    | Add                                              |
| addu rd, rs, rt   | Add unsigned                                     |
| addi rd, rs, imm  | Add immediate                                    |
| addiu rd,rs,imm   | Add immediate unsigned                           |
| and rd, rs, rt    | Bitwise and                                      |
| andi rt, rs, imm  | Bitwise and immediate                            |
| beq rs, rt, label | Branch on equal                                  |
| bgez rs, offset   | Branch on greater than or equal to zero          |
| bgezal rs, offset | Branch on greater than or equal to zero and link |
| bgtz rs,offset    | Branch on greater than zero                      |
| blez rs, offset   | Branch on less than or equal to zero             |
| bltz rs, offset   | Branch on less than zero                         |
| bltzal rs, offset | Branch on less than zero and link                |
| bne rs, rt, label | Branch on not equal                              |
| div rs, rt        | Divide                                           |
| divu rs, rt       | Divide unsigned                                  |
| j addr            | Jump                                             |
| jal addr          | Jump and link                                    |
| jalr rd, rs       | Jump register and link                           |
| jr rs             | Jump register                                    |
| lb rd, offset     | Load byte                                        |
| lbu rd, offset    | Load byte unsigned                               |
| lh rd, offset     | Load halfword                                    |
| lhu rd, offset    | Load halfword unsigned                           |
| lw rd, offset     | Load word                                        |
| mfhi rd           | Move from HI                                     |
| mflo rd           | Move from LO                                     |
| mthi rs           | Move to HI                                       |
| mtlo rs           | Move to LO                                       |
| mult rs, rt       | Multiply                                         |
| multu rs, rt      | Multiply unsigned                                |
| nor rd, rs, rt    | Bitwise nor                                      |
| or rd, rs, rt     | Bitwise or                                       |
| ori rd, rs, imm   | Bitwise or immediate                             |
| sb rs, offset     | Store byte                                       |
| sh rs, offset     | Store halfword                                   |
| sll rd, rs, shift | Shift left logical                               |
| sllv rd, rs, rt   | Shift left logical variable                      |
| slt rd, rs, rt    | Set on less than signed                          |
| slti rd, rs, imm  | Set on less than immediate signed                |
| sltiu rd, rs, imm | Set on less than immediate unsigned              |
| sltu rd, rs, rt   | Set on less than unsigned                        |
| sub rd, rs, rt    | Subtract                                         |
| subu rd, rs, rt   | Subtract unsigned                                |
| sra rd, rs, shift | Shift right arithmetic                           |
| srav rd, rs, rt   | Shift right arithmetic variable                  |
| srl rd, rs, shift | Shift right logical                              |
| srlv rd, rs, rt   | Shift right logical variable                     |
| sw rs, offset     | Store word                                       |
| teq rs rt         | Trap if equal                                    |
| teqi rs, imm      | Trap if equal immediate                          |
| tge rs, rt        | Trap if greater than or equal                    |
| tgei rs, imm      | Trap if greater than or equal immediate          |
| tgeiu rs, imm     | Trap if greater than or equal immediate unsigned |
| tgeu rs, rt       | Trap if greater than or equal unsigened          |
| tlt rs, rt        | Trap if less than                                |
| tlti rs, imm      | Trap if less than immediate                      |
| tltu rs, rt       | Trap if less than unsigned                       |
| tltiu rs, imm     | Trap if less than immediate unsigned             |
| tne rs, rt        | Trap if not equal                                |
| tnei rs, imm      | Trap if not equal immediate                      |
| xor rd, rs, rt    | Bitwise exclusive or                             |
| xori rd, rs, imm  | Bitwise exclusive or immediate                   |

Table of supported pseudo instructions (22 instructions):

| Assembly         | Pseudo Instruction               |
| ---------------- | -------------------------------- |
| abs $d, $s       | absolute value                   |
| b C              | branch unconditionally           |
| bal C            | branch unconditionally and link  |
| beq $t, V, C     | branch if equal to immediate     |
| beqz $s, C       | branch if zero                   |
| bge $s, $t, C    | branch if greater than or equal  |
| bgt $s, $t, C    | branch if greater than           |
| bgtu $s, $t, C   | branch if greater than unsigned  |
| ble $s, $t, C    | branch if less than or equal     |
| blt $s, $t, C    | branch if less than              |
| bne $t, V, C     | branch if not equal to immediate |
| clear $t         | clear                            |
| div $d, $s, $t   | quotient                         |
| la $t, A         | load label address               |
| li $t, C         | load 32-bit immediate            |
| move $t, $s      | move                             |
| mul $d, $s, $t   | multiply and return              |
| mulou $d, $s, $t | unsigned multiply and return     |
| not $t, $s       | not                              |
| nop              | nop                              |
| rem $d, $s, $t   | remainder                        |
| remu $d, $s      | unsigned remainder               |

Table of supported `syscall`.

| Service      | System call code | Arguments                                               | Result                       |
| ------------ | ---------------- | ------------------------------------------------------- | ---------------------------- |
| print_int    | 1                | `$a0` = integer                                         |                              |
| print_string | 4                | `$a0` = string                                          |                              |
| read_int     | 5                |                                                         | integer (in `$v0`)           |
| read_string  | 8                | `$a0` = buffer, `$a1` = length                          |                              |
| sbrk         | 9                | `$a0` = amount                                          | address (in `$v0`)           |
| exit         | 10               |                                                         |                              |
| print_char   | 11               | `$a0` = char                                            |                              |
| read_char    | 12               |                                                         | char (in `$v0`)              |
| open         | 13               | `$a0` = filename (string)                               | file descriptor (in `$a0`)   |
| read         | 14               | `$a0` = file descriptor, `$a1` = buffer, `$a2` = length | num chars read (in `$a0`)    |
| write        | 15               | `$a0` = file descriptor, `$a1` = buffer, `$a2` = length | num chars written (in `$a0`) |
| close        | 16               | `$a0` = file descriptor                                 |                              |

