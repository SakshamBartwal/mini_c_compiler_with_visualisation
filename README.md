# Multi-File Mini C Compiler with Visualization

A custom multi-file mini-compiler for a subset of the C programming language built using Flex and Bison.

This project aims to simulate the architecture of real-world compilers like GCC by supporting:
- multi-file compilation
- scoped semantic analysis
- symbol resolution
- TAC generation
- CFG visualization
- interactive compiler phase visualization

---

# Features

## Frontend
- Lexical Analysis using Flex
- Syntax Analysis using Bison
- Recursive grammar parsing
- Import statement support

## Semantic Analysis
- Scoped symbol tables
- Duplicate declaration detection
- Undeclared variable detection
- Global/local scope resolution
- Function-level scope handling
- Parameter tracking
- Shadowing support

## Planned Features
- AST generation
- Three Address Code (TAC)
- Control Flow Graph (CFG)
- Intermediate code optimization
- Interactive web-based visualization UI

---

# Tech Stack

## Compiler Core
- C
- Flex
- Bison

## Visualization UI
- React
- Node.js
- Express

---

# Current Architecture

## Global Symbol Table
Stores:
- global variables
- functions
- imports

## Per-Function Symbol Tables
Each function maintains:
- parameters
- local variables

This architecture supports:
- shadowing
- scope isolation
- semantic resolution

---

# Build Instructions

```bash
make

./compiler < test.c

# Output
Starting compilation...

Variable declared: x

Function defined: main

Compilation finished.