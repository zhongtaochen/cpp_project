# cpp_project



## Naming Convention

Class: `Assembler`, `ObjectFile`. Noun with all words that start with a capital letter.

Function: `writeFile()`. Start with lower case letter with capital letter for each word afterwards.

Variable: `text_size` or `textsize`. Better to be something meaningful. Do not worry about the length of the name. If longer name helps understanding, use the longer one.

Constant: `START_ADDRESS`. Capitalize all.



## Comments

Doxygen: http://www.doxygen.nl/. Auto doc generator for C++.



File:

```cpp
/**
 * @file executablefile.h
 * @brief <code>ExecutableFile</code> class
 * @details This file exports an <code>ExecutableFile</code> class,
 * adapting from the descriptions in Patterson and Henessy's book section 2.12.
 */
```



Class:

```cpp
/**
 * @brief Output of designed <code>Linker</code> in this project.
 * Records neccessary information for further simulating and debugging.
 */
```



Function/Method:

```cpp
/**
 * @brief Void initilizer for the <code>ExecutableFile</code> class.
 * All attributes are public.
 */
```



//TODO determine what to fill in the @brief and @details.