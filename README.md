# ChessApp

[![Build Status](https://img.shields.io/badge/build-passing-green)](#) [![License](https://img.shields.io/badge/license-MIT-blue)](#LICENSE)

A minimal chess demo built in C++17 using SFML.  
Supports move validation, piece‐capture, board rendering, and basic event handling.

---

## Table of Contents

- [Features](#features)  
- [Prerequisites](#prerequisites)  
- [Directory Layout](#directory-layout)  
- [Building](#building)  
  - [Visual Studio (native)](#visual-studio-native)  
  - [CMake (cross-platform)](#cmake-cross-platform)  
- [Running](#running)  
- [Contributing](#contributing)  
- [License](#license)  

---

## Features

- Full 8×8 board rendering with alternating square colors  
- Move legality checks and turn management  
- Sprite-based piece rendering & capture handling  
- Keyboard & mouse event loop with 60 FPS cap  

---

## Prerequisites

- **C++17** compiler (MSVC 2019+, GCC 9+, Clang 10+)  
- **SFML 2.5.x** (graphics · window · system)  
- **CMake ≥ 3.10** (if you use the CMake workflow)  
- **Git** (for cloning & submodule management)

---

## Directory Layout

```text
ChessApp/
├─ .gitignore
├─ LICENSE
├─ README.md
├─ ChessApp.sln              # VS solution
├─ ChessApp.vcxproj          # VS project (includes .vcxproj.filters)
│
├─ src/                       # All .cpp implementation files
│  ├─ Main.cpp
│  ├─ ChessWindow.cpp
│  └─ ChessElements.cpp
│
├─ include/                   # Public headers
│  ├─ ChessWindow.h
│  └─ ChessElements.h
│
├─ assets/                    # Game assets
│  ├─ pieces/                 # piece sprites (.png)
│  └─ sounds/default/         # .wav effects
│
└─ x64/                       # (git-ignored) build output
   ├─ Debug/                  # .exe, .pdb, assets copied
   └─ Release/

