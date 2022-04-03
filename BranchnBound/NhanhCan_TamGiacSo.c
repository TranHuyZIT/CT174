#include <stdio.h>
#define size 50

void readFromFile(int a[][size], int* n){
	FILE* f = fopen("tamgiacso.txt", "r");
	if(f == NULL){
		printf("Loi mo file\n");
		return;
	}
	int i = 0, j;
	fscanf(f, "%d", n);
	for(i = 0 ; i < *n; i++){
		for(j = 0 ; j <= i ; j++){
			fscanf(f, "%d", &a[i][j]);
		}
	}
	fclose(f);
	return;	
}

void printData(int a[][size], int n){
	int i, j;
	for(i = 0 ; i < n; i++){
		printf("\n");
		for(j = 0 ; j < n; j++){
			printf("%d ", a[i][j]);
		}
	}
	printf("\n");
}

int max(int a[][size], int i){
	int j, maxVal = a[i][0];
	for(j = 0 ; j <= i; j ++){
		if (maxVal < a[i][j]){
			maxVal = a[i][j];
		}
	}
	return maxVal;
}

int max3(int a, int b, int c){
	int tmp = a > b ? a : b;
	return tmp > c ? tmp : c;
}

int maxNext(int a[], int j){
	if (j == 0){
		return a[0] > a[1]? a[0] : a[1];
	}
	return max3(a[j-1], a[j], a[j+1]);
}

void Can_Tren(int i, int j, int a[][size], int TGT, int* CT, int n){
	int k;
	*CT = TGT + maxNext(a[i + 1], j);
	for(k = 0 ; k <= i ; k++){
		*CT += max(a, k);
	}
}

void Tao_Nut_Goc(int * TGT, int* CT, int* GTLNTT, int x[], int a[][size], int n){
	(*TGT) = a[0][0];
	Can_Tren(0, 0, a, *TGT, CT, n);
	*GTLNTT = *TGT;
	x[0] = *TGT;
}

void CapNhat_PATN(int TGT, int* GTLNTT, int x[], int PA[], int n){
	int i;
	if (*GTLNTT < TGT){
		*GTLNTT = TGT;
		for(i = 0 ; i < n; i++){
			PA[i] = x[i];
		}
	}
}

void Nhanh_Can(int i, int j, int a[][size], int* TGT, int* CT, int* GTLNTT, int x[], int PA[], int n){
	int k;
	int dau, cuoi;
	if (j == 0){
		dau = 0;
		cuoi = 1;
	}
	else{
		dau = j-1;
		cuoi = j + 1;
	}
	for(k = dau; k <= cuoi; k++){
		*TGT += a[i][k];
		Can_Tren(i, k, a, *TGT, CT, n);
		if (*CT > *GTLNTT){
			x[i] = a[i][k]; // thành phan thu i cua phuong an tot nhat tam thoi x
			if (i == n - 1){ // Xet den dong cuoi cung cua tam giac so
				CapNhat_PATN(*TGT, GTLNTT,x,PA,n);
			}
			else{
				Nhanh_Can(i+1,k,a,TGT,CT,GTLNTT,x,PA,n);
			}
		}
		// Quay lui
		x[i] = 0;
		*TGT -= a[i][k];
	}
}

int GiaPA(int PA[], int n){
	int sum = 0;
	int i;
	for(i = 0 ; i < n; i++){
		sum+= PA[i];
	}
	return sum;
}

void InPA(int PA[], int n){
	printf("\n");
	int i;
	for(i = 0 ; i < n ; i++){
		printf("%d ", PA[i]);
	}
	printf("\nGia cua Phuong An la: %d", GiaPA(PA, n));
}

int main(){
	int a[size][size];
	int n;
	readFromFile(a, &n);
	printData(a, n);
	
	int x[n];
	int PA[n];
	int CT, TGT, GLNTT;
	Tao_Nut_Goc(&TGT,&CT,&GLNTT,x,a,n);
	Nhanh_Can(1,0,a,&TGT,&CT,&GLNTT,x,PA,n);
	InPA(PA, n);
	
	return 0;
}
