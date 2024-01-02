#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;

const char* action[]= {
	"First State", "Flip 1-2-3", "Flip 2-3-4","Flip 3-4-5","Flip 4-5-6"
};

#define NumGlasses 6
#define Up 1
#define Down -1

typedef struct 
{
    int Glasses[NumGlasses];
}State;
void makenullState(State *state){

    for(int i = 0; i<NumGlasses; i++){
        if(state->Glasses[i]%2 ==0)
            state->Glasses[i]= Up;
        else    
            state->Glasses[i]= Down;
    }
}
void printState(State S){
    cout<<"\n";
    for(int i = 0; i<NumGlasses ; i++){
        if(S.Glasses[i]==Up)
            cout<< "U   ";
        else
            cout<< "D   ";
    }
}
int goalCheck(State S){
    for(int i = 0; i<NumGlasses; i++){
        if(S.Glasses[i] == Down)
            return 0;
    }
    return 1;
}

void flipGlasses(State cur_state, State *result, int k){
	for(int i = 0; i< NumGlasses; i++){
		result->Glasses[i] = cur_state.Glasses[i];
	}

	result->Glasses[k-1]=-cur_state.Glasses[k-1];
	result->Glasses[k]=-cur_state.Glasses[k];
	result->Glasses[k+1]=-cur_state.Glasses[k+1];
}

//========================

typedef struct Node{
    State state;
    struct Node* Parent;
    int no_funtion;
}Node;

int compareStates(State s1, State s2) {
	int i;
	for(i=0; i<NumGlasses; i++) {
		if(s1.Glasses[i]!=s2.Glasses[i])
			return 0;
	}
	return 1;
}

int findState(State state, stack<Node*> Open) {
	while(!Open.empty()) {
		if(compareStates(Open.top()->state, state))
			return 1;
		
        Open.pop();
	}
	return 0;
}
Node* DFS_Algorithm(State state) {
	stack<Node*> open_DFS;
    stack<Node*> close_DFS; 
	/* Tao nut trang thai cha */
	Node* root=(Node*)malloc(sizeof(Node));
	root->state=state;
	root->Parent=NULL;
	root->no_funtion=0;
	open_DFS.push(root);
	
	while(!open_DFS.empty()) {
		/* Lay dinh trong Stack */
		Node* node=open_DFS.top();
		open_DFS.pop();
		close_DFS.push(node);
		/* Kiem tra trang thai muc tieu */
		if(goalCheck(node->state))
			return node;
		/* Goi cac phep toan */
		int opt;
		for(opt=1; opt<=4; opt++) {
			State new_state;
			makenullState(&new_state);
            flipGlasses(node->state, &new_state, opt);
			/* Neu ton tai thi bo qua */
			if(findState(new_state, open_DFS) || findState(new_state, close_DFS))
				continue;
				
			Node* new_node=(Node*)malloc(sizeof(Node));
			new_node->state=new_state;
			new_node->Parent=node;
			new_node->no_funtion=opt;
			open_DFS.push(new_node);
		}
	}
	return NULL;
}

void printWaysToGetGoal(Node* node) {
	stack<Node*> S;
	/* Duyet nguoc ve nut parent */
	while(node->Parent!=NULL) {
		S.push(node);
		node=node->Parent;
	}
	S.push(node);
	/* In ra thu tu */
	int no_action=0;
	while(!S.empty()) {
		printf("\nAction %d: %s", no_action, action[S.top()->no_funtion]);
		printState(S.top()->state);
		S.pop();
		no_action++;
	}
}

int main() {
	State cur_state={Up, Down, Up, Down, Up, Down};
	Node* p=DFS_Algorithm(cur_state);
	printWaysToGetGoal(p);
	return 0;
}