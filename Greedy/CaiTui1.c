#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char tenDV[20];
	float TL, GT, DG;
	int soDV_Dc_Chon;
}DoVat;

DoVat * readFromFile(float* W, int* n){
	FILE* file = fopen("CaiTui1.txt", "r");
	if (file){
		fscanf(file, "%f", W);
		DoVat* dsdv = (DoVat*)malloc(sizeof(DoVat));
		int i = 0;
		while(!feof(file)){
			fscanf(file, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
			dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
			dsdv[i].soDV_Dc_Chon = 0;
			i++;
			dsdv = realloc(dsdv, (sizeof(DoVat))*(i+1));
		}
		*n = i;
		fclose(file);
		return dsdv;
	}
	else{
		printf("Loi Mo File. \n");
	}
}

void swap(DoVat* x, DoVat* y){
	DoVat tmp = (*x);
	(*x) = (*y);
	(*y) = tmp;
}

void bubbleSort(DoVat* dsdv, int n){
	int i, j;
	for(i = 0; i <= n - 2; i++){
		for(j = n-1; j >= i + 1; j--){
			if (dsdv[j].DG > dsdv[j-1].DG){
				swap(&dsdv[j], &dsdv[j-1]);
			}
		}
	}
}


void inDSDV(DoVat* dsdv, int n, float W){
	int i;
	for(i = 0; i < n ; i++){
		printf("%-3d%-20s%9.2f%9.2f%8d    \n",i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].DG, dsdv[i].soDV_Dc_Chon);
	}
}

void Greedy(DoVat* dsdv, int n, float W){
	int i ;
	for(i =  0 ; i < n; i++){
		dsdv[i].soDV_Dc_Chon = (W / dsdv[i].TL);
		W = W - (dsdv[i].soDV_Dc_Chon) * (dsdv[i].TL);
	}
}

int main(){
	int n;
	float W;
	DoVat* dsdv;
	dsdv = readFromFile(&W, &n);
	printf("Trong Luong Cai Ba Lo Ban Dau La: %.2f\n", W);
	printf("Danh Sach Do Vat Ban Dau: \n");
	inDSDV(dsdv, n, W);
	printf("\n");
	bubbleSort(dsdv, n);
	Greedy(dsdv, n, W);
	printf("Phuong An Chon Do Vat: \n");
	inDSDV(dsdv, n, W);
	return 0;
}
