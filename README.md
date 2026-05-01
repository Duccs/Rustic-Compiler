# Rustic-Compiler

A bare-bones compiler for a small C++-like language, written from scratch in C++ as a proof of concept. Built as part of CS-4550.

Neither the title nor the project has any relation the Rust programming language. A major oversight.

## Overview

Rustic-Compiler takes a source file in a small C++-style language and compiles it through this pipeline:

```
Source -> Scanner -> Parser -> Parse Tree -> Machine Code -> Execute
```

The final stage places raw x64 machine code directly into an in-memory buffer and executes it via a function pointer.

## Features

- **Scope-aware symbol table**: Supports nested blocks with proper shadowing via push/pop scope semantics.
- **Scanner**: Implemented with an explicit state machine over the input stream.
- **Recursive-descent parser**: produces a typed AST with a hierarchy of nodes.
- **Dual execution modes**: All nodes support tree-walking interpretation and machine-code generation. Hence, parse trees can be either run directly or compiled.
- **Linux syscall-based I/O**: Limited for Linux operating systems and uses Linux specfic machine code.

## Coding Language

A small C++ subset:

- **Types:** `int` only
- **Statements:** declarations, assignments, blocks, `if`/`else`, `while`, `do`/`while`, `break`, `continue`
- **I/O:** `cout << expr << endl;`,  `Print(expr);`
- **Arithmetic operators:** `+`, `-`, `*`, `/`
- **Augmented assignment:** `+=`, `-=`
- **Relational operators:** `<`, `<=`, `>`, `>=`, `==`, `!=`
- **Logical operators:** `&&`, `||`
- **Comments:** `// line comments`
- **Nested scopes** with variable shadowing

### Example

```cpp
void main()
{
    int x;
    int y;
    x = 1;
    y = 10;
    cout << x << y << endl;

    while (x < 25) {
        x += 4;
        cout << x << endl;
    }

    {
        int x;       // shadows outer x
        x = 99;
        cout << x << endl;
    }
    cout << x << endl;  // outer x again
}
```

## Architecture

The codebase is organized into focused libraries, each owning one stage of the pipeline:

| Library | Responsibility |
|---|---|
| `lib-token` | Token type definitions and the scanner's state machine |
| `lib-scanner` | Reads the source file and produces a stream of tokens |
| `lib-symbol` | Symbol table with scoped variable storage |
| `lib-parser` | Recursive-descent parser and AST node hierarchy (`Node.h`) |
| `lib-instructions` | x86-64 machine-code buffer, encoding helpers, and the in-memory executor |
| `lib-debug` | Debug macros and helpers |
| `src` | Test drivers, one executable per pipeline stage |

Each AST node implements two virtual methods:

- `Interpret()`: Walks the tree and executes the program directly in C++.
- `Code(InstructionsClass&)`: emits x64 bytes that, when executed, produce the same result.

## Building

> **Platform:** Builds on **Linux only**. The machine-code backend emits raw x64 instructions and uses Linux syscalls for I/O, so the project, in its current state, is not portable to Windows or macOS.

Requirements:

- A C++17 compiler (g++ or clang++)
- CMake 3.10 or newer
- x64 Linux

Build with CMake:

```sh
mkdir build && cd build
cmake ..
make
```

This produces six executables in the build directory, one per pipeline stage:

| Executable | What it does |
|---|---|
| `Scanner` | Tokenizes `code.txt` and prints the token stream |
| `SymbolTable` | Exercises the symbol table |
| `ParseTree` | Parses `code.txt` and prints the AST |
| `Parser` | Parses and interprets `code.txt` via the tree-walking interpreter |
| `Instructions` | Exercises the machine-code emitter directly |
| `MachineCode` | Full pipeline: parse `code.txt`, emit x64, execute it |

## Running

The end-to-end compiler is the `MachineCode` executable. It expects a file named `code.txt` in the working directory:

```sh
cd build/src
./MachineCode
```

Edit `src/code.txt` to compile and run a different program. A larger example covering most language features is in `src/20test.txt`.

## License

See [LICENSE](LICENSE).
