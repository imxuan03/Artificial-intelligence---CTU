#include <stdio.h>

#define MAX_N 100
#define EMPTY 0

const char* name[]={"", "WA", "NT", "Q", "NSW", "V", "SA", "T"};
const char* color[]={"", "Red", "Green", "Blue"};

typedef struct{
    int n;
    int A[MAX_N][MAX_N];
    int color[MAX_N];
}Graph;

void initGraph(int n, Graph *G){
    G->n= n;
    for(int i = 1; i<= n; i++){
        for(int j =1; j<=n; j++){
            G->A[i][j]=0;
        }
        G->color[i]=0;
    }
}
int adjacent(int x, int y, Graph G){
    return G.A[x][y]!=0;
}
void addEdge(int x, int y, Graph *G){
    G->A[x][y]= 1;
}

int isSafe(int x, int c,Graph G ){
    for(int i =1; i<=G.n;i++){
        if(adjacent(x, i, G)&& G.color[i]==c)
            return 0;
    }
    return 1;
}
int solve(int x, Graph *G){
    if(x>G->n)
        return 1;
    
    for(int c =1; c<=3; c++){
        if(isSafe(x, c, *G)){
            G->color[x]= c;

            if(solve(x+1, G))
                return 1;


            G->color[x]=0;
        }
    }
}
int main(){

    //nhap
    freopen("MAP.txt","r", stdin);
    Graph G;
    int n,x;
    scanf("%d", &n);
    initGraph(n, &G);

    for(int i =0; i<n; i++){
        do{
            scanf("%d", &x);
            if(x>0)
                addEdge(i, x, &G);
        }while(x>0);
    }

    if(solve(1, &G)){
        printf("Solution :\n");
        for(int i = 1; i<= n; i++){
            printf("%s : ", name[i]);
            for(int j =1; j<=3;j++){
                if(G.color[i]==j)
                    printf("%s\n", color[j]);
            }
        }
    }else{
        printf("Not Solve");
    }

}