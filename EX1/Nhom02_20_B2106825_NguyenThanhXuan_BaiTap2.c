#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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
//======================================================
typedef struct Node{
    State state;
    struct Node* Parent;
    int no_funtion;

}Node;

//khai bao stack
typedef struct{
    Node* Element[Maxlength];
    int Top_idx;
}Stack;

void makenullStack(Stack *S){
    S->Top_idx = Maxlength;
}
int emptyStack(Stack S){
    return S.Top_idx == Maxlength;
}
int full_Stack(Stack S){
    return S.Top_idx ==0;
}
//trả về phần tử trên đỉnh ngăn xếp
Node* top(Stack stack){
    if(!emptyStack(stack)){
        return stack.Element[stack.Top_idx];
    }
    return NULL;
}
void push(Node *x, Stack *S){
    if(full_Stack(*S)){
        printf("Error. Stack is full");
    }
    else{
        S->Top_idx-=1;
        S->Element[S->Top_idx] = x;
    }
}
void pop(Stack *stack){
    if(!emptyStack(*stack)){
        stack->Top_idx++;
    }
    else{
        printf("Error. Stack is empty");
    }
}
int compareStates(State s1, State s2){
    if(s1.x==s2.x &&s1.y==s2.y)
        return 1;
    
    return 0;
}
int find_State(State state, Stack openStack){
    while(!emptyStack(openStack)){
        if(compareStates(top(openStack)->state ,state ))
            return 1;
        else    
            pop(&openStack);
    }
    return 0;
}

// Thuật toán duyệt theo chiều sâu
Node* DFS(State state){
    Stack open_DFS;
    Stack close_DFS;
    makenullStack(&open_DFS);
    makenullStack(&close_DFS);
    //tạo nút trạng thái cha
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_funtion = 0;
    push(root, &open_DFS);
    while(!emptyStack(open_DFS)){
        Node* node = top(open_DFS);
        pop(&open_DFS);
        push(node,&close_DFS);
        //Kiem tra dinh lay ra co phai trang thai muc tieu
        if(goalcheck(node->state))
            return node;
        
        int opt;
        for(opt =1; opt<= 6; opt++){
            State newstate;
            makenullState(&newstate);
            if(call_operator(node->state, &newstate, opt)){
                //neu trang thai moi sinh ra ton tai thi bo qua
                if(find_State(newstate, close_DFS)||find_State(newstate, open_DFS))
                    continue;
                    
                //neu trang thai moi chua ton tai thi theo vao ngan xep
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newstate;
                newNode->Parent = node;
                newNode->no_funtion = opt;
                push(newNode, &open_DFS);
            }
        }


    }
    return NULL;
}
//In ket qua chuyen nuoc
void print_WayToGetGoal(Node* node){
    Stack stackPrint;
    makenullStack(&stackPrint);
    //duyet nguoc ve nut Parent
    while(node->Parent!=NULL){
        push(node, &stackPrint);
        node= node->Parent;
    }
    push(node, &stackPrint);
    //in ra thu tu hanh dong chuyen nuoc
    int no_action = 0;
    while(!emptyStack(stackPrint)){
        printf("\nAction %d : %s", no_action , action[top(stackPrint)->no_funtion]);
        print(top(stackPrint)->state);
        pop(&stackPrint);
        no_action++;
    }
}

int main(){
    State cur_state = {0,0};
    Node* p = DFS(cur_state);
    print_WayToGetGoal(p);

    return 0;
}