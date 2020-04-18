[TOC]

<div STYLE="page-break-after: always;"></div>

## 1. **Introduction**

In this programming project, an integrated development environment (IDE) is designed for users to edit and run simple MIPS32 programs. To follow the real process of transforming an assembly program in a file on disk into a program running on a computer, the IDE embeds **assembler**, **linker**, **loader** and **simulator**. Furthermore, to provide users ease of programming, graphical user interface (GUI) **editor** and **debugger** are designed. The highlighted features may include **embedding all essential toolkits for an IDE** and **supporting pseudo MIPS instructions**. 

The proposal is organized the following: the related work we referred to is introduced in section 2; section 3 elaborates our solution; finally, time schedule and work distribution is specified in section 4 and 5.

------



## 2. **Related Work**

Most knowledge about assembler, linker, loader and simulator are obtained from the well-known *Patterson and Hennessy*'s book [1]. Furthermore, lexical analysis from the theories of compilers [2] may be incorporated in the implementation of the assembler. Moreover, systematic knowledge about GUI programming mainly comes from tutorials on Qt [3]. Additionally, contents from the Internet have been of great help [4] [5] [6] [7]. We consider the current resources to be sufficient for implementing the whole project, therefore the illustration of accessing further resources is omitted here.

------



## 3. **Our Work**
### 3.1. Editor

In this project, we propose to embed a screen editor which allows users to access the cursor on the screen and perform `copy`, `cut`, `paste` operation easily. To achieve this aim, we will create a complete GUI application based on Qt, which contains menus, toolbars, document windows, a status bar, dialogs, and underlying functionality. The structure is presented in the following chart:

<img src="C:\Users\40455\OneDrive\IMG_3045.PNG" alt="IMG_3045" style="zoom:25%;" />



Detailed GUI **layout design** (subject to change) is illustrated as follow:

- **Code Editor and Shell**

  When the project is launched, a window with several icons across the top will show up, along with one white block on the left, and two white panels on the right:

  <img src="C:\Users\40455\AppData\Roaming\Typora\typora-user-images\image-20200326223838854.png" alt="image-20200326223838854" style="zoom: 67%;" />

  On the left of the window, there is a file list, which specifies assembly code files to be assembled and linked. On the right, there are two main sections. The top section is the code editor, where users writes MIPS32 program. The bottom half is the shell, which shows the output of the program.

- **Icons**

  Across the top shows the following icons.

  <img src="C:\Users\40455\AppData\Roaming\Typora\typora-user-images\image-20200326223856802.png" alt="image-20200326223856802" style="zoom: 67%;" />

  - The `paper` icon is used to create a new file.

  - The `open` icon is used to open a file existed in the disk.

  - The `save` icon is used to save the codes.

  - The `play` icon is used to run the program.

  - The `debug` icon is used to debug the program.

  - The `stop` icon is used to stop running the code.

- **Debug panel**

  Pressing the `debug` icon, two additional panels will be shown. The left one displays address-instruction pair in the text section in the memory. The right one shows values in register files. We may also let these two panels stay on the screen from the very beginning.

  <img src="C:\Users\40455\AppData\Roaming\Typora\typora-user-images\image-20200326223928148.png" alt="image-20200326223928148" style="zoom:80%;" />



If time permits, we will also implement the following appealing features:

- **Syntax highlighting:** we shall implement functions such as bracket matching to make it convenient for programmers to see whether a brace has been left out or locate the match of the brace the cursor is on by highlighting the pair in a different color. Thus, it would significantly improve the readability of the codes and the productivity of the programmers.

- **Options to change theme:** we will try to provide a variety of stylish themes with unique color palettes for users to choose, such as `Atom One Light`, `Dark`, `Color`.



### 3.2. Object File & Executable File

Before illustrating detailed assembling process, we would like to introduce two file formats: object file and executable file, which play a fundamental rule in the project.

