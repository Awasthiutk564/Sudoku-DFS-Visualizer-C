# 🔢 Sudoku Solver using DFS + Backtracking  
### 🚀 Visual + Animated + Colored + Batch Solver + Auto File Export in C

This project is a **fully featured Sudoku Solver** built in **C**, powered by  
**Depth-First Search (DFS) + Backtracking Algorithm**, with real-time visualization,  
colored animation, multi-puzzle batch-solving and solution export.

---

## 🔥 Features

| Feature | Status |
|--------|:-----:|
| DFS + Backtracking Algorithm | ✔ |
| Real-time Visual Solving | ✔ |
| Colored State Animation | ✔ |
| Manual Input Mode | ✔ |
| Load Sudoku From File (`input.txt`) | ✔ |
| Solve Multiple Sudokus in Batch (`puzzles.txt`) | ✔ |
| Auto Export Solved Grids → `output.txt` | ✔ |
| Execution Time Tracking | ✔ |

---

## 📂 Project Structure
sudoku.c → Main program + all modes integrated
input.txt → Single puzzle input (if using mode 2)
puzzles.txt → Multiple puzzles for batch solving (mode 3)
output.txt → Auto-saved solved grids
README.md → Documentation

---

## 📸 Visualization Preview

Green = Valid Placement ✔
Red = Backtracking step ❌
Yellow = Trying number (exploration) 🔍


> 🎥 Realtime animation shows DFS solving path step by step.

---

## 💻 How to Run

### 1️⃣ Compile

```bash
gcc sudoku.c -o sudoku
2️⃣ Run
./sudoku
3️⃣ Choose Mode
## 🟦 Choose Execution Mode

| Option | Mode Description                        | Input Source         |
|:-----:|------------------------------------------|---------------------|
| 1     | Solve Sudoku manually                    | User keyboard input |
| 2     | Solve single Sudoku                      | `input.txt`         |
| 3     | Batch solve multiple Sudoku puzzles      | `puzzles.txt`       |


📄 Example input.txt
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9

🚀 Author

Utkarsh Awasthi
⭐ Feel free to Fork / Add new visualization / GUI version
### Star ⭐ this repository if you like it!

## 🏁 Next Upgrade Ideas

| Difficulty | Feature                                      |
|-----------:|----------------------------------------------|
| ⭐ Easy     | Sudoku puzzle random generator               |
| ⭐⭐ Medium  | GUI using SDL/GTK                            |
| ⭐⭐⭐ Hard   | Heuristic + Constraint Propagation (AC-3/MRV) |
| 🔥 Pro     | AI-based difficulty estimator + GUI solver    |


