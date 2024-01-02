#include <stdio.h>
#include <stdlib.h>

#define Maxlength 500
#define Max_Value 10
#define EMPTY 0
#define AREA_SQUARE_SIZE 3
#define INF 9999999

typedef struct 
{
    int x, y;
}Coord;

typedef struct{
    Coord data[Maxlength];
    int size;
}ListCoord;

void initListCoord(ListCoord *L){
    L->size=0;
}

void appendListCoord(ListCoord *L, Coord coord){
    L->data[L->size++]= coord;
}

//cau truc rang buoc
#define NB_ROWS 9
#define NB_COLS 9                                                             

typedef struct 
{
    int data[NB_ROWS*NB_COLS][NB_ROWS*NB_COLS];
    int n;
}Constrains;

//Khoi tao rang buoc rong
void initConstrains(Constrains *constrains){
    for(int i =0; i<NB_ROWS*NB_COLS; i++){
        for(int j =0; j<NB_ROWS*NB_COLS; j++){
            constrains->data[i][j]=0;
        }
    }
    constrains->n= NB_ROWS*NB_COLS;
}

int indexOf(Coord coord){
    return (NB_ROWS*coord.x+coord.y);
}

Coord positionOfVertex(int vertex){
    Coord coord;
    coord.x = vertex/NB_ROWS;
    coord.y = vertex% NB_COLS;
    return coord;
}

int addConstrain(Constrains *constrain, Coord source, Coord target){
    int u = indexOf(source);
    int v = indexOf(target);
    if(constrain->data[u][v]==0){
        constrain->data[u][v]=1;
        constrain->data[v][u]=1;
        return 1;
    }
    return 0;
}

ListCoord getConstrains(Constrains constrains, Coord coord){

    int v = indexOf(coord);
    ListCoord result;
    initListCoord(&result);
    for(int i =0; i<constrains.n;i++){
        if(constrains.data[v][i]==1){
            appendListCoord(&result, positionOfVertex(i));
        }
    }
    return result;
}

//===========================================
typedef struct 
{
    int cells[NB_ROWS][NB_COLS];
    Constrains constrains;
}Sudoku;

//khoi tao bang Sudoku
void initSudoku(Sudoku *sudoku){
    for(int i = 0; i<NB_ROWS; i++){
        for(int j =0; j<NB_COLS; j++){
            sudoku->cells[i][j]= EMPTY;
        }
    }
    initConstrains(&sudoku->constrains);
}

void initSudokuWithValues(Sudoku* sudoku, int inputs[NB_ROWS][NB_COLS]){
    for(int i =0; i<NB_ROWS;i++){
        for(int j =0; j<NB_COLS;j++){
            sudoku->cells[i][j]=inputs[i][j];
        }
    }
    initConstrains(&sudoku->constrains);
}

void printSudoku(Sudoku sudoku){
    printf("Sudoku: \n");
    for(int i =0; i<NB_ROWS;i++){
        if(i%AREA_SQUARE_SIZE==0) printf("---------------------------------------\n");
        for(int j =0; j<NB_COLS;j++){
            if(j %AREA_SQUARE_SIZE ==0) printf("| ");
            printf("%d ",sudoku.cells[i][j]);
        }
        printf("|\n");
    }
    printf("----------------------------------\n");
}

int isFilledSudoku(Sudoku sudoku){
    for(int i =0; i<NB_ROWS;i++){
        for(int j =0; j<NB_COLS;j++){
            if(sudoku.cells[i][j]== EMPTY)
                return 0;
        }
    }
    return 1;
}

void spreadConstrainsFrom(Coord position, Constrains* constrains, ListCoord* changeds){
    int row = position.x, column = position.y;
    //tao rang buoc theo cot
    for(int i =0; i<NB_ROWS;i++){
        if(i!=row){
            Coord pos = {i, column};
            if(addConstrain(constrains, position, pos))
                appendListCoord(changeds, pos);
        }
    }

    //tao rang buoc theo hang
    for(int i =0; i<NB_COLS;i++){
        if(i!=column){
            Coord pos = {row, i};
            if(addConstrain(constrains, position, pos))
                appendListCoord(changeds, pos);
        }
    }

    //truyen rang buoc theo khoi
    for(int i =0; i<AREA_SQUARE_SIZE;i++){
        for(int j =0; j<AREA_SQUARE_SIZE;j++){
            int areaX = (row/AREA_SQUARE_SIZE)*AREA_SQUARE_SIZE;
            int areaY = (column/AREA_SQUARE_SIZE)*AREA_SQUARE_SIZE;
            if(areaX+i != row || areaY+j != column){
                Coord pos = {areaX+i, areaY+j};
                if(addConstrain(constrains, position, pos))
                    appendListCoord(changeds, pos);
            }
        }
    }
}