An object file consists of a header, a text segment, a data segment, a relocation information segment and a symbol table. In the header, name, text size and data size are specified. Text segment and data segment keeps track of binaries with their corresponding addresses, leaving label dependent instruction unresolved. Relocation information segment records information of unresolved addresses, including the address, instruction type and label dependency. The symbol table demonstrates label dependencies and leaves blank for their absolute addresses. An executable file, on the other hand, consists of a header, a text segment and a data segment. Text size and data size are specified in the header. Text segment and data segment now record binaries with their absolute address in the memory.

In this project, structured classes `ObjectFile` and `ExecutableFile` are defined to characterize object files and executable files. In order to simulate real assembling process, after the assembler generates an `ObjFile` object, the program may serialize the object into a file (either utilize existed library or simply generate text file recording necessary information) for future recovery to avoid repeated assembling of the same assembly code file.



### 3.3. Assembler

Assembler translates one single assembly program and outputs as an `ObjectFile`. A MIPS32 program mainly consists of two parts: data section (specified by keyword `.data`) and text section (`.text`). In either part, each line of code is independent of the next line of code and forms clear structure, which offers great convenience for the design of assembler. In this project, the IDE supports assembling assembly code file with data section and supports necessary pseudo MIPS instructions. Here we demonstrate two solutions for the implementation.

The first solution utilizes regular expression along with string manipulation. The assembler scans through the file and updates the symbol table to keep track of labels. In the second pass, to utilize the independence of separate line of codes, the assembler handles the MIPS32 program line by line. More specifically, in text section, with `split` and `trim` function easily deduced from the regular expression library, a typical instruction `add $s0, $s1, $s2 # add` can be converted into tokens `{"add", "$s0", "s1", "s2"}` with comment ignored. The assembler then identifies the type of the instruction (either R-type, I-type or J-type) according to the instruction code, determines the correspondence of each token to the field (e.g. in R-type instruction, `rs`, `rt`, `rd` or `shamt`), translate each token based on the type of the operand (either register, immediate or label) and complete line assembling by filling up fields with translations. Notice that any instruction involving absolute referencing is left unresolved for the linker to solve. For the data section, the assembler follows similar procedure, including generating tokens and translating, with extensive use of functions provided by string library, like `find` and `substr`.

The second solution is inspired by the theories of compilers. Although the compiler is not planned to be implemented in this project, great ideas from lexical analysis may be incorporated in the design of the assembler. More specifically, consider the same exact instruction `add $s0, $s1, $s2 # add`, from a new point of view, tokens now are designed to include more information `{<"add", keyword>, <"$s0", reg>, <",", comma>, <"$s1", reg>, <",", comma>, <"s2", reg>}`. To realize such functionality, deterministic finite automaton based lexer scans each character sequentially, ignores ineffective blank characters and comments, determines the state according to the character and generate tokens. Following the tokenization, translation to machine code is simple as illustrated above. For the data section, consider one typical line of assembly code, `str1: .asciiz "Hello, world."`, tokens may be generated as `{<"str1", label>, <":", colon>, <"asciiz", keyword>, <""", quote>, <"Hello, world", string literal>, <""", quote>}`. (`keyword` specification may further modified to more detailed specification like `keyword_data_type`, details omitted here)

Comparing the above solutions, the first one is more straightforward and easier to implement. Unlike the first solution treats the text section and data section quite differently, the second solution assembles both sections in one unified framework, which improves extensiveness to more keywords (like `.align` etc. which we do not intend to support in this project). Moreover, the second solution may identify bracket mismatch or naming error, while the first solution may crash if such exceptions exist. Attempts to implementing the second solution will be made. However, there is no guarantee that the work would be accomplished. Once such attempts fail, we would turn to implement the baseline solution. 



### 3.4. Linker

