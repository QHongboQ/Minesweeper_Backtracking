# 🧠 Minesweeper Backtracking Visualizer

A graphical Minesweeper puzzle solver built in C++ using the [Malena](https://github.com/daversmith/Malena) framework and SFML.  
This project visually demonstrates how a backtracking algorithm can be used to find a valid mine placement that satisfies all numbered tiles on a Minesweeper board.

![demo](Image/minesweep_cut.png)

---

## ✨ Features

- 🎯 **Backtracking Solver**: Recursively finds a valid mine placement that satisfies all constraints.
- 🧩 **Animated Visualization**: Step-by-step display of node traversal and flag placements.
- 🖱️ **Interactive Testing**: Clickable tiles with highlight feedback.
- 🧠 **Logic-Conscious Flagging**: Respects number constraints when flagging.
- 🎨 **Custom Textures**: Dynamically update tile appearance based on number, flag, or blank.
- 🔧 **Modular Design**: Clean separation of logic into `Board`, `Node`, `BackTracking`, `Highlighter`, and `TileSprite`.

---

## 📁 Project Structure

```
.
├── src/
│   ├── Board.{cpp,h}
│   ├── Node.{cpp,h}
│   ├── BackTracking.{cpp,h}
│   ├── Highlighter.{cpp,h}
│   ├── TileSprite.{cpp,h}
│   ├── MinesweeperApp.{cpp,h}
│   └── main.cpp
├── Image/
│   └── minesweep_cut.png
├── CMakeLists.txt
├── .gitignore
└── README.md
```

---

## 🚀 How to Build

### ✅ Prerequisites

- C++17 or later
- [CMake >= 3.14](https://cmake.org/download/)
- Git

### 🔧 Build Instructions

```bash
# Clone the repository
git clone https://github.com/QHongboQ/Minesweeper_Backtracking.git
cd Minesweeper_Backtracking

# Configure (Release mode recommended for CI and performance)
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# Run (Windows)
./build/bin/Minesweeper_Backtracking.exe
```

---

## 🧪 Try it without building

1. Go to the [Releases](https://github.com/QHongboQ/Minesweeper_Backtracking/releases) page.
2. Download the `.zip` package.
3. Extract it and double-click `Minesweeper_Backtracking.exe`.

✅ Make sure the `Image/` folder is next to the `.exe`.

---

## 🎨 Tile States

| Number | Meaning              | Texture Coordinates |
|--------|----------------------|----------------------|
| `0-5`  | Numbered tiles       | `(1,0)` to `(1,4)`   |
| `-1`   | Flag                 | `(0,2)`              |
| `-2`   | Revealed blank tile  | `(0,3)`              |
| `-6`   | Mine explosion       | `(0,6)`              |

---

## 🧠 Algorithm Overview

The backtracking solver:

- Iterates over all `number > 0` nodes
- Tests all neighbor flag combinations that satisfy the current tile
- Prunes invalid paths early to improve efficiency
- Generates a full animation script:
  - `step`: highlight exploration sequence
  - `flagStep`: flag/unflag visualization updates

This script is played back by the `Highlighter` to show the solving process.

---

## 🛠 Technical Details

- Uses `FetchContent` to automatically download [Malena](https://github.com/daversmith/Malena)
- CI tested on Windows, macOS, and Linux
- No manual dependency setup needed
- Compatible with CMake + VSCode, MSYS2, GitHub Actions

---

## 📜 License

MIT License. See `LICENSE.md` for details.

---

## 🙌 Credits

- Framework: [Malena](https://github.com/daversmith/Malena) by [@daversmith](https://github.com/daversmith)
- Author: Hongbo Zhou (QHongboQ)