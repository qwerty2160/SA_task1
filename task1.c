#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

int n = 0, m = 0;
char abc[] = "abcdhfgijkln";
int *exp_numbers;
char **table0;
int **table1, **rmoreMatrix;
int ***cannonicalMatrices;

void getDataFromUser(){
	printf("Введите количество экспертов: ");
	scanf("%d", &n);
	printf("Введите количество вариантов: ");
	scanf("%d", &m);
	exp_numbers = (int*)malloc(n*sizeof(int));
	table0 = (char**)malloc(m*sizeof(char *));
	for(char i=0;i<m;++i) {table0[i] = (char*)malloc(n*sizeof(char));}	
	for (int i=0; i<n; ++i){
		printf("Номер эксперта %d: ", i+1);
		scanf("%d", &exp_numbers[i]);
	}
	printf("\nВвод исходной таблицы:\n\n");
	printf("  ");
	for (int i=0; i<n; ++i){printf("E%d ", exp_numbers[i]);}
	printf("\n");
	for (int i=0; i<m; ++i){
		printf("V%d:", i+1);
		char str_tmp[n+1];
		scanf("%s", str_tmp);
		for (int j=0; j<n; ++j){table0[i][j] = str_tmp[j];}
	}
}

void createTable1(){	
	table1 = (int**)malloc(m*sizeof(int*));
	for(int i= 0;i<m;++i) {table1[i] = (int*)malloc(n*sizeof(int));}
	printf("\nТаблица 1. Участники экспертного опроса и ранжируемые объекты.\n\n\t");
	for(int i=0; i<n; ++i){printf("E%d\t", exp_numbers[i]);}
	printf("\n");
	for(int i=0; i<m; ++i){
		printf("V%d%c:\t", i+1, abc[i]);
		for(int j=0; j<n; ++j){
			for(int t=0; t<sizeof(abc)/sizeof(char); ++t){
				if(table0[i][j]==abc[t]){
					table1[i][j] = t+1;
					printf("V%d\t", table1[i][j]);
					break;
				}
			}
		}
		printf("\n");
	}
}

void createCannonicalMatrices(){
	cannonicalMatrices=(int***)malloc(n*(sizeof(int**)));
	for(int i=0; i<n; ++i){
		cannonicalMatrices[i]=(int**)malloc(m*sizeof(int*));
		for(int j=0; j<m; ++j){cannonicalMatrices[i][j]=(int*)malloc(m*sizeof(int));}
	}
	for(int i=0; i<n; ++i){		
		int *exp_list = (int*)malloc(m*sizeof(int));
		for(int j=0; j<m; ++j){exp_list[j]=table1[j][i];}
		for(int j=0; j<m; ++j){
			for(int t=0; t<m; ++t){
				int exp_list_index_t = 0, exp_list_index_j = 0;
				for(int z=0; z<m; ++z){if(exp_list[z]==j+1){exp_list_index_j=z;	break;}}
				for(int z=0; z<m; ++z){if(exp_list[z]==t+1){exp_list_index_t=z;	break;}}
				if(exp_list_index_t>exp_list_index_j){cannonicalMatrices[i][j][t]=1;}
				else if(exp_list_index_t<exp_list_index_j){cannonicalMatrices[i][j][t]=-1;}
				else{cannonicalMatrices[i][j][t] = 0;}
			}			
		}		
		free(exp_list);
	}
	for(int i=0; i<n; ++i){
		printf("\nМатрица упорядочения в канонической форме для эксперта E%d.\n\nE%d\t", exp_numbers[i], exp_numbers[i]);
		for(int j=0; j<m; ++j){printf("V%d\t", j+1);}
		printf("\n");
		for(int j=0; j<m; ++j){
			printf("V%d\t", j+1);
			for(int t=0; t<m; ++t){printf("%d\t", cannonicalMatrices[i][j][t]);}
			printf("\n");
		}
	}
	
}

int kemeni(int **x, int **y){
	int s = 0;
	for(int i=0; i<m; ++i){
		for(int j=0; j<m; ++j){
			int tmp = x[i][j]-y[i][j];
			if (tmp<0){s+=tmp*-1;}
			else{s+=tmp;}
		}
	}
	return s*0.5;
}

void createRmore(){
	rmoreMatrix = (int**)malloc((n+1)*sizeof(int*));
	for(int i=0;i<(n+1);++i) {rmoreMatrix[i] = (int*)malloc((n+3)*sizeof(int));}
	rmoreMatrix[n][n] = 0;
	rmoreMatrix[n][n+1] = 0;
	int min_square_s = INT_MAX;
	for(int i=0; i<n; ++i){
		int s = 0, square_s = 0;		
		for(int j=0; j<n; ++j){
			rmoreMatrix[i][j]=kemeni(cannonicalMatrices[i], cannonicalMatrices[j]);
			s+=rmoreMatrix[i][j];
			square_s+=rmoreMatrix[i][j]*rmoreMatrix[i][j];			
		}
		if(square_s<min_square_s){min_square_s=square_s;}
		rmoreMatrix[i][n+1] = square_s;		
		rmoreMatrix[n][n] += s;
		rmoreMatrix[n][i] = s;
		rmoreMatrix[i][n] = s;
	}
	rmoreMatrix[n][n+1] = min_square_s;
	for(int i=0; i<n; ++i){
		if(rmoreMatrix[n][n+1]==rmoreMatrix[i][n+1]){
			rmoreMatrix[i][n+2]=1;
		}
		else{
			rmoreMatrix[i][n+2]=0;
		}
	}
	
	printf("\nРасстояния между ответами-ранжированиями экспертов E%d-E%d.\n\n",exp_numbers[0], exp_numbers[n-1]);
	printf("Dij\t");
	for(int i=0; i<n; ++i){printf("E%d\t", exp_numbers[i]);}
	printf("ΣрК\tΣкрК\tНСР\n");
	for(int i=0; i<n+1; ++i){
		if(i<n){printf("E%d\t", exp_numbers[i]);}
		else{printf("Σ\t");}
		for(int j=0; j<n+3; ++j){printf("%d\t",rmoreMatrix[i][j]);}
		printf("\n");
	}
}

void freeMem(){	
	for(int i=0; i<m; ++i){free(table0[i]);}
	free(table0);
	for(int i=0; i<m; ++i){free(table1[i]);}
	free(table1);
	for(int i=0; i<(n+1); ++i){free(rmoreMatrix[i]);}
	free(rmoreMatrix);
	free(exp_numbers);
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){free(cannonicalMatrices[i][j]);}
		free(cannonicalMatrices[i]);
	}
	free(cannonicalMatrices);
	for(int i=0; i<n; ++i){
		cannonicalMatrices[i]=(int**)malloc(m*sizeof(int*));
		for(int j=0; j<m; ++j){cannonicalMatrices[i][j]=(int*)malloc(m*sizeof(int));}
	}
}

int main(){
	setlocale(LC_ALL, "Russian");
	getDataFromUser();
	createTable1();
	createCannonicalMatrices();
	createRmore();
	freeMem();
	return EXIT_SUCCESS;
}
