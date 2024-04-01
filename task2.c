//gcc task2.c -lm

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int object_number, dimension, n_classes;
char *class_letters;
int *object, *B_arr;
int **classes;

void getDataFromUser(){
	printf("Введите размерность: ");
	scanf("%d", &dimension);
	printf("Количество классов: ");
	scanf("%d", &n_classes);
	class_letters = (char*)malloc(n_classes*sizeof(char));
	printf("Буквы классов (слитно): ");
	scanf("%s", class_letters);
	printf("Введите цифру объекта, M");
	scanf("%d", &object_number);
	object = (int*)malloc(dimension*sizeof(int));
	classes = (int**)malloc(n_classes*sizeof(int *));
	for(int i=0;i<n_classes;++i) {classes[i] = (int*)malloc(dimension*sizeof(int));}
	for(int i=0; i<n_classes; ++i){
		printf("\n");
		for(int j=0; j<dimension; ++j){
			printf("Ввод %d члена класса %c: ", j+1, class_letters[i]);
			scanf("%d", &classes[i][j]);
		}
	}
	printf("\n");
	for(int i=0; i<dimension; ++i){
		printf("Ввод %d члена объекта M%d: ", i+1, object_number);
		scanf("%d", &object[i]);
	}
}

void method1(){
	printf("\n1. Классификация (распознавание) от объектов до центров тяжести классов:\n\n");
	int p_min = INT_MAX, p_min_index, n_min = 0, p_arr[n_classes];
	for(int i=0; i<n_classes; ++i){
		int p=0;
		printf("p(M%d,%c)=√(",object_number, class_letters[i]);
		for(int j=0; j<dimension; ++j){
			p+=pow((classes[i][j]-object[j]), 2);
			printf("(%d-%d)²", classes[i][j], object[j]);
			if(dimension-j>1){printf("+");}
		}
		printf(")=√(%d)\n", p);
		p_arr[i]=p;
		if(p_min>p){
			p_min=p;
			p_min_index=i;
		}
	}
	for(int i=0; i<n_classes; ++i){
		if(p_arr[i]==p_min){
			++n_min;
		}
	}
	if(n_min==1){printf("M%d ∈ %c\n", object_number, class_letters[p_min_index]);}
	else{printf("Отнести невозможно, требуется больше данных\n");}
}

void method3(){
	printf("\n3. Классификация (распознавание) по скалярному произведению:\n\n");
	int B_max = INT_MIN, B_max_index, n_max = 0;
	B_arr = (int*)malloc(n_classes*sizeof(int));
	for(int i=0; i<n_classes; ++i){
		int B=0;
		printf("B(M%d,%c)=",object_number, class_letters[i]);
		for(int j=0; j<dimension; ++j){
			B+=object[j]*classes[i][j];
			printf("%d*%d", object[j], classes[i][j]);
			if(dimension-j>1){printf("+");}
		}
		printf("=%d\n", B);
		B_arr[i]=B;
		if(B_max<B){
			B_max=B;
			B_max_index=i;
		}
	}
	for(int i=0; i<n_classes; ++i){
		if(B_arr[i]==B_max){
			++n_max;
		}
	}
	if(n_max==1){printf("M%d ∈ %c\n", object_number, class_letters[B_max_index]);}
	else{printf("Отнести невозможно, требуется больше данных\n");}
}

void method4(){
	printf("\n4. Классификация (распознавание) с использованием корреляционного метода:\n\n");
	int r_max_index, n_max = 0;
	double r_max = INT_MIN, r_arr[n_classes];
	for(int i=0; i<n_classes; ++i){
		double r=1, tmp=0;
		printf("r(M%d,%c)=%d-(",object_number, class_letters[i], B_arr[i]);
		printf("(");
		for(int j=0; j<dimension; ++j){
			tmp+=object[j];
			printf("%d", object[j]);
			if(dimension-j>1){printf("+");}
		}
		r*=tmp;
		printf(")*(");
		tmp = 0;
		for(int j=0; j<dimension; ++j){
			tmp+=classes[i][j];
			printf("%d", classes[i][j]);
			if(dimension-j>1){printf("+");}
		}
		r*=tmp;
		printf(")");
		r/=dimension;
		r=B_arr[i]-r;

		printf(")/%d=%lg\n", dimension, r);
		r_arr[i]=r;
		if(r_max<r){
			r_max=r;
			r_max_index=i;
		}
	}
	for(int i=0; i<n_classes; ++i){
		if(r_arr[i]==r_max){
			++n_max;
		}
	}
	if(n_max==1){printf("M%d ∈ %c\n", object_number, class_letters[r_max_index]);}
	else{printf("Отнести невозможно, требуется больше данных\n");}
}

void method5(){
	printf("\n5. Классификация (распознавание) по углу между векторами объекта и центра тяжести классов:\n\n");
	int cos_phi_max_index, n_max = 0;
	double cos_phi_max = INT_MIN, cos_phi_arr[n_classes];
	for(int i=0; i<n_classes; ++i){
		double cos_phi=1, tmp=0;
		printf("cosφ(M%d,%c)=%d/(",object_number, class_letters[i], B_arr[i]);
		printf("√(");
		for(int j=0; j<dimension; ++j){
			tmp+=pow(object[j], 2);
			printf("%d²", object[j]);
			if(dimension-j>1){printf("+");}
		}
		cos_phi*=sqrt(tmp);
		printf(")*√(");
		tmp = 0;
		for(int j=0; j<dimension; ++j){
			tmp+=pow(classes[i][j], 2);
			printf("%d²", classes[i][j]);
			if(dimension-j>1){printf("+");}
		}
		cos_phi*=sqrt(tmp);
		printf(")");
		cos_phi=B_arr[i]/cos_phi;
		printf(")=%lg\n", cos_phi);
		cos_phi_arr[i]=cos_phi;
		if(cos_phi_max<cos_phi){
			cos_phi_max=cos_phi;
			cos_phi_max_index=i;
		}
	}
	for(int i=0; i<n_classes; ++i){
		if(cos_phi_arr[i]==cos_phi_max){
			++n_max;
		}
	}
	if(n_max==1){printf("M%d ∈ %c\n", object_number, class_letters[cos_phi_max_index]);}
	else{printf("Отнести невозможно, требуется больше данных\n");}
}

void freeMem(){
	free(class_letters);
	free(object);
	for(int i=0; i<n_classes; ++i){
		free(classes[i]);
	}
	free(classes);
}

int main(){
	getDataFromUser();
	method1();
	method3();
	method4();
	method5();
	freeMem();
	return EXIT_SUCCESS;
}
