#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char tenDV[20];
	float TL, GT, DG;
	int SL, SoDV_DcChon;
}DoVat;


DoVat* readFromFile(float* W, int* n){
	FILE* f;
	DoVat* dsdv;
	f = fopen("CaiTui3.TXT", "r");
	fscanf(f, "%f", W);
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].tenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].SL;
		dsdv[i].SoDV_DcChon = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat)* (i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}

void swap(DoVat* x, DoVat* y){
	DoVat temp;
	temp = *(x);
	*(x) = *(y);
	*(y) = temp;
}

void bubbleSort(DoVat* a, int n){
	int i = 1, j;
	for( i = 0 ; i <= n - 2; i++){
		for(j = n - 1; j >= i + 1; j --){
			if (a[j-1].DG > a[j]. DG){
				swap(&a[j-1], &a[j]);
			}
		}
	}
}

void inDSDV(DoVat* dsdv, int n){
	printf("Phuong An Chon Do Vat la: \n");
	printf("STT - Ten Do Vat - T.Luong - Gia Tri - S.Luong - Don Gia - SoDV_DcChon -\n");
	float tongTl = 0, tongGt = 0;
	int i;
	for(i = 0 ; i < n; i++){
		printf("%d %-20s %-15.2f %-9.2f %-5d %-9.2f %-8d\n", i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].SL , dsdv[i].DG, dsdv[i].SoDV_DcChon);
		tongTl += dsdv[i].TL*dsdv[i].SoDV_DcChon;
		tongGt += dsdv[i].GT*dsdv[i].SoDV_DcChon;
	}
	printf("Tong Trong Luong: %-9.2f\n", tongTl);
	printf("Tong Gia Tri: %-9.2f\n", tongGt);
}

void Tao_Nut_Goc(float W, float* TLConLai, float* CT, float* GLNTT, float* TGT, float DGLN){
	*TGT = 0;
	*TLConLai = W;
	*CT = (*TLConLai)*(DGLN);
	*GLNTT = 0;
}

void CapNhatPATN(float TGT, float* GLNTT, int x[], DoVat* dsdv, int n){
	int i;
	if (*GLNTT < TGT){
		(*GLNTT) = TGT;
		for(i = 0 ; i < n; i++){
			dsdv[i].SoDV_DcChon = x[i];
		}
	}
}

int min(int a, int b){
	return a > b? b : a; 
}

void Nhanh_Can(int i, float* TGT, float* CT, float* TLConLai, float* GLNTT,  int x[], DoVat* dsdv, int n){
	int j;
	int SoDV_Lon_Nhat_Dc_Chon = min(dsdv[i].SL, (*TLConLai)/dsdv[i].TL);
	for(j = SoDV_Lon_Nhat_Dc_Chon; j >= 0; j --){
		*TGT = *TGT + j*dsdv[i].GT;
		*TLConLai = *TLConLai - j*dsdv[i].TL;
		*CT = (*TLConLai)*(dsdv[i+1].DG) + *TGT;
		
		if (*CT > *GLNTT){
			x[i] = j;
			if ((i == n - 1 )|| (*TLConLai == 0)){
				CapNhatPATN(*TGT, GLNTT, x, dsdv, n);
			}
			else{
				Nhanh_Can(i + 1, TGT, CT, TLConLai, GLNTT, x, dsdv, n);
			}
		}
		x[i] = 0;
		*TLConLai += j*dsdv[i].TL;
		*TGT -= j*dsdv[i].GT;
	}	
}

int main(){
	DoVat* dsdv;
	int n;
	float W, TGT, GLNTT, CT, TLConLai;
	dsdv = readFromFile(&W, &n);
	bubbleSort(dsdv, n);
	int x[n];
	Tao_Nut_Goc(W, &TLConLai, &CT, &GLNTT, &TGT, dsdv[0].DG);
	Nhanh_Can(0, &TGT, &CT, &TLConLai, & GLNTT, x, dsdv, n);
	inDSDV(dsdv, n);
	
	
}
