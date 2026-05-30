# Exercise 00 — Megaphone
---

## Description

A warm-up exercise to get comfortable with C++ basics. The program takes words from the command line and prints them in uppercase. If no arguments are given, it prints a feedback noise message instead.

The goal is to make the transition from C to C++ output — replacing `printf` with `std::cout` and learning how command-line arguments work.

---

## How it Works

```bash
./megaphone "hello world"
# HELLO WORLD

./megaphone Damnit " ! " "Sorry students"
# DAMNIT ! SORRY STUDENTS

./megaphone
# * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

---

## The Logic

The program receives its input through `argc` and `argv`:

```
argc  →  how many arguments were typed (the program name counts as 1)
argv  →  array of strings containing each argument

./megaphone hello world
argc = 3
argv[0] = "./megaphone"
argv[1] = "hello"
argv[2] = "world"
```

If `argc == 1`, only the program name was typed — no arguments — so the noise message is printed.

Otherwise, the program loops through every argument (starting from index 1 to skip the program name), and for each argument loops through every character, converting it to uppercase with `std::toupper`.

```cpp
for (int i = 1; i < argc; i++) {         // each argument
    for (int j = 0; argv[i][j]; j++) {   // each character
        std::cout << (char)std::toupper(argv[i][j]);
    }
    if (i < argc - 1)
        std::cout << " ";                 // space between words
}
std::cout << std::endl;
```

### Why does the inner loop stop automatically?

In C and C++, every string ends with a special character `'\0'` (null terminator) whose numeric value is `0`. Since `0` is treated as `false` in a condition, the loop stops as soon as it reaches it — no need to know the length in advance.

```
argv[1] = ['h']['e']['l']['l']['o']['\0']
                                     ↑
                               value 0 → loop stops
```

### What does `std::toupper` do?

It converts a single character to its uppercase version. It comes from `<cctype>` (the C++ version of C's `<ctype.h>`).

```
'h' → 'H'
'3' → '3'   (digits are unchanged)
'!' → '!'   (symbols are unchanged)
```

---

## Key Concepts Learned

**`std::cout` instead of `printf`:**
```cpp
std::cout << "Hello" << std::endl;
```

**Command-line arguments:**
```cpp
int main(int argc, char **argv)
//        ↑ count   ↑ array of strings
```

**Iterating over a string character by character:**
```cpp
for (int j = 0; argv[i][j]; j++)
//              ↑ stops at '\0' automatically
```

**`std::toupper` from `<cctype>`:**
```cpp
(char)std::toupper(argv[i][j])
```

---

## How to Compile and Run

```bash
make            # compile
./megaphone     # run with no arguments
./megaphone hi  # run with arguments
make fclean     # clean everything
```

**Compilation flags:**
```
-Wall -Wextra -Werror -std=c++98
```

---

## File Structure

```
ex00/
├── Makefile
└── megaphone.cpp
```
