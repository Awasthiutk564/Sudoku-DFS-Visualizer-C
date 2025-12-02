#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define N 9
#define DELAY 10

// ---------- Stats ----------
long long RECURSIONS = 0, BACKTRACKS = 0, NODES_EXPLORED = 0;

// ---------- Colors ----------
#define GREEN  "\x1b[32m"
#define RED    "\x1b[31m"
#define YELLOW "\x1b[33m"
#define WHITE  "\x1b[37m"
#define RESET  "\x1b[0m"

// ---------- RESET STATS ----------
void resetStats() {
    RECURSIONS = 0;
    BACKTRACKS = 0;
    NODES_EXPLORED = 0;
}

// ---------- GRID DISPLAY ----------
void printGrid(int grid[N][N], int hr, int hc, int mode) {
    system("cls");
    printf("\n🔥 Sudoku Multi-Mode Solver (DFS / MRV / MRV+FC)\n\n");

    for (int r=0;r<N;r++) {
        for (int c=0;c<N;c++) {
            if (grid[r][c] == 0) printf(" . ");
            else if (r==hr && c==hc) {
                if(mode==1)      printf(GREEN" %d "RESET);
                else if(mode==2) printf(RED" %d "RESET);
                else             printf(YELLOW" %d "RESET);
            } else printf(WHITE" %d "RESET);
        }
        printf("\n");
    }
    Sleep(DELAY);
}

// ---------- SAFETY CHECK ----------
int isSafe(int g[N][N], int r, int c, int num) {
    for(int x=0;x<9;x++)
        if(g[r][x]==num || g[x][c]==num) return 0;

    int sr=r-r%3, sc=c-c%3;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(g[sr+i][sc+j]==num) return 0;

    return 1;
}

//
// ---------------- NORMAL DFS SOLVER ----------------
//
int solveDFS(int g[N][N]) {
    RECURSIONS++;
    for(int r=0;r<9;r++){
        for(int c=0;c<9;c++){
            if(g[r][c]==0){
                for(int num=1;num<=9;num++){
                    NODES_EXPLORED++;
                    if(isSafe(g,r,c,num)){
                        g[r][c]=num;
                        printGrid(g,r,c,1);
                        if(solveDFS(g)) return 1;
                        g[r][c]=0;
                        BACKTRACKS++;
                        printGrid(g,r,c,2);
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

//
// ---------------- MRV FUNCTION ----------------
//
int findMRV(int g[N][N], int *br, int *bc) {
    int best=10, found=0;

    for(int r=0;r<9;r++){
        for(int c=0;c<9;c++){
            if(g[r][c]==0){
                int cnt=0;
                for(int n=1;n<=9;n++)
                    if(isSafe(g,r,c,n)) cnt++;

                if(cnt < best){
                    best = cnt;
                    *br = r;
                    *bc = c;
                    found = 1;
                }
            }
        }
    }
    return found;
}

//
// ---------------- DFS + MRV ----------------
//
int solveMRV(int g[N][N]) {
    RECURSIONS++;

    int r,c;
    if(!findMRV(g,&r,&c)) return 1;

    for(int num=1;num<=9;num++){
        NODES_EXPLORED++;
        if(isSafe(g,r,c,num)){
            g[r][c]=num;
            printGrid(g,r,c,1);
            if(solveMRV(g)) return 1;
            g[r][c]=0;
            BACKTRACKS++;
            printGrid(g,r,c,2);
        }
    }
    return 0;
}

//
// ---------------- FORWARD CHECKING ----------------
//
int forwardCheck(int g[N][N]){
    for(int r=0;r<9;r++){
        for(int c=0;c<9;c++){
            if(g[r][c]==0){
                int ok=0;
                for(int num=1;num<=9;num++)
                    if(isSafe(g,r,c,num)) ok=1;
                if(!ok) return 0;
            }
        }
    }
    return 1;
}

//
// -------- DFS + MRV + FORWARD CHECKING --------
//
int solveMRV_FC(int g[N][N]) {
    RECURSIONS++;

    int r,c;
    if(!findMRV(g,&r,&c)) return 1;

    for(int num=1;num<=9;num++){
        NODES_EXPLORED++;

        if(isSafe(g,r,c,num)){
            g[r][c]=num;
            printGrid(g,r,c,1);

            if(!forwardCheck(g)){
                g[r][c]=0;
                BACKTRACKS++;
                printGrid(g,r,c,2);
                continue;
            }

            if(solveMRV_FC(g)) return 1;

            g[r][c]=0;
            BACKTRACKS++;
            printGrid(g,r,c,2);
        }
    }
    return 0;
}

//
// ---------------- MAIN ----------------
//
int main(){

    int original[N][N] = {
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

    int choice;
    printf("\n========== SELECT SOLVER MODE ==========\n");
    printf("1. Normal DFS\n");
    printf("2. DFS + MRV Heuristic\n");
    printf("3. DFS + MRV + Forward Checking (FAST)\n");
    printf("========================================\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

    int grid[N][N];
    memcpy(grid, original, sizeof(original));

    printGrid(grid,-1,-1,0);
    resetStats();

    clock_t start = clock();

    int solved = 0;

    if(choice==1) solved = solveDFS(grid);
    else if(choice==2) solved = solveMRV(grid);
    else if(choice==3) solved = solveMRV_FC(grid);

    double t = (double)(clock()-start)/CLOCKS_PER_SEC*1000;

    system("cls");

    printf("\n🎉 FINAL SOLVED GRID:\n\n");
    for(int r=0;r<9;r++){
        for(int c=0;c<9;c++)
            printf(" %d ",grid[r][c]);
        printf("\n");
    }

    printf("\n📊 PERFORMANCE REPORT\n");
    printf("-----------------------------\n");
    printf("Recursions      : %lld\n", RECURSIONS);
    printf("Backtracks      : %lld\n", BACKTRACKS);
    printf("Nodes Explored  : %lld\n", NODES_EXPLORED);
    printf("Execution Time  : %.2f ms\n", t);
    printf("-----------------------------\n");

    return 0;
}
