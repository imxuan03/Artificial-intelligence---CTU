#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3
#define EMPTY 0
#define Maxlength 500

const char* action[]={
    "First State", "Move Cell EMPTY to UP", "Move Cell EMPTY to DOWN",
    "Move Cell EMPTY to LEFT", "Move Cell EMPTY to RIGHT"
};

//Khai bao cau truc trang thai Puzzel
typedef struct 
{
    int eightPuzzel[ROWS][COLS];
    int emptyRow;
    int emptyCol;
}State;

void printState(State state){
    printf("\n");
    for(int i = 0; i<ROWS;i++){
        for(int j =0; j<COLS ; j++){
            printf("|%d ", state.eightPuzzel[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------\n");
}

int compareStates(State s1, State s2){
    if(s1.emptyCol != s2.emptyCol || s1.emptyRow!=s2.emptyRow)
        return 0;

    for(int i =0; i<ROWS;i++){
        for(int j =0; j<COLS; j++){
            if(s1.eightPuzzel[i][j]!= s2.eightPuzzel[i][j])
                return 0;
        }
    }
    return 1;

}

int goalCheck(State state, State goal){
    return compareStates(state, goal);
}

int UP(State state, State *result){

    *result = state;
    int emptyRowCurrent = state.emptyRow;
    int emptyColCurrent = state.emptyCol;

    if(emptyRowCurrent>0){
        result->emptyRow = emptyRowCurrent-1;
        result->emptyCol = emptyColCurrent;
        result->eightPuzzel[emptyRowCurrent][emptyColCurrent]= state.eightPuzzel[emptyRowCurrent-1][emptyColCurrent];
        result->eightPuzzel[emptyRowCurrent-1][emptyColCurrent] = EMPTY;
        return 1;
        }
    return 0;

}

int DOWN(State state, State *result){
    *result = state;
    int emptyRowCurrent = state.emptyRow;
    int emptyColCurrent = state.emptyCol;

    if(emptyRowCurrent<2){
        result->emptyRow = emptyRowCurrent+1;
        result->emptyCol = emptyColCurrent;
        result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent+1][emptyColCurrent];
        result->eightPuzzel[emptyRowCurrent+1][emptyColCurrent]= EMPTY;
        return 1;
    }
    return 0;
}

int LEFT(State state, State *result){
    *result = state;
    int emptyRowCurrent = state.emptyRow;
    int emptyColCurrent = state.emptyCol;
    if(emptyColCurrent>0){
        result->emptyRow = emptyRowCurrent;
        result->emptyCol = emptyColCurrent-1;
        result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent][emptyColCurrent-1];
        result->eightPuzzel[emptyRowCurrent][emptyColCurrent-1]= EMPTY;
        return 1;
    }
    return 0;
}
int RIGHT(State state, State *result){
    *result = state;
    int emptyRowCurrent = state.emptyRow;
    int emptyColCurrent = state.emptyCol;
    if(emptyColCurrent<2){
        result->emptyRow = emptyRowCurrent;
        result->emptyCol = emptyColCurrent+1;
        result->eightPuzzel[emptyRowCurrent][emptyColCurrent]=state.eightPuzzel[emptyRowCurrent][emptyColCurrent+1];
        result->eightPuzzel[emptyRowCurrent][emptyColCurrent+1]= EMPTY;
        return 1;
    }
    return 0;
}

int call_Operators(State state, State *result , int opt){
    switch (opt)
    {
        case 1: return UP(state,result);
        case 2: return DOWN(state, result);
        case 3: return LEFT(state, result);
        case 4: return RIGHT(state, result);
        default: printf("\nCannot call operators");
            return 0;
    }
}

int main(){

    State state, result;
    state.emptyRow=1;
    state.emptyCol =1;
    state.eightPuzzel[0][0] =3;
    state.eightPuzzel[0][1] =4;
    state.eightPuzzel[0][2] =5;
    state.eightPuzzel[1][0] =1;
    state.eightPuzzel[1][1] =0;
    state.eightPuzzel[1][2] =2;
    state.eightPuzzel[2][0] =6;
    state.eightPuzzel[2][1] =7;
    state.eightPuzzel[2][2] =8;

    for(int i =1; i<=4;i++){
        call_Operators(state, &result, i);
        if(!compareStates(state,result)){
            printf("Hanh dong %s thanh cong\n", action[i]);
            printState(result);
        }else{
            printf("Hanh dong %s khonog thanh cong\n", action[i]);
        }
    }




    return 0;
}