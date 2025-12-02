<h1 align="center">🔢 Sudoku Solver in C — DFS + MRV + Forward Checking</h1>

<p align="center">
  <b>Real-Time Visual Solver • Color Animation • Multi-Mode Engine • Performance Stats</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Algorithms-DFS%20%2B%20MRV%20%2B%20ForwardChecking-green?style=for-the-badge">
  <img src="https://img.shields.io/github/last-commit/Awasthiutk564/Sudoku-DFS-Visualizer-C?style=for-the-badge">
  <img src="https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge">
</p>

---

## 🚀 About The Project  
This is an advanced Sudoku Solver implemented in pure **C**, featuring:

✔ Depth-First Search (DFS)  
✔ MRV (Minimum Remaining Values) Heuristic  
✔ Forward Checking (reduces dead states)  
✔ Multiple solver modes  
✔ Color-based real-time visualization  
✔ Full performance analytics (recursions, backtracks, nodes explored, execution time)

The project is built as a **toolkit** to compare different Sudoku solving strategies interactively.

---

## 🧠 Solver Modes (Multi-Mode Engine)

| Mode | Name | Description | Speed |
|------|------|-------------|--------|
| **1** | Normal DFS | Classic recursive solver | 🟡 Medium |
| **2** | DFS + MRV | Picks cell with lowest options | 🟢 Fast |
| **3** | DFS + MRV + Forward Checking | Avoids future dead states | 🔥 Fastest & Smartest |

---

## 🎨 Visual Animation

Colors used during solving:

| Color | Meaning |
|-------|---------|
| 🟢 **Green** – Correct Placement |
| 🔴 **Red** – Backtracking step |
| 🟡 **Yellow** – Tried but rejected |
| ⚪ **White** – Final stable number |

Animation speed can be controlled using:

```c
#define DELAY 10
📊 Performance Output Example
🎉 FINAL SOLVED GRID

Recursions      : 52
Backtracks      : 0
Nodes Explored  : 239
Execution Time  : 15.20 ms
Shows how heuristics dramatically reduce search depth.
📂 File Structure
📦 Sudoku-DFS-Visualizer-C
 ├── sudoku.c        ← Multi-mode solver (DFS/MRV/FC)
 ├── README.md       ← Documentation
 ├── input.txt       ← Single puzzle input
 ├── puzzles.txt     ← Batch solve (optional)
 ├── output.txt      ← Auto saved solved output
🛠 How to Build & Run
gcc sudoku.c -o sudoku
./sudoku.exe
On running, choose a mode:
1 → Normal DFS
2 → DFS + MRV
3 → DFS + MRV + Forward Checking 
andn Enter the value from user
🧩 Example Sudoku Input
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
🔮 Future Enhancements

(If you want to upgrade)

GUI using SDL

AC-3 Constraint Propagation

Sudoku difficulty estimator

Solution heatmap visualization

Export step-by-step solving as GIF
