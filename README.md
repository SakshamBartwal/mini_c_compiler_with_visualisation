# Multi-File Mini C Compiler with Visualization

A custom multi-file mini-compiler for a subset of the C programming language built using Flex and Bison.

This project aims to simulate the architecture of real-world compilers like GCC by supporting:
- multi-file compilation via nested custom include stacks
- scoped semantic analysis and validation
- complex symbol resolution across cascading scopes
- linear Three-Address Code (TAC) generation
- Control Flow Graph (CFG) basic block partitioning
- interactive web-based visualization UI (AST, Symbols, TAC, CFG)

---

# Features

## Frontend & Parser
- Lexical Analysis using Flex
- Syntax Analysis using Bison
- Recursive grammar parsing and tree construction
- Import statement support with custom nested file tracking up to 10 layers deep

## Semantic Analysis
- Scoped symbol tables with dynamic parent-linking
- Duplicate declaration detection inside the same block frame
- Undeclared variable detection across cascading parent scopes
- Global/local scope resolution
- Function-level scope handling and parameter tracking

## Intermediate Representation & Graphing
- Abstract Syntax Tree (AST) vertical-child and horizontal-sibling processing
- Three Address Code (TAC) quadruple statement generation with unique temporary (`t0, t1`) and label (`L0, L1`) variables
- Control Flow Graph (CFG) basic block partitioning with automated leader identification
- Inter-block jump path routing tracing `true/fallthrough` and `false/jump` conditional edges

## Visualization UI
- Interactive web-based workspace driven by Monaco Editor
- Reactive node graph canvas layouts powered by React Flow
- Real-time pipeline metrics dashboard mapping memory node weights and semantic errors

---

# Tech Stack

## Compiler Core
- C
- Flex (Lexer)
- Bison (Parser)
- GNU Make

## Visualization UI
- React (Vite template)
- React Flow (Canvas layouts)
- Monaco Editor (Code entry)
- Node.js & Express (Orchestration API middleware)

---

# Project Architecture

```text
mini_c_compiler_with_visualisation/
├── compiler/
│   ├── main.c                      # Compiler toolchain coordinator
│   ├── 1_lexer/
│   │   └── lexer.l                 # Flex lexical tokenizer configurations
│   ├── 2_parser/
│   │   └── parser.y                # Bison context-free grammar constraints
│   ├── 3_ast/
│   │   ├── ast.c                   # AST data models & JSON generation rules
│   │   └── ast.h
│   ├── 4_semantics/
│   │   ├── semantic.c              # Recursive tree-walking analyzer pass
│   │   ├── symbol_table.c          # Scoped map lookups & UI snapshot exporters
│   │   └── symbol_table.h
│   ├── 5_tac/
│   │   ├── tac.c                   # Intermediate registration code emitter
│   │   └── tac.h
│   └── 6_cfg/
│       ├── cfg.c                   # Leader evaluation & basic block partitioner
│       └── cfg.h
├── backend/
│   └── server.js                   # Node Express API orchestration subprocess
├── ui/
│   └── frontend/
│       ├── src/
│       │   ├── App.jsx             # React UI layout dashboard framework
│       │   └── main.jsx
│       └── package.json
├── Makefile                        # Automation build instructions script
└── README.md