//Khai bao list
typedef struct{
    int Elements[Maxlength];
    int size;
}List;

void makenullList(List *L){
    L->size =0;
}
int emptyList(List L){
    return L.size==0;
}
int fullList(List L){
    return L.size == Maxlength;
}
//truy van gia tri cua phan tu vitri p
int element_at(int p, List L){
    return L.Elements[p-1];
}

void push_List(int x, int positon, List *L){
    if(!fullList(*L)){
    	int q;
        for( q =L->size; q>= positon; q--){
            L->Elements[q]= L->Elements[q-1];
        }
        L->Elements[positon-1]=x;
        L->size++;
    }else   
        printf("List is full\n");
}
//xoa phan tu tai vi tri position ra khoi danh sach
void delete_List(int position, List *L){
    if(emptyList(*L))
        printf("List is empty.\n");
    else if(position>L->size || position<1)
        printf("Position is not possible to delete.\n");
    else{
    	int i;
        for( i = position -1; i<L->size-1;i++){
            L->Elements[i]= L->Elements[i+1];           
        }
        L->size--;
    }
} 

void appendList(List *L, int x){
    push_List(x,L->size+1,L);
}

List getAvailableValues(Coord position, Sudoku sudoku){
    ListCoord posList = getConstrains(sudoku.constrains, position);
    int available[Max_Value];
    for(int i =1; i<Max_Value;i++) available[i]=1;
    for(int i =0; i<posList.size;i++){
        Coord pos = posList.data[i];
        if(sudoku.cells[pos.x][pos.y]!=EMPTY){
            available[sudoku.cells[pos.x][pos.y]] =0;
        }
    }
    List result;
    makenullList(&result);
    for(int i =1; i<Max_Value;i++){
        if(available[i])    appendList(&result, i);
    }
    return result;
}

//Xac dinh o nao uu tien dien truoc
//Cach 1: Do lan luot, o nao trong thi chon
Coord getNextEmptyCell(Sudoku sudoku){
    for(int i =0; i<NB_ROWS;i++){
        for(int j =0; j<NB_COLS;j++){
            Coord pos ={i,j};
            if(sudoku.cells[i][j]==EMPTY)
                return pos;
        }
    }
}
//Cach 2
Coord getNextMinDomainCell(Sudoku sudoku){
    int minLength = INF;
    Coord result;;
    for(int i=0; i<NB_ROWS;i++){
        for(int j =0; j<NB_COLS;j++){
            if(sudoku.cells[i][j] == EMPTY){
                Coord pos = {i,j};
                int availablesLength = getAvailableValues(pos, sudoku).size;
                if(availablesLength<minLength){
                    minLength = availablesLength;
                    result = pos;
                }
            }
        }
    }
    return result;
}

int exploredCounter =0;
int sudokuBackTracking(Sudoku *sudoku){
    if(isFilledSudoku(*sudoku)) return 1;
    Coord position = getNextMinDomainCell(*sudoku);
    List availables = getAvailableValues(position, *sudoku);
    if(availables.size ==0)
        return 0;

    for(int j =0; j<availables.size;j++){
        int value = availables.Elements[j];
        sudoku->cells[position.x][position.y] = value;
        exploredCounter++;
        if(sudokuBackTracking(sudoku))
            return 1;

        sudoku->cells[position.x][position.y] = EMPTY;
    }
    return 0;
}

Sudoku solveSudoku(Sudoku sudoku){
    initConstrains(&sudoku.constrains);
    for(int i =0; i<NB_ROWS;i++){
        for(int j =0; j<NB_COLS;j++){
            ListCoord history;
            initListCoord(&history);
            Coord pos = {i, j};
            spreadConstrainsFrom(pos, &sudoku.constrains, &history);
        }
    }
    exploredCounter =0;
    if(sudokuBackTracking(&sudoku)) printf("Solved\n");
    else printf("Can not solve\n");

    printf("Explored %d states\n", exploredCounter);
    return sudoku;
}

int inputs1[9][9]={
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9},
};

int inputs2[9][9]={
    {0,6,1,0,0,7,0,0,3},
    {0,9,2,0,0,3,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,8,5,3,0,0,0,0},
    {0,0,0,0,0,0,5,0,4},
    {5,0,0,0,0,8,0,0,0},
    {0,4,0,0,0,0,0,0,1},
    {0,0,0,1,6,0,8,0,0},
    {6,0,0,0,0,0,0,0,0},
};


int main(){
    Sudoku sudoku;
    initSudokuWithValues(&sudoku, inputs2);
    printSudoku(sudoku);
    Sudoku result = solveSudoku(sudoku);
    printSudoku(result);

    return 0;
}