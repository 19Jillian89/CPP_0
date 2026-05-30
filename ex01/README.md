# Exercise 01 — My Awesome PhoneBook

---

## Description

A command-line phonebook application inspired by 80s technology. The program runs in a loop and accepts three commands: `ADD`, `SEARCH`, and `EXIT`. It is built entirely using two custom classes — `Contact` and `PhoneBook` — with no dynamic memory allocation and no STL containers.

The goal of this exercise is to understand the fundamentals of object-oriented programming in C++: how to design classes, separate private data from public methods, and make two classes work together.

---

## How it Works

At startup the phonebook is empty. The user is prompted to enter a command:

```
ADD     → add a new contact (5 fields, none can be empty)
SEARCH  → display the contact list, then show details of one entry
EXIT    → quit the program (all contacts are lost)
```

Any other input is silently ignored and the program waits for the next command.

---

## The Two Classes

### Contact
Represents a single phonebook entry. It stores five fields, all private. The only way to read or write them is through public getter and setter methods — this is the principle of **encapsulation**.

```
Contact
│
├── private
│   ├── _firstName
│   ├── _lastName
│   ├── _nickname
│   ├── _phoneNumber
│   └── _darkestSecret
│
└── public
    ├── setFirstName()      setLastName()      setNickname()
    ├── setPhoneNumber()    setDarkestSecret()
    ├── getFirstName()      getLastName()      getNickname()
    └── getPhoneNumber()    getDarkestSecret()
```

Why private? Because no code outside the class should be able to write `contact._firstName = ""` directly. Every modification passes through a method, where validation can be applied.

### PhoneBook
Holds an array of up to 8 contacts and a counter tracking how many have been added. It exposes two methods: one to add a contact and one to search.

```
PhoneBook
│
├── private
│   ├── _contacts[8]    fixed-size array, no dynamic allocation
│   └── _count          total number of contacts added so far
│
└── public
    ├── PhoneBook()       constructor — initializes _count to 0
    ├── addContact()
    └── searchContact()
```

---

## The Circular Buffer

The phonebook stores a maximum of 8 contacts. When a 9th is added, it overwrites the oldest one. This is achieved with the modulo operator `%`:

```cpp
index = _count % 8;
```

`%` gives the remainder of a division. Dividing by 8 always produces a result between 0 and 7:

```
_count = 0  →  0 % 8 = 0  →  slot 0
_count = 1  →  1 % 8 = 1  →  slot 1
...
_count = 7  →  7 % 8 = 7  →  slot 7
_count = 8  →  8 % 8 = 0  →  slot 0  ← overwrites the first contact!
_count = 9  →  9 % 8 = 1  →  slot 1  ← overwrites the second contact!
```

The array never grows — it wraps around like a clock.

---

## The ADD Command

The user is prompted for each field one at a time. If any field is left empty, the operation is cancelled and the contact is not saved.

```
First name: Mario
Last name: Rossi
Nickname: Macio
Phone number: 3331234567
Darkest secret: eats pineapple pizza
```

---

## The SEARCH Command

First, all saved contacts are displayed as a formatted table — 4 columns, each exactly 10 characters wide, right-aligned, separated by `|`. If a name is longer than 10 characters, it is truncated: the first 9 characters are shown followed by a dot.

```
     Index|     First|      Last|  Nickname|
         0|     Mario|     Rossi|     Macio|
         1|Alessandro|    Verdi.|  Pallina.|
                          ↑            ↑
                     fits exactly   truncated (was "Pallinetta")
```

Truncation rule:
```
"Rossi"       (5 chars)  →  "Rossi"      no change needed
"Alessandro"  (10 chars) →  "Alessandro" fits exactly
"Alessandros" (11 chars) →  "Alessand."  first 9 + dot
```

Then the user is asked for an index. If valid, the full details of that contact are printed one field per line:

```
First name:     Mario
Last name:      Rossi
Nickname:       Macio
Phone number:   3331234567
Darkest secret: eats pineapple pizza
```

If the index is out of range or not a number, an error message is shown.

---

## Key Concepts Learned

**Encapsulation** — private data, public interface. Nobody touches `_firstName` directly; they go through `setFirstName()` and `getFirstName()`.

**Two collaborating classes** — `PhoneBook` does not inherit from `Contact`. It simply contains an array of them. This is called *composition*.

**Stack allocation** — `Contact _contacts[8]` lives on the stack. No `new`, no `delete`, no memory leaks.

**Input validation** — empty fields are rejected before the contact is saved.

**Formatted output with `<iomanip>`:**
```cpp
std::cout << std::setw(10) << std::right << text << "|";
//            ↑ column width   ↑ alignment
```

**Circular buffer** — `index = _count % 8` keeps the index always between 0 and 7.

---

## How to Compile and Run

```bash
make        # compile
./phonebook # run
make fclean # clean everything
```

**Compilation flags:**
```
-Wall -Wextra -Werror -std=c++98
```

---

## File Structure

```
ex01/
├── Makefile
├── main.cpp         → program loop: ADD / SEARCH / EXIT
├── Contact.hpp      → class declaration
├── Contact.cpp      → getters and setters
├── PhoneBook.hpp    → class declaration
└── PhoneBook.cpp    → addContact and searchContact logic
```
