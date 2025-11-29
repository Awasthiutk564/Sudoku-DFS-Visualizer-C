<h1 align="center">🔢 Sudoku Solver — DFS + MRV + Forward Checking (C)</h1>

<p align="center">
  <b>Realtime Visual Solver • Color Tracing • Heuristic MRV Engine • Backtracking Optimized</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Algorithm-DFS%20%2B%20MRV%20Heuristic-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/Optimization-Forward%20Checking-orange?style=for-the-badge">
  <img src="https://img.shields.io/github/last-commit/Awasthiutk564/Sudoku-DFS-Visualizer-C?style=for-the-badge">
</p>

---

## 🚀 What This Project Can Do

| Feature | Status |
|---|:---:|
| DFS + Backtracking Solver | ✔ |
| MRV (Minimum Remaining Values) Heuristic | ✔ |
| Forward Checking (reduced dead branches) | ✔ |
| Live Terminal Animation + Colors | ✔ |
| Execution Stats (Recursions/Backtracks/Nodes) | ✔ |
| Very Fast Logical Solving | 🔥 |

---

## 🧠 How MRV + Forward Checking Improves Performance

| Version | Backtracking | Recursions | Speed |
|---|---|---|---|
| Normal DFS | Very High 🔴 | 40k–200k+ | Slow |
| DFS + MRV | Medium/Low 🟡 | 500–1000 approx | Faster |
| **DFS + MRV + Forward Checking (this repo)** | Very Low 🟢 | 50–200 avg | ⚡ Smart & Fast |

MRV reduces random guess-work  
Forward Checking prevents dead boards early  
Together = 💥 Very Efficient Solver

---

## 🎥 Visualization Look

Green → correct placement
Yellow → testing possibility
Red → backtrack step


> Solver looks alive while solving.

---

## 🛠 How To Run

```bash
gcc sudoku.c -o sudoku
./sudoku.exe
Speed-Up Option:

#define DELAY 1   // for faster solve //For those who edit or fork to this repo

📊 Output Example (after Upgrade-B)
Recursions      :    ~50–200
Backtracks      :    Very Low
Nodes Explored  :    Small Search Tree
Time            :    <200ms without animation

📌 Files
sudoku.c        ← Full optimized solver
README.md       ← Documentation
input.txt       ← Single Sudoku input (optional)
puzzles.txt     ← Multiple sudoku batch solver (optional)
output.txt      ← Auto-generated on batch run

