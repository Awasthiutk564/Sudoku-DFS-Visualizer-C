#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define N 9
#define DELAY 10   // animation speed (ms) - 0 or 1 for very fast

// ---------- Performance Stats ----------
long long RECURSIONS = 0;
long long BACKTRACKS = 0;
long long NODES_EXPLORED = 0;

// ---------- ANSI Colors ----------
#define GREEN  "\x1b[32m"
#define RED    "\x1b[31m"
#define YELLOW "\x1b[33m"
#define WHITE  "\x1b[37m"
#define RESET  "\x1b[0m"

// ---------- GRID DISPLAY WITH ANIMATION ----------
void printGrid(int grid[N][N], int hr, int hc, int mode) {
    system("cls");

    printf("\n🚀 Sudoku Solver — DFS + MRV + Forward Checking + Stats\n\n");

    for (int r=0; r<N; r++) {
        for (int c=0; c<N; c++) {

            if (grid[r][c] == 0) {
                printf(" . ");
            }
            else if (r == hr && c == hc) {
                if (mode == 1)      printf(GREEN  " %d " RESET);   // placed
                else if (mode == 2) printf(RED    " %d " RESET);   // backtrack
                else                printf(YELLOW " %d " RESET);   // tested
            } else {
                printf(WHITE " %d " RESET);
            }
        }
        printf("\n");
    }

    Sleep(DELAY);
}

// ---------- SAFETY CHECK ----------
int isSafe(int grid[N][N], int r, int c, int num) {

    for (int x = 0; x < 9; x++)
        if (grid[r][x] == num || grid[x][c] == num)
            return 0;

    int sr = r - r % 3;
    int sc = c - c % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[sr + i][sc + j] == num)
                return 0;

    return 1;
}

// ---------- FORWARD CHECKING ----------
// check that every empty cell still has at least one valid number
int forwardCheck(int grid[N][N]) {
    for (int r=0; r<N; r++) {
        for (int c=0; c<N; c++) {

            if (grid[r][c] == 0) {
                int hasOption = 0;

                for (int num=1; num<=9; num++) {
                    if (isSafe(grid,r,c,num)) {
                        hasOption = 1;
                        break;
                    }
                }

                if (!hasOption) {
                    return 0;  // dead state → prune early
                }
            }
        }
    }
    return 1;
}

// ---------- MRV: CELL WITH MINIMUM OPTIONS ----------
int findBestCell(int grid[N][N], int *br, int *bc) {
    int minOptions = 10;
    int found = 0;

    for (int r=0; r<N; r++) {
        for (int c=0; c<N; c++) {

            if (grid[r][c] == 0) {
                int cnt = 0;

                for (int num=1; num<=9; num++)
                    if (isSafe(grid,r,c,num))
                        cnt++;

                if (cnt < minOptions) {
                    minOptions = cnt;
                    *br = r;
                    *bc = c;
                    found = 1;

                    if (cnt == 1)
                        return 1;  // best possible MRV
                }
            }
        }
    }
    return found;
}

// ---------- DFS + MRV + FORWARD CHECKING ----------
int solveSudokuHeuristic(int grid[N][N]) {
    RECURSIONS++;

    int r, c;

    // 1) pick best cell by MRV
    if (!findBestCell(grid, &r, &c)) {
        // no empty cells -> solved
        return 1;
    }

    // 2) try all numbers in that cell
    for (int num=1; num<=9; num++) {

        NODES_EXPLORED++;

        if (isSafe(grid,r,c,num)) {

            grid[r][c] = num;
            printGrid(grid,r,c,1);  // green: placed

            // 3) forward check: ensure no future dead cell
            if (!forwardCheck(grid)) {
                // this assignment will lead to dead-end → backtrack early
                grid[r][c] = 0;
                BACKTRACKS++;
                printGrid(grid,r,c,2); // red backtrack
                continue;
            }

            // 4) continue recursion
            if (solveSudokuHeuristic(grid))
                return 1;

            // 5) normal backtrack
            grid[r][c] = 0;
            BACKTRACKS++;
            printGrid(grid,r,c,2); // red backtrack
        }
        else {
            // optional visualization of failed attempt
            grid[r][c] = num;
            printGrid(grid,r,c,3);  // yellow try
            grid[r][c] = 0;
        }
    }

    return 0;
}

// ================= MAIN =================
int main() {

    int grid[N][N] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    printGrid(grid,-1,-1,0);

    clock_t start = clock();
    int ok = solveSudokuHeuristic(grid);
    double time_ms = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;

    system("cls");

    if (ok) {
        printf("\n🎉 FINAL SOLVED GRID (Clean Output):\n\n");
        for (int r=0; r<N; r++) {
            for (int c=0; c<N; c++)
                printf(" %d ", grid[r][c]);
            printf("\n");
        }
    } else {
        printf("\n❌ No solution found.\n");
    }

    printf("\n📊 PERFORMANCE REPORT\n");
    printf("-----------------------------\n");
    printf("Recursions      : %lld\n", RECURSIONS);
    printf("Backtracks      : %lld\n", BACKTRACKS);
    printf("Nodes Explored  : %lld\n", NODES_EXPLORED);
    printf("Execution Time  : %.2f ms\n", time_ms);
    printf("-----------------------------\n");

    return 0;
}
