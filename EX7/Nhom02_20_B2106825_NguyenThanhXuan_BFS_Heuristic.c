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
    int i,j;
    for(i = 0; i<ROWS;i++){
        for( j =0; j<COLS ; j++){
            printf("|%d ", state.eightPuzzel[i][j]);
        }
        printf("|\n");
    }
    printf("-----------------------\n");
}

int compareStates(State s1, State s2){
    if(s1.emptyCol != s2.emptyCol || s1.emptyRow!=s2.emptyRow)
        return 0;
	int i, j;
    for( i =0; i<ROWS;i++){
        for( j =0; j<COLS; j++){
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

//Khai bao cau truc List
typedef struct{
    Node *Elements[Maxlength];
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
Node* element_at(int p, List L){
    return L.Elements[p-1];
}

void push_List(Node* x, int positon, List *L){
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

//kiem tra trang thai State do co trong close/open khong
Node* find_State(State state, List L, int *position){
	int i;
    for( i =1; i<=L.size;i++){
        if(compareStates(element_at(i,L)->state, state)){
            *position = i;
            return element_at(i, L);
        }
    }
    return NULL;
}
//sap xep danh sach
void sort_List(List *L){
	int i, j;
    for( i = 0 ; i<L->size-1;i++){
        for( j = i+1; j<L->size;j++){
            if(L->Elements[i]->heuristic > L->Elements[j]->heuristic){
                Node* node = L->Elements[i];
                L->Elements[i]= L->Elements[j];
                L->Elements[j]= node;
            }
        }
    }
}

int heuristic(State state, State goal){
    int count =0;
    int i, j;
    for( i = 0; i<ROWS;i++){
        for( j =0; j<COLS ; j++){
            if(state.eightPuzzel[i][j]!=goal.eightPuzzel[i][j])
                count++;
        }
    }
    return count;
}

void print_WaystoGetGoal(Node* node){
    List listPrint;
    makenullList(&listPrint);
    while(node->Parent!=NULL){
        push_List(node, listPrint.size+1, &listPrint );
        node = node->Parent;
    }
    push_List(node, listPrint.size+1, &listPrint );

    int no_action = 0;
    int i;
    for( i = listPrint.size; i>0; i--){
        printf("\nAction : %d : %s", no_action, action[element_at(i, listPrint)->no_funtion]);
        printState(element_at(i, listPrint)->state);
        no_action++;
    }
}

Node* best_first_search(State state, State goal){
    List open_BFS, close_BFS;
    makenullList(&open_BFS);
    makenullList(&close_BFS);
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->no_funtion = 0;
    root->heuristic = heuristic(root->state,goal);
    push_List(root, open_BFS.size+1, &open_BFS);
    while(!emptyList(open_BFS)){
        Node* node = element_at(1, open_BFS);
        delete_List(1, &open_BFS);
        push_List(node, close_BFS.size+1, &close_BFS);
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
                int pos_open,pos_close;
                Node* nodeFoundOpen = find_State(newState,open_BFS,&pos_open);
                Node* nodeFoundClose = find_State(newState,close_BFS,&pos_close);

                if(nodeFoundOpen==NULL && nodeFoundClose==NULL){
                    push_List(newNode, open_BFS.size+1, &open_BFS);

                }else if(nodeFoundOpen!=NULL && nodeFoundOpen->heuristic>newNode->heuristic){
                    delete_List(pos_open, &open_BFS);
                    push_List(newNode, pos_open, &open_BFS);
                }else if(nodeFoundClose!=NULL && nodeFoundClose->heuristic>newNode->heuristic){
                    delete_List(pos_close, &close_BFS);
                    push_List(newNode, open_BFS.size+1, &open_BFS);
                }
    
                sort_List(&open_BFS);
            }
        }

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