# COMPILER ARCHITECTURE

# Overview

The compiler follows a multi-phase compilation pipeline similar to real-world compilers.

---

# PIPELINE

Source Code
↓
Lexical Analysis (Flex)
↓
Syntax Analysis (Bison)
↓
Semantic Analysis
↓
AST Generation
↓
TAC Generation
↓
CFG Generation
↓
Optimization
↓
Visualization UI

---

# LEXICAL ANALYSIS

Implemented using Flex.

Responsibilities:
- tokenize source code
- identify keywords
- identify identifiers
- identify operators
- identify literals

---

# SYNTAX ANALYSIS

Implemented using Bison.

Responsibilities:
- grammar parsing
- syntax validation
- expression parsing
- statement parsing
- control structure parsing

---

# SEMANTIC ANALYSIS

## Responsibilities
- duplicate declaration checking
- undeclared variable detection
- scope resolution
- shadowing support
- parameter tracking

---

# SYMBOL TABLE ARCHITECTURE

## Global Symbol Table

Stores:
- global variables
- functions
- imports

---

## Function Symbol Tables

Each function contains:
- parameters
- local variables

Example:

GLOBAL TABLE
├── globalA
├── add()
│    ├── a
│    ├── b
│    └── result
│
└── main()
     ├── x
     └── y

---

# VARIABLE LOOKUP STRATEGY

Inside a function:

1. Search local function table
2. Search global table
3. If not found → semantic error

---

# SHADOWING

Supported.

Example:

```c
int x = 5;

void test(){
    int x = 10;
}