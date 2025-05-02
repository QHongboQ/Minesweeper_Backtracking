# 🧠 Minesweeper Backtracking Visualizer

A graphical Minesweeper puzzle solver built in C++ using the [Malena](https://github.com/daversmith/Malena) framework and SFML.
This project visually demonstrates how a backtracking algorithm can be used to find valid mine placements that satisfy all numbered tiles on a Minesweeper board.

![demo](Image/minesweep_cut.png)

---

## ✨ Features

* 🎯 **Backtracking Solver**: Recursively finds valid mine layouts using constraint satisfaction.
* 🧩 **Step-by-Step Animation**: Visualizes recursion and flag placement using a highlighter.
* 🔍 **Constraint Checking**: Ensures each numbered tile has exactly the required mines adjacent.
* 🌟 **Texture-Based Display**: Dynamically renders tile images via `TileSprite` based on game state.
* 🖱️ **Interactive Controls**: Clickable UI elements simulate gameplay and debugging behavior.

---

## 📁 Project Structure

```
.
├── src/                # C++ source files
│   ├── Board.cpp/.h
│   ├── BackTracking.cpp/.h
│   ├── Highlighter.cpp/.h
│   ├── TileSprite.cpp/.h
│   ├── Node.cpp/.h
│   ├── MinesweeperApp.cpp/.h
│   └── main.cpp
├── Image/              # Texture sheet (minesweep_cut.png)
├── CMakeLists.txt      # CMake build config (uses FetchContent)
├── CMakePresets.json   # Preset compiler/build targets (optional)
└── README.md           # This file
```

---

## 🚀 How to Build

### ✅ Requirements

* C++17 or later
* CMake 3.14+
* Git
* SFML runtime (auto-handled via Malena)

### 🔧 Build Instructions

#### 🖥️ Windows (MSVC / MinGW):

```bash
cmake -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

#### 🐧 Linux / macOS:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

#### 📦 Output:

After building, the executable can be found in:

```
build/bin/Minesweeper_Backtracking(.exe)
```

---

## 🚪 Try Without Building

To run the demo instantly:

1. Visit the [Releases page](https://github.com/QHongboQ/Minesweeper_Backtracking/releases)
2. Download the latest `.zip`
3. Unzip and run `Minesweeper_Backtracking.exe`

✅ No compilation required!

---

## 🎨 Tile States Overview

| Value | Meaning            | Texture Index      |
| ----- | ------------------ | ------------------ |
| `0-8` | Number tile        | `(1,0)` \~ `(1,8)` |
| `-1`  | Flagged tile       | `(0,2)`            |
| `-2`  | Clicked blank tile | `(0,3)`            |
| `-6`  | Exploded mine      | `(0,6)`            |

Tile graphics are sliced from `Image/minesweep_cut.png` using a grid-based approach.

---

## 🤓 Algorithm Overview

The solver uses recursive **backtracking** to explore flag placement possibilities around all numbered tiles:

1. Collect all tiles with numbers > 0 (`allNumberNodes`).
2. For each such tile, generate valid mine combinations around it.
3. Apply recursive backtracking with constraint checks:

   * If a combination is invalid (conflicts with neighbors), skip.
   * If valid, place flags and recurse.
4. Track steps and flagSteps for animation playback.
5. Use `Highlighter` to animate movement and flag placement.

All animations are recorded to allow real-time visualization of solving progress.

---

## 🌐 Dependencies

* [Malena UI Framework](https://github.com/daversmith/Malena) — auto-downloaded with CMake `FetchContent`
* [SFML 2.5+](https://www.sfml-dev.org/) — runtime dependency for rendering

You **do not need to clone Malena manually** — everything is fetched and built automatically.

---

## 💼 License

MIT License. Feel free to use and remix.

---

## 🙏 Credits

* Built using [Malena](https://github.com/daversmith/Malena) by [@daversmith](https://github.com/daversmith)
* Developed by Hongbo Zhou
* Inspired by classic recursive puzzle solving visualizations
