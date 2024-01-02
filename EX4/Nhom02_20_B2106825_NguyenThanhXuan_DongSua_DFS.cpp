#include <stdio.h>
#include <stdlib.h>

#define tankcapacity_X 10
#define tankcapacity_Y 5
#define tankcapacity_Z 6
#define empty 0
#define goal 8
#define Maxlength 100

const char* action[]={
    "First State",
    "pour Empty X", "pour Empty Y", "pour Empty Z", 
    "pour Water X to Y","pour Water X to Z",
    "pour Water Y to X","pour Water Y to Z",
    "pour Water Z to X","pour Water Z to Y",
};

typedef struct
{
    int x;
    int y;
    int z;
}State;

void makenullState(State *S){
    S->x = 10;
    S->y = 0;
    S->z = 0;
}
void print(State S){
    printf("\nX : %d --- Y : %d --- Z : %d",S.x, S.y, S.z );
}
int goalcheck(State S){
    return S.x == goal || S.y ==goal || S.z == goal;
}

int pourEmptyX(State cur_state, State *result){
    if(cur_state.x >0){
        result->x = empty;
        result->y = cur_state.y;
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}
int pourEmptyY(State cur_state, State *result){
    if(cur_state.y >0){
        result->x = cur_state.x;
        result->y = empty;
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}
int pourEmptyZ(State cur_state, State *result){
    if(cur_state.z >0){
        result->x = cur_state.x;
        result->y = cur_state.y;
        result->z = empty;
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
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}
int pourWaterXZ(State cur_state, State *result){
    if(cur_state.x>0 && cur_state.z <tankcapacity_Z){
        result->x = max( cur_state.x-(tankcapacity_Z-cur_state.z)  ,0);
        result->z = min(cur_state.x+cur_state.z ,tankcapacity_Z );
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}
int pourWaterYX(State cur_state, State *result){
    if(cur_state.y > 0 && cur_state.x <tankcapacity_X){
        result->x = min(tankcapacity_X , cur_state.x+cur_state.y);
        result->y = max(cur_state.y - (tankcapacity_X - cur_state.x) , 0);
        result->z = cur_state.z;
        return 1;
    }
    return 0;
}
int pourWaterYZ(State cur_state, State *result){
    if(cur_state.y > 0 && cur_state.z<tankcapacity_Z){
        result->x = cur_state.x;
        result->y = max(cur_state.y - (tankcapacity_Z - cur_state.z) , 0);
        result->z = min(cur_state.y + cur_state.z, tankcapacity_Z);
        return 1;
    }
    return 0;
}
int pourWaterZX(State cur_state, State *result){
    if(cur_state.z > 0 && cur_state.x <tankcapacity_X){
        result->x =  min(cur_state.x+cur_state.z, tankcapacity_X);
        result->y = cur_state.y;
        result->z = max(cur_state.z - (tankcapacity_X - cur_state.x) , 0);
        return 1;
    }
    return 0;
}
int pourWaterZY(State cur_state, State *result){
    if(cur_state.z > 0 && cur_state.y <tankcapacity_Y){
        result->x =  cur_state.x;
        result->y = min(cur_state.z+cur_state.y, tankcapacity_Y);
        result->z = max(cur_state.z - (tankcapacity_Y - cur_state.y) , 0);
        return 1;
    }
    return 0;
}
int call_operator(State cur_state, State *result, int option){
    switch (option)
    {
    case 1:
        return pourEmptyX(cur_state, result);
        break;
    case 2:
        return pourEmptyY(cur_state, result);
        break;
    case 3:
        return pourEmptyZ(cur_state, result);
        break;
    case 4:
        return pourWaterXY(cur_state, result);
        break;
    case 5:
        return pourWaterXZ(cur_state, result);
        break;   
    case 6:
        return pourWaterYX(cur_state, result);
        break;  
    case 7:
        return pourWaterYZ(cur_state, result);
        break;  
    case 8:
        return pourWaterZX(cur_state, result);
        break;
    case 9:
        return pourWaterZY(cur_state, result);
        break;  
    default:
        printf("Error calls operators");
        return 0;
    }
}

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

//========================================

//tr? v? ph?n t? trên d?nh ngan x?p
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
    if(s1.x==s2.x &&s1.y==s2.y  && s1.z == s2.z)
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

// Thu?t toán duy?t theo chi?u sâu
Node* DFS(State state){
    Stack open_DFS;
    Stack close_DFS;
    makenullStack(&open_DFS);
    makenullStack(&close_DFS);
    //t?o nút tr?ng thái cha
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
        for(opt =1; opt<= 9; opt++){
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
    State cur_state ;
    makenullState(&cur_state);
    Node* p = DFS(cur_state);
    print_WayToGetGoal(p);
    return 0;
 }
