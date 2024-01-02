#include <stdio.h>

#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0
#define goal 6
#define Maxlength 100

const char* action[]={
    "First State", "pour Water Full X", "pour Water Full Y",
    "pour Empty X", "pour Empty Y", "pour Water X to Y",
    "pour Water Y to X"
};

typedef struct
{
    int x;
    int y;
}State;

void makenullState(State *S){
    S->x = 0;
    S->y = 0;
}
void print(State S){
    printf("\nX : %d --- Y : %d",S.x, S.y );
}
int goalcheck(State S){
    return S.x == 6 || S.y ==6;
}

int pourWaterFullX(State cur_state, State *result){
    if(cur_state.x<tankcapacity_X){
        result->x = tankcapacity_X;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}
int pourWaterFullY(State cur_state, State *result){
    if(cur_state.y < tankcapacity_Y){
        result->x = cur_state.x;
        result->y = tankcapacity_Y;
        return 1;
    }
    return 0;
}
int pourEmptyX(State cur_state, State *result){
    if(cur_state.x >0){
        result->x = empty;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}
int pourEmptyY(State cur_state, State *result){
    if(cur_state.y >0){
        result->x = cur_state.x;
        result->y = empty;
        return 1;
    }
    return 0;
}
int max(int a, int b)
{
    return a>b?a:b;
}
int min(int a, int b){
    return a<b?a:b;
}
int pourWaterXY(State cur_state, State *result){
    if(cur_state.x>0 && cur_state.y <tankcapacity_Y){
        result->x = max( cur_state.x-(tankcapacity_Y-cur_state.y)  ,0);
        result->y = min(cur_state.x+cur_state.y ,tankcapacity_Y );
        return 1;
    }
    return 0;
}
int pourWaterYX(State cur_state, State *result){
    if(cur_state.y > 0 && cur_state.x <tankcapacity_X){
        result->x = min(tankcapacity_X , cur_state.x+cur_state.y);
        result->y = max(cur_state.y - (tankcapacity_X - cur_state.x) , 0);
        return 1;
    }
    return 0;
}
int call_operator(State cur_state, State *result, int option){
    switch (option)
    {
    case 1:
        return pourWaterFullX(cur_state, result);
        break;
    case 2:
        return pourWaterFullY(cur_state, result);
        break;
    case 3:
        return pourEmptyX(cur_state, result);
        break;
    case 4:
        return pourEmptyY(cur_state, result);
        break;
    case 5:
        return pourWaterXY(cur_state, result);
        break;   
    case 6:
        return pourWaterYX(cur_state, result);
        break;  
    default:
        printf("Error calls operators");
        return 0;
    }
}


int main(){

    State cur_state, result;
    cur_state.x = 5;
    cur_state.y =4;

    printf("Trang thai bat dau : ");
    print(cur_state);
    int opt;
    for(opt =1; opt<=6;opt++){
        int thuchien = call_operator(cur_state, &result, opt);
        if(thuchien){
            printf("\nHanh dong %s thanh cong ", action[opt] );
            print(result);
        }
        else{
            printf("\nHanh dong %s khong thanh cong", action[opt]);
        }
    }
    return 0;
}