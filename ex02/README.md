# Exercise 02 — The Job Of Your Dreams
---

## Description

A reverse-engineering exercise. It is your first day at GlobalBanksters United. A source file — `Account.cpp` — was accidentally deleted by a colleague. No Git, no backup, just a USB key with three surviving files: `Account.hpp`, `tests.cpp`, and a log file.

Your task is to reconstruct `Account.cpp` from scratch so that the program compiles and its output matches the log exactly — timestamps excluded, since those reflect the current date and time.

---

## The Three Clues

```
Account.hpp   →  tells you WHAT exists (methods, attributes)
tests.cpp     →  tells you HOW the class is used
log file      →  tells you WHAT the program must print
```

You write only `Account.cpp`. Everything else is provided and must not be modified.

---

## Reading the Log

The log is the most important clue. Each line tells you what a specific method must print. The timestamp at the beginning is always different — ignore it. Everything after it must match exactly.

### Constructor — called when an Account is created
```
index:0;amount:42;created
```
Prints the account index, its initial deposit, and the word `created`.

### Destructor — called when an Account is destroyed
```
index:0;amount:47;closed
```
Prints the account index, its final balance, and the word `closed`.

### displayAccountsInfos — global snapshot of all accounts
```
accounts:8;total:20049;deposits:0;withdrawals:0
```
Prints the total number of accounts, total money across all accounts, total deposits made, total withdrawals made.

### displayStatus — snapshot of one account
```
index:0;amount:42;deposits:0;withdrawals:0
```
Prints this account's index, current balance, number of deposits, number of withdrawals.

### makeDeposit — add money
```
index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
              ↑ before          ↑ after
```
Prints the balance BEFORE the deposit (`p_amount`), the deposited amount, the balance AFTER, and the total number of deposits on this account.

### makeWithdrawal — remove money (two possible outcomes)
```
index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1   ← success
index:0;p_amount:47;withdrawal:refused                           ← not enough funds
```
If the withdrawal amount exceeds the current balance, it is refused and nothing changes.

---

## Static Members — the key concept

The class tracks two kinds of data:

```
Per-account data (normal attributes):
  _amount         →  each account has its own balance
  _nbDeposits     →  each account counts its own deposits

Global data (static attributes — shared by ALL accounts):
  _nbAccounts         →  how many accounts exist right now
  _totalAmount        →  sum of all balances
  _totalNbDeposits    →  sum of all deposits ever made
  _totalNbWithdrawals →  sum of all withdrawals ever made
```

Visually:
```
account0 → _amount=47,   _nbDeposits=1  ─┐
account1 → _amount=785,  _nbDeposits=1  ─┼──→  _nbAccounts = 8
account2 → _amount=864,  _nbDeposits=1  ─┘     _totalAmount = 12442
...                                             _totalNbDeposits = 8
```

Static variables must be **defined** in the `.cpp` file, outside the class body:
```cpp
int Account::_nbAccounts        = 0;
int Account::_totalAmount       = 0;
int Account::_totalNbDeposits   = 0;
int Account::_totalNbWithdrawals = 0;
```

---

## The Timestamp

The log was generated in 1992. Your program runs today. The format is:
```
[YYYYMMDD_HHMMSS]
```

Since months and hours can be single digits, zero-padding is needed — `09` not ` 9`. This is done with `<iomanip>`:
```cpp
std::cout << std::setfill('0') << std::setw(2) << (t->tm_mon + 1);
//                ↑ pad with 0     ↑ 2 chars wide
```

Note: `tm_mon` starts from 0 (January = 0), so `+1` is needed. `tm_year` starts from 1900, so `+1900` is needed.

---

## The Refused Withdrawal

A withdrawal is refused when the requested amount is greater than the current balance:

```cpp
if (withdrawal > _amount) {
    std::cout << ";withdrawal:refused" << std::endl;
    return false;
}
```

From the log, two accounts are refused:
```
index:0 → had 47,  wanted to withdraw 321  →  321 > 47   → refused
index:5 → had 23,  wanted to withdraw 275  →  275 > 23   → refused
```

---

## Key Concepts Learned

**Static members** — one shared copy across all instances of a class, used here to track global bank statistics.

**Constructors and destructors** — the constructor assigns the account index, updates global counters, and prints the creation log. The destructor does the reverse and prints the closing log.

**Initialization list** — used in the constructor to assign `_accountIndex` before `_nbAccounts` is incremented:
```cpp
Account::Account(int initial_deposit)
    : _accountIndex(_nbAccounts),   // takes current value BEFORE increment
      _amount(initial_deposit),
      _nbDeposits(0),
      _nbWithdrawals(0)
{
    _nbAccounts++;
    _totalAmount += initial_deposit;
    // ...
}
```

**Log-driven development** — reading an output log and working backwards to reconstruct the code that produced it.

**Zero-padded output with `<iomanip>`:**
```cpp
std::setfill('0') << std::setw(2) << value
```

---

## Output Example

```
[20260530_010903] index:0;amount:42;created
[20260530_010903] index:1;amount:54;created
...
[20260530_010903] accounts:8;total:20049;deposits:0;withdrawals:0
[20260530_010903] index:0;amount:42;deposits:0;withdrawals:0
...
[20260530_010903] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
...
[20260530_010903] index:0;p_amount:47;withdrawal:refused
[20260530_010903] index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1
...
[20260530_010904] accounts:8;total:12442;deposits:8;withdrawals:6
...
[20260530_010904] index:0;amount:47;closed
...
```

The timestamps will differ from the original log — that is expected and correct.

---

## How to Compile and Run

```bash
make       # compile
./account  # run
make fclean
```

**Compilation flags:**
```
-Wall -Wextra -Werror -std=c++98
```

---

## File Structure

```
ex02/
├── Makefile
├── Account.hpp    → provided, do not modify
├── Account.cpp    → the file you reconstruct
└── tests.cpp      → provided, do not modify
```
