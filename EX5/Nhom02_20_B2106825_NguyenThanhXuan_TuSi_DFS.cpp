#include <iostream>
#include <queue>
#include <cstdlib>
#include <stack>

using namespace std;

#define Maxlength 1000
#define tankcapacity_Monk 3
#define tankcapacity_Devil 3

const char* action[]={
    "First State", "Move 1 Monk", "Move 1 Devil", "Move 2 Monk", "Move 2 Devil",
    "Move 1 Monk and 1 Devil"
};
//Luôn tính là đang đứng bên bờ A. Muốn tính số thầy chùa và số con quỷ bên bờ B thì tự trừ ra.

typedef struct 
{
    /* data */
    int Monk;
    int Devil;
    int pos_boat; //0: thuyen ben A , 1 : thuyen ben B
}State;

void makenullState(State *S){
    S->Monk = 3;
    S->Devil = 3;
    S->pos_boat = 0;
}

int checkGoal(State S){
    return (S.Monk == 0 && S.Devil == 0 && S.pos_boat == 1);
}

int checkDead(State state){
    if((state.Monk>0 && state.Monk<state.Devil) || (3-state.Monk>0 && 3-state.Monk<3-state.Devil) )
        return 1;
    
    return 0;
}

void printState(State S){
    printf("\nMonk : %d --- Devil : %d --- Ben Bo : ", S.Monk, S.Devil);
    if(S.pos_boat == 0){
        printf("A");
    }else{
        printf("B");
    }
}

int Move1Monk(State cur_state, State *result)
{
  
        if(cur_state.pos_boat==0 ){
            //ben bo A
            if(cur_state.Monk>0){
                
                    result->Monk = cur_state.Monk-1;
                    result->Devil = cur_state.Devil;
                    result->pos_boat = 1;
                    return 1;
                             
            }
        }else{
            //ben bo B
            if(cur_state.Monk<3){
                
                    result->Monk = cur_state.Monk+1;
                    result->Devil = cur_state.Devil;
                    result->pos_boat = 0;
                    return 1;
                              
            }
        }
    
    return 0;
}
int Move1Devil(State cur_state, State *result)
{
   
        if(cur_state.pos_boat == 0 ){
            //bo A
            if(cur_state.Devil>0){
              
                    result->Devil = cur_state.Devil-1;
                    result->Monk = cur_state.Monk;
                    result->pos_boat = 1;
                    return 1;
                          
            }
        }else{
            //bo B
            if(cur_state.Devil <3){
                
                    result->Devil = cur_state.Devil+1;
                    result->Monk = cur_state.Monk;
                    result->pos_boat = 0;
                    return 1;
                            
            }
        }
    
    return 0;
}
int Move2Monk(State cur_state, State *result)
{

        if(cur_state.pos_boat==0  ){
            //ben bo A
            if(cur_state.Monk>=2){
                
                    result->Monk = cur_state.Monk-2;
                    result->Devil = cur_state.Devil;
                    result->pos_boat = 1;
                    return 1;
                           
            }
        }else{
            //ben bo B
            if(cur_state.Monk<=1 ){
                
                  result->Monk = cur_state.Monk+2;
                    result->Devil = cur_state.Devil;
                    result->pos_boat = 0;
                    return 1;  
                              
            }
        }

    return 0;
    
}
int Move2Devil(State cur_state, State *result)
{
   
        if(cur_state.pos_boat == 0){
            //bo A
            if(cur_state.Devil >=2 ){
                
                    result->Devil = cur_state.Devil-2;
                    result->Monk = cur_state.Monk;
                    result->pos_boat = 1;
                    return 1;
                              
            }
        }else{
            //bo B
            if(cur_state.Devil<=1){
                
                    result->Devil = cur_state.Devil+2;
                    result->Monk = cur_state.Monk;
                    result->pos_boat = 0;
                    return 1;
                              
            }
        }

    return 0;
}
int Move1Monk1Devil(State cur_state, State *result)
{

        if(cur_state.pos_boat == 0 ){
            //dang bo ben A
            if(cur_state.Monk>0 && cur_state.Devil>0){
                
                    result->Monk = cur_state.Monk-1;
                    result->Devil = cur_state.Devil -1;
                    result->pos_boat =1;
                    return 1;
                              
            }
        }else{
            //dang bo ben B
            if(cur_state.Monk <3  && cur_state.Devil<3){
                
                    result->Monk = cur_state.Monk+1;
                    result->Devil = cur_state.Devil + 1;
                    result->pos_boat =0;
                    return 1;             
            }
        }


    return 0;
}

int call_operator(State cur_state, State *result, int option){
    switch (option)
    {
    case 1:
        return Move1Monk(cur_state, result);
        break;
    case 2:
        return Move1Devil(cur_state, result);
        break;
    case 3:
        return Move2Monk(cur_state, result);
        break;
    case 4:
        return Move2Devil(cur_state, result);
        break;
    case 5:
        return Move1Monk1Devil(cur_state, result);
        break;    
    default:
        printf("Error calls operators\n");
        return 0;
    }
}
typedef struct Node
{
    /* data */
    State state;
    struct Node* Parent;
    int no_funtion;
}Node;

int compareStates(State s1, State s2){
    if(s1.Monk==s2.Monk &&s1.Devil==s2.Devil&&s1.pos_boat==s2.pos_boat)
        return 1;
    
    return 0;
}
int find_State(State state, stack<Node*> Q){
    while(!Q.empty()){
        if(compareStates(Q.top()->state,state ))
            return 1;
      
        Q.pop();
    }
    return 0;
}

Node* DFS(State state){
    stack<Node*> open_DFS;
    stack<Node*> close_DFS;

    Node* root = (Node*)malloc(sizeof(Node));
    root->no_funtion = 0;
    root->Parent = NULL;
    root->state = state;
    open_DFS.push(root);
    
    while(!open_DFS.empty()){

        Node* node = open_DFS.top();
        open_DFS.pop();
        close_DFS.push(node);
    
        
        if(checkGoal(node->state))
            return node;

        int opt ;
        for(opt =1;opt<=5; opt++){
            State newState;
            makenullState(&newState);
            if(call_operator(node->state, &newState, opt)){

                if(find_State(newState, open_DFS)|| find_State(newState, close_DFS) ||checkDead(newState))
                    continue;

                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->Parent = node;
                newNode->no_funtion = opt;
                open_DFS.push(newNode);


            }
        }


    }

}

void print_WaytoGetGoal(Node* node){
   
    stack<Node*> S;

    while(node->Parent!=NULL){
        S.push(node);
        node = node->Parent;
    }
    S.push(node);

    int no_action = 0;
    while(!S.empty()){
        cout << "\nAction " << no_action << " : "<<  action[S.top()->no_funtion];
        printState(S.top()->state);
        S.pop();
        no_action++;
    }

}

int main(){
    State S;
    makenullState(&S);

    Node* d = DFS(S);
    print_WaytoGetGoal(d);


    return 0;
}