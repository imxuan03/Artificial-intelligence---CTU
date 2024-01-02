#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
#define empty 0

typedef struct{
	int queens[SIZE];
}Queen;

void init_Queen(Queen *Q){
	int i;
	for(i=0; i<SIZE; i++)
		Q->queens[i] = 0;
}

void print_Queen(Queen Q){
	int i, j;
	for(i=0; i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			if(Q.queens[i] == j)
				printf("Q  ");
			else
				printf(".  ");		
		}
		printf("\n");
	}

	printf("\nDo you want to see more? (y/n)\n");
	if(getchar() == 'y'){
		fflush(stdin);
		printf("=============================\n");
	}
	else
		exit(1);
}

int Constrains(Queen Q, int i, int j){
	int k;
	for(k=0; k<i; k++)
		if(Q.queens[k] == j || abs(k - i) == abs(Q.queens[k] - j))
			return 0;
	return 1;	
}

void Queen_Back_Tracking(Queen *Q, int idx){
	int j;
	for(j=0; j<SIZE; j++){
		if(Constrains(*Q, idx, j)){
			Q->queens[idx] = j;
			
			if(idx == SIZE - 1)
				print_Queen(*Q);
			else
				Queen_Back_Tracking(Q, idx+1);
			
			Q->queens[idx] = 0;
		}
	}
}

int main(){
	Queen Q;
	Queen_Back_Tracking(&Q, 0);
	return 0;
}
