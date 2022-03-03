#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef int keytype;
typedef float othertype;
typedef struct{
	keytype key;
	othertype value;
} recordtype;

void swap(recordtype* x, recordtype* y){
	recordtype temp;
	temp = *(x);
	*(x) = *(y);
	*(y) = temp;
}

void readData(recordtype a[], int* n){
	FILE* file = fopen("data.txt", "r");
	int i = 0;
	if (file != NULL){
		while(!feof(file)){
			fscanf(file, "%d%f", &a[i].key, &a[i].value);
			i++;	
		}
	}
	else{
		printf("Error occured while open file");
	}
	fclose(file);
	*n = i;
}

void printData(recordtype a[], int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d %f\n", a[i].key, a[i].value);
	}
}


