# ctg
C Turtle Graphics Interpreter

# Why?
Learning purposes.

Every kind of helpful feedback will be greatly appreciated.
:)

---

# Files
## *.c files
### [main.c](main.c)
- Actual implementation of turtle graphics.
### [libturtlef.c](libturtlef.c)
- Main engine functions taking care of execution.

## *.h files
### [libturtle.h](libturtle.h)
- Main engine header file, containing macros, data type defs API functions.
### [bitman.h](bitman.h)
- Contains bit manipulation macros.

---

# How to use
1. Compile with (for more details look into [makefile](makefile))
`make`
1. Execution
- Execute file:
`./ctg <file path>`
- Execute stdin/piped input:
`./ctg`
