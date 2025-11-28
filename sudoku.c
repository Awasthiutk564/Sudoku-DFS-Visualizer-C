#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define N 9
#define DELAY 35   

// ============= COLORS ============
#define GREEN  "\x1b[32m"
#define RED    "\x1b[31m"
#define YELLOW "\x1b[33m"
#define RESET  "\x1b[0m"

// ============= PRINT VISUAL GRID ============
void printGrid(int grid[N][N], int rH, int cH, int mode) {
    system("cls");

    printf("\n🔵 REAL-TIME DFS SUDOKU SOLVER [Visual + Batch + Export]\n\n");

    for(int r=0;r<N;r++){
        for(int c=0;c<N;c++){

            if(grid[r][c]==0) printf(" . ");

            else if(r==rH && c==cH){
                if(mode==1) printf(GREEN" %d "RESET);   // placed
                else if(mode==2) printf(RED" %d "RESET); // backtrack
                else printf(YELLOW" %d "RESET);          // testing
            }
            else printf(" %d ",grid[r][c]);
        }
        printf("\n");
    }
    Sleep(DELAY);
}

// ============= CHECK SAFE ============
int isSafe(int grid[N][N],int r,int c,int num){
    for(int x=0;x<9;x++)
        if(grid[r][x]==num||grid[x][c]==num) return 0;

    int sr=r-r%3,sc=c-c%3;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(grid[sr+i][sc+j]==num) return 0;

    return 1;
}

// ============= SOLVER + ANIMATION ============
int solveSudoku(int grid[N][N]){
    for(int r=0;r<N;r++){
        for(int c=0;c<N;c++){
            if(grid[r][c]==0){
                for(int num=1;num<=9;num++){
                    if(isSafe(grid,r,c,num)){
                        grid[r][c]=num; printGrid(grid,r,c,1);
                        if(solveSudoku(grid)) return 1;
                        grid[r][c]=0; printGrid(grid,r,c,2);
                    }
                    else{
                        grid[r][c]=num; printGrid(grid,r,c,3);
                        grid[r][c]=0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

// ======================================================
// SAVE SOLVED BOARD → output.txt
// ======================================================
void saveOutput(int grid[N][N], int id, double time){
    FILE *out=fopen("output.txt","a");
    fprintf(out,"\n==== SOLVED PUZZLE %d (%.2f ms) ====\n\n",id,time);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fprintf(out,"%d ",grid[i][j]);
        }
        fprintf(out,"\n");
    }
    fclose(out);
}


// ======================================================
// LOAD ONE PUZZLE FROM FILE
// ======================================================
int loadPuzzle(FILE *fp,int grid[N][N]){
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(fscanf(fp,"%d",&grid[i][j])!=1) return 0; 
    return 1;
}


// ======================================================
// MAIN MENU + MODES
// ======================================================
int main(){

    int choice;
    
    printf("\n==================== MENU ====================\n");
    printf("1. Solve a Sudoku manually (keyboard input)\n");
    printf("2. Solve single Sudoku from input.txt\n");
    printf("3. Batch solve multiple Sudoku from puzzles.txt\n");
    printf("===============================================\n");
    printf("Choose option: ");
    scanf("%d",&choice);

    system("cls");

    if(choice==1){
        int grid[N][N];
        printf("Enter 9x9 Sudoku (0 for blank):\n");
        for(int r=0;r<9;r++)
            for(int c=0;c<9;c++)
                scanf("%d",&grid[r][c]);

        printGrid(grid,-1,-1,0);
        clock_t s=clock();

        if(solveSudoku(grid)){
            double time=(clock()-s)/(double)CLOCKS_PER_SEC*1000;
            printf("\n✔ Solved Successfully in %.2f ms\n",time);
            printGrid(grid,-1,-1,1);
            saveOutput(grid,1,time);
            printf("\nSolution saved → output.txt\n");
        }else printf("❌ No solution!");
    }


    else if(choice==2){
        FILE *fp=fopen("input.txt","r");
        if(!fp){ printf("❌ input.txt missing!"); return 0; }

        int grid[N][N];
        loadPuzzle(fp,grid);

        printGrid(grid,-1,-1,0);
        clock_t s=clock();
        solveSudoku(grid);
        double time=(clock()-s)/(double)CLOCKS_PER_SEC*1000;

        printf("\n✔ Solved in %.2f ms\n",time);
        printGrid(grid,-1,-1,1);
        saveOutput(grid,1,time);
        printf("\nSaved → output.txt\n");
    }


    else if(choice==3){
        FILE *fp=fopen("puzzles.txt","r");
        if(!fp){ printf("❌ puzzles.txt missing!"); return 0; }

        int grid[N][N],id=0,solved=0,total=0;

        while(loadPuzzle(fp,grid)){
            total++; id++;
            printf("\n🧩 Solving Puzzle %d ...\n",id);

            printGrid(grid,-1,-1,0);
            clock_t s=clock();
            int ok=solveSudoku(grid);
            double time=(clock()-s)/(double)CLOCKS_PER_SEC*1000;

            if(ok){
                solved++;
                printf("\n✔ Puzzle-%d Solved in %.2f ms\n",id,time);
                printGrid(grid,-1,-1,1);
                saveOutput(grid,id,time);
            }else{
                printf("\n❌ Puzzle-%d UNSOLVABLE\n",id);
            }
            getchar(); getchar(); 
        }

        printf("\n====== SUMMARY ======\n");
        printf("Total: %d\n",total);
        printf("Solved: %d\n",solved);
        printf("Failed: %d\n",total-solved);
        printf("Solutions exported → output.txt\n\n");
    }

    return 0;
}