`ObjectFile` objects produced by the assembler cannot be loaded directly by the loader because labels are left unresolved. This is where linker comes into the play. Linker takes several `ExecutableFile` objects and handles unresolved references to produce one `ExecutableFile`. The linker follows traditional **static linking** procedure and does not support dynamic linking, since the program does not aim to support importing large-scale libraries (in default setting, only 2 MB is reserved for the text section).

More specifically, in the procedure of static linking, the linker piles up text sections and data sections, calculates the absolute address for each and copies to an initialized `ExecutableFile` object. Following that, the linker scans through text section and data section, and fills in the blank of the symbol table with corresponding absolute address for each labels. Accomplishing identifying unresolved labels, the linker goes through the relocation information segment in each `ObjectFile` object and resolves the reference.



### 3.5. Loader

Loader reads an `ExecutableFile` and determines the size of memory to allocate according to the header. After that, loader copies instruction and data to the memory simulator. Then loader initializes register file `$gp` to the starting point of data segment and register file `$fp` to the end address of the memory. Later loader provides the starting reference of text section to the program counter (PC), and transfers the control to simulator for executing.



### 3.6. Simulator

- Memory Simulator

Memory in a computer stores information in binary format. The structure of memory could be seen as either sequential blocks of data or address-indexed table. Considering that the addresses take consecutive integer values, map is no longer superior in accessing values in this case, thus array data structure would be more appropriate. More specifically, bytes are the minimal units in MIPS ISA, thus memory could be characterized as an 8-digit-binary-number array. To represent such a number, both `int8_t` or `string` type would work. Although `string` object may be advantageous in displaying value while debugging and segmenting if the binary represents an instruction, `int8_t` object occupies much less space and supports arithmetic and logical operation. Therefore, in the project, the `MemorySimulator` class encapsulates a fixed-size (10 MB in default setting would be enough, wherein 2 MB for the text section) `int8_t` array and provides I/O interface for clients.

- Processor Simulator

For the design of simulator for MIPS processor units, the project may only implement simulator for part of the central processor unit (CPU), while omitting floating-point coprocessor unit and low-level arithmetic and logical unit (ALU). The project does not design low-level unit like adder, but rather assumes that the ALU has already been implemented and directly fetches arithmetic and logical operations supported by C++. Regarding the simulator for register files in CPU, the `RegisterFilesSimulator` class encapsulates an `int8_t` array of fixed size 34 (32 registers, `LO` and `HI` in multiply/divide unit) to keep track of values in register files and provides I/O interface for clients. Furthermore, to simulate the behaviors of CPU, in one machine cycle, `Simulator` object interprets binary code as instruction at address provided by PC, and executes the instruction. It supports all instructions excluding those related to FPU and a minimal set of operating system services (called by `syscall` instruction) to communicate with users. Additionally, for overflow and trap, simulator would simply print exception information with current PC address.



### 3.7. Debugger

A simple debugger is designed to be embedded in this IDE. The debugger displays MIPS assembly instruction associated with corresponding address in text section, and receives information of breakpoints specified by users through the graphical interface. It also supports step (goto the next line) and continue (goto the next breakpoint) function (step into or step out is not necessary for assembly language). Furthermore, the values of register files (including HI and LO) would be shown aside, and users could query value in memory of a specific address.

------



## 4. **Schedule**

| Time Period | Work                                        |
| ----------- | ------------------------------------------- |
| Week 10     | Header file implementation                  |
| Week 11-13  | Source file implementation                  |
| Week 14     | Code review and optimization, Documentation |

-----



## 5. **Team**

| Work                           | Team Members                           |
| ------------------------------ | -------------------------------------- |
| Editor                         | Xiao Jie, Shu Ningyi                   |
| Linker, Loader                 | Qu Yahui                               |
| Assembler, Simulator, Debugger | Shen Kunshuo, Ma Ruofei, Chen Zhongtao |

------

<div STYLE="page-break-after: always;"></div>

## 6. **Reference**

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