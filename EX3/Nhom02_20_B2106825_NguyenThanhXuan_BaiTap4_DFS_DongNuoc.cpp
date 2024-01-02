#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

#define tankcapacity_X 9
#define tankcapacity_Y 4
#define Empty 0;
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
    
    cout << "\nX : "<< S.x << "--- Y : "<< S.y ;
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
        result->x = Empty;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}
int pourEmptyY(State cur_state, State *result){
    if(cur_state.y >0){
        result->x = cur_state.x;
        result->y = Empty;
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


int compareStates(State s1, State s2){
    if(s1.x==s2.x &&s1.y==s2.y)
        return 1;
    
    return 0;
}
int find_State(State state, stack<Node*> openStack){
    while(!openStack.empty()){
        if(compareStates(openStack.top()->state ,state ))
            return 1;

        openStack.pop();

    }
    return 0;
}

// Thuật toán duyệt theo chiều sâu
Node* DFS(State state){
    stack<Node*> open_DFS;
    stack<Node*> close_DFS;
    
    //tạo nút trạng thái cha
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_funtion = 0;
    open_DFS.push(root);
    while(!open_DFS.empty()){
        Node* node = open_DFS.top();
        open_DFS.pop();
        close_DFS.push(node);
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
                open_DFS.push(newNode);
            }
        }


    }
    return NULL;
}
//In ket qua chuyen nuoc
void print_WayToGetGoal(Node* node){
   
    stack<Node*> stackPrint;
    
    //duyet nguoc ve nut Parent
    while(node->Parent!=NULL){
    
        stackPrint.push(node);
        node= node->Parent;
    }
   
    stackPrint.push(node);
    //in ra thu tu hanh dong chuyen nuoc
    int no_action = 0;
    while(!stackPrint.empty()){
        
        cout << "\nAction " << no_action << " : "<<  action[stackPrint.top()->no_funtion];
        print(stackPrint.top()->state);
        stackPrint.pop();
        no_action++;
    }
}

int main(){
    State cur_state = {0,0};
    Node* p = DFS(cur_state);
    print_WayToGetGoal(p);

    

    return 0;
}

