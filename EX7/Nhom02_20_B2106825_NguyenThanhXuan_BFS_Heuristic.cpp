#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;


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

//=======================================================
typedef struct Node{
    State state;
    struct Node* Parent;
    int no_funtion;
    int heuristic;
}Node;


//kiem tra trang thai State do co trong close/open khong
Node* find_State(State state, vector<Node*> v, vector<Node*>::iterator *position){
    vector<Node*>::iterator it = v.begin();
    if(v.size()==0)
        return NULL;

    while(it!=v.end()){
        if(compareStates((*it)->state, state)){
            *position = it;
            return *it;
        }
        it= v.erase(it);
    }

    return NULL;
}

int heuristic(State state, State goal){
    int count =0;
    for(int i = 0; i<ROWS;i++){
        for(int j =0; j<COLS ; j++){
            if(state.eightPuzzel[i][j]!=goal.eightPuzzel[i][j])
                count++;
        }
    }
    return count;
}

bool compareHeuristic(Node* a, Node* b){
    return a->heuristic >b->heuristic;
}
void print_WaystoGetGoal(Node* node){
    vector<Node*> listPrint;
    listPrint.clear();
    while(node->Parent!=NULL){
        listPrint.push_back(node);
        node = node->Parent;
    }
    listPrint.push_back(node);

    int no_action = 0;
    for(int i = listPrint.size()-1; i>=0; i--){
        printf("\nAction : %d : %s", no_action, action[listPrint.at(i)->no_funtion]);
        printState(listPrint.at(i)->state);
        no_action++;
    }
}

Node* best_first_search(State state, State goal){
   
    vector<Node*> open_BFS;
    vector<Node*> close_BFS;
    open_BFS.clear();
    close_BFS.clear();
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_funtion = 0;
    root->heuristic = heuristic(root->state,goal);
    open_BFS.push_back(root);
    
    while(!open_BFS.empty()){
        Node* node = open_BFS.back();
        open_BFS.pop_back();
        close_BFS.push_back(node);
        if(goalCheck(node->state, goal))
            return node;

        int opt;
        for(opt = 1; opt<=4; opt++){
            State newState;
            newState = node->state;
            if(call_Operators(node->state,&newState, opt)){

                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->Parent = node;
                newNode->state = newState;
                newNode->no_funtion=opt;
                newNode->heuristic = heuristic(newState, goal);

                //kiem tra trang thai moi xin ra co thuoc Open/close
                vector<Node*>::iterator pos_open,pos_close;
                Node* nodeFoundOpen = find_State(newState,open_BFS,&pos_open);
                Node* nodeFoundClose = find_State(newState,close_BFS,&pos_close);

                if(nodeFoundOpen==NULL && nodeFoundClose==NULL){
                    open_BFS.push_back(newNode);

                }else if(nodeFoundOpen!=NULL && nodeFoundOpen->heuristic>newNode->heuristic){
                    open_BFS.erase(pos_open);
                    open_BFS.push_back(newNode);
                    
                }else if(nodeFoundClose!=NULL && nodeFoundClose->heuristic>newNode->heuristic){
                    
                    close_BFS.erase(pos_close);
                    open_BFS.push_back(newNode);
                }
            }
        }
        sort(open_BFS.begin(), open_BFS.end(), compareHeuristic);

    }

}

int main(){

    State state;
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

    
   
    State goal;
    goal.emptyRow=0;
    goal.emptyCol =0;
    goal.eightPuzzel[0][0] =0;
    goal.eightPuzzel[0][1] =1;
    goal.eightPuzzel[0][2] =2;
    goal.eightPuzzel[1][0] =3;
    goal.eightPuzzel[1][1] =4;
    goal.eightPuzzel[1][2] =5;
    goal.eightPuzzel[2][0] =6;
    goal.eightPuzzel[2][1] =7;
    goal.eightPuzzel[2][2] =8;

    Node* p = best_first_search(state, goal);
    print_WaystoGetGoal(p);

    return 0;
}