#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 5
#define Maxlength 200


typedef struct{
	int neighbor[MAX_VERTICES];
	int h;
}Vertices;

typedef struct{
	int num_vertices;
	Vertices v[MAX_VERTICES];
}Graph;

void initGraph(int num_vertices, Graph *G){
	G->num_vertices = num_vertices;
	for(int i = 0; i<num_vertices;i++){
		for(int j =0; j<num_vertices; j++){
			G->v[i].neighbor[j]=0;
			G->v[i].h =0;	
		}
	}
}

const char name[]= {'A', 'B', 'C', 'D', 'G'};

typedef struct{
	int vertex;
}State;

void printState(State s){
	printf("%c ", name[s.vertex]);
}

int compareStates(State s1, State s2){
	return s1.vertex == s2.vertex;
}

typedef struct Node{
	State state; 
	struct Node* Parent;
	int f;
	int g;
	int h;	
}Node;

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
        for( i = position -1; i<L->size;i++){
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

int goalcheck(State state, State goal){
	return compareStates(state, goal);
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
       
        printState(element_at(i, listPrint)->state);
        if(i!=1)
        	printf("->");
        	
        	
        no_action++;
    }
}

void sort_List(List *L){
	int i, j;
    for( i = 0 ; i<L->size-1;i++){
        for( j = i+1; j<L->size;j++){
            if(L->Elements[i]->f > L->Elements[j]->f){
                Node* node = L->Elements[i];
                L->Elements[i]= L->Elements[j];
                L->Elements[j]= node;
            }
        }
    }
}
Node* A_star(Graph G,State state, State goal){
    List open_BFS;
	List close_BFS;
    makenullList(&open_BFS);
    makenullList(&close_BFS);
    Node* root = (Node*)malloc(sizeof(Node));
    root->state = state;
    root->Parent = NULL;
    root->g = 0;
    root->h = G.v[state.vertex].h;
    root->f = root->h + root->g;
    push_List(root, open_BFS.size+1, &open_BFS);
    while(!emptyList(open_BFS)){
        Node* node = element_at(1, open_BFS);
        delete_List(1, &open_BFS);
        push_List(node, close_BFS.size+1, &close_BFS);
        if(goalcheck(node->state, goal))
            return node;

        int opt;
        for(opt = 0; opt<G.num_vertices; opt++){
            State newState;
            
            if(G.v[node->state.vertex].neighbor[opt]>0){

                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->Parent = node;
                newNode->state.vertex = opt;
       
                newNode->g = node->g + G.v[node->state.vertex].neighbor[opt];
                newNode->h = G.v[opt].h;
                newNode->f = newNode->g+newNode->h;

                //kiem tra trang thai moi xin ra co thuoc Open/close
                int pos_open,pos_close;
                Node* nodeFoundOpen = find_State(newNode->state,open_BFS,&pos_open);
                Node* nodeFoundClose = find_State(newNode->state,close_BFS,&pos_close);

                if(nodeFoundOpen==NULL && nodeFoundClose==NULL){
                    push_List(newNode, open_BFS.size+1, &open_BFS);

                }else if(nodeFoundOpen!=NULL && nodeFoundOpen->g>newNode->g){
                    delete_List(pos_open, &open_BFS);
                    push_List(newNode, pos_open, &open_BFS);
                }else if(nodeFoundClose!=NULL && nodeFoundClose->g>newNode->g){
                    delete_List(pos_close, &close_BFS);
                    push_List(newNode, open_BFS.size+1, &open_BFS);
                }
    
                
            }
        }
		sort_List(&open_BFS);
    }
	return NULL;
}


int main(){
	Graph graph;
	initGraph(MAX_VERTICES,&graph);
	for(int i = 0; i<MAX_VERTICES;i++){
		int x;
		scanf("%d", &x);
		graph.v[i].h = x;
		for(int j = 0; j<MAX_VERTICES;j++){
			scanf("%d", &x);
			graph.v[i].neighbor[j] = x;
		}
	}
	State A, G;
	A.vertex =0;
	G.vertex = 4;
	Node* result = A_star(graph, A, G);
	print_WaystoGetGoal(result);
	
	
	return 0;
}
