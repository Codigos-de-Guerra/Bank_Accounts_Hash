# Hash Implementation for Bank Accounts. A project for Estrutura de Dados Básicas I (EDB I)

## Introduction

This programming project implements a hash for Bank Account Management. Through information received via client, we shall be able to manage each and every account, supporting basic operations such as *inserting, consulting and removing*.

## How to compile

First of all, obviously this repository is needed to work as desired, so we must to download this repo. As we know that ```git``` is a tremendous tool for any programmer, then we must have git installed.

It is also expected for user to have installed [doxygen](https://en.wikipedia.org/wiki/Doxygen) program. This will automatically generate documentation for code. Not a necessary package to compile and run program, but it is a tool to guide user through code functions. To install `doxygen` on UBUNTU, for example:

```bash
$ sudo apt-get install doxygen
```
To compile we will use a makefile, so compilations may be more dynamic and automatic.
```bash
# Using 'git clone' to clone this repo into desired directory:
$ git clone https://github.com/Codigos-de-Guerra/Bank_Accounts_Hash.git

# Enter repo:
$ cd Bank_Accounts_Hash

# To compile the whole project and also generate documentation, insert 'make' inside root of path:
$ make

# To clean up all remaining trash data and files, such as the binary ones, insert 'make clean':
$ make clean
```

## How to execute

Now, we show how to run the program. 
```bash
# To execute program:
$ ./bank <Version>
```
- `<Version>`: Represents which Version is supossed to be utilized for viewing accounts.

### Example

Let's say you wish an simple test for Account Management, differing each account by only it's number, then should execute as:
```bash
$ ./bank 1
```

In this example 
## GitHub Repository:

*https://github.com/Codigos-de-Guerra/Bank_Accounts_Hash*

## Authorship

Program developed by [_Daniel Oliveira Guerra_](https://github.com/Codigos-de-Guerra) (*daniel.guerra13@hotmail.com*), 2018.1

&copy; IMD/UFRN 2018.
