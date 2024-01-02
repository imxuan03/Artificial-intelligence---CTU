#include <stdio.h>
#include <stdlib.h>

#define Maxlength 100
#define goal 6
#define tankcapacity_X 9
#define tankcapacity_Y 4
#define empty 0

const char* action[]= {
    "First state", "pour Water Full X", "pour Water Full Y", "pour Empty X", "pour Empty Y",
    "pour Water X to Y", "pour Water Y to X"
};

typedef struct 
{
    /* data */
    int x;
    int y;
}State;

void makenullState(State *S){
    S->x =0;
    S->y =0;
}

void print_State(State S){
    printf("\nX : %d --- Y : %d", S.x, S.y);
}

int checkgoal(State S){
    return S.x == goal || S.y == goal;
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

    if(cur_state.y<tankcapacity_Y){
        result->x = cur_state.y;
        result->y = tankcapacity_Y;
        return 1;
    }
    return 0;
}

int pourEmptyX(State cur_state, State *result){
    if(cur_state.x>0){
        result->x =0;
        result->y = cur_state.y;
        return 1;
    }
    return 0;
}
int pourEmptyY(State cur_state, State *result){
    if(cur_state.y>0){
        result->x =cur_state.x;
        result->y = 0;
        return 1;
    }
    return 0;
}

int max(int a, int b){
    return a>b?a:b;
}

int min(int a, int b){
    return a<b?a:b;
}

int pourWaterXY(State cur_state, State *result){
    if(cur_state.x>0 && cur_state.y<tankcapacity_Y){
        result->x = max(cur_state.x - (tankcapacity_Y-cur_state.y) ,0);
        result->y = min(cur_state.x+cur_state.y , tankcapacity_Y );
        return 1;
    }
    return 0;
}

int pourWaterYX(State cur_state, State *result){
    if(cur_state.x<tankcapacity_X && cur_state.y >0){
        result->x = min(cur_state.x + cur_state.y, tankcapacity_X);
        result->y = max(0, cur_state.y - (tankcapacity_X- cur_state.x));
        return 1;
    }
    return 0;
}

int call_operators(State cur_state, State *result, int opt){
    switch(opt){
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
            return pourWaterYX(cur_state , result);
        default:
            printf("Error call operators.");
            return 0;
    }
}
//=========================================================================
//khai bao Node
typedef struct Node
{
    /* data */
    State state;
    struct Node* Parent;
    int no_funtion;
}Node;

//Khai bao hang doi

typedef struct
{
    /* data */
    Node* Element[Maxlength];
    int front, rear;
}Queue;

void makenullQueue(Queue *Q){
    Q->front = -1;
    Q->rear = -1;
}
int isFullQueue(Queue Q){
    return (Q.rear - Q.front) + 1 == Maxlength;
}
int isEmptyQueue(Queue Q){
    return Q.front == -1;
}
//them 
void push(Queue *Q, Node* node){
    if(!isFullQueue(*Q)){
        if(isEmptyQueue(*Q)){
            Q->front=0;
        }
        Q->rear++;
        Q->Element[Q->rear] = node;

    }else{
        printf("Queue is full.");
    }
}
//xoa
void pop(Queue *Q){
    if(!isEmptyQueue(*Q)){
        Q->front++;
        if(Q->front>Q->rear)
            makenullQueue(Q);
    }else{
        printf("Queue is empty.");
    }
}
//lay ra
Node* front(Queue Q){
    return Q.Element[Q.front];
}

int compareStates(State s1, State s2){
    if(s1.x==s2.x &&s1.y==s2.y)
        return 1;
    
    return 0;
}
int find_State(State state, Queue openQueue){
    while(!isEmptyQueue(openQueue)){
        if(compareStates(front(openQueue)->state,state ))
            return 1;
        else    
            pop(&openQueue);
    }
    return 0;
}

Node* BFS(State state){

    Queue open_BFS;
    Queue close_BFS;
    makenullQueue(&open_BFS);
    makenullQueue(&close_BFS);

    Node* root = (Node*)malloc(sizeof(Node));
    root->no_funtion = 0;
    root->Parent = NULL;
    root->state = state;
    push(&open_BFS, root);
    while(!isEmptyQueue(open_BFS)){

        Node* node = front(open_BFS);
        pop(&open_BFS);
        push(&close_BFS, node);
        
        if(checkgoal(node->state))
            return node;

        int opt ;
        for(opt =1;opt<=6; opt++){
            State newState;
            makenullState(&newState);
            if(call_operators(node->state, &newState, opt)){

                if(find_State(newState, open_BFS)|| find_State(newState, close_BFS))
                    continue;

                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->Parent = node;
                newNode->no_funtion = opt;
                push(&open_BFS, newNode);

            }
        }


    }

}

void print_WaytoGetGoal(Node* node){

    Queue Q;
    makenullQueue(&Q);

    while(node->Parent!=NULL){
        push(&Q, node);
        node = node->Parent;
    }
    push(&Q, node);

    int i;
    for(i = Q.rear; i>= Q.front; i--){
        printf("\nAction %d : %s", Q.rear-i, action[Q.Element[i]->no_funtion]);
        print_State(Q.Element[i]->state);
    }


}
int main(){
    
    State cur_state = {0,0};
    Node* p = BFS(cur_state);
    print_WaytoGetGoal(p);

    return 0;
}