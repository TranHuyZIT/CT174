#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char tenDV[20];
	float TL, GT, DG;
	int soDV_Dc_Chon;
}DoVat;

typedef struct{
	int x , f;
} pair;

DoVat * readFromFile(float* W, int* n){
	FILE* file = fopen("Balo.txt", "r");
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

void inDSDV(DoVat* dsdv, int n, float W){
	int i;
	for(i = 0; i < n ; i++){
		printf("%-3d%-20s%9.2f%9.2f%8d    \n",i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].DG, dsdv[i].soDV_Dc_Chon);
	}
}

void DP(int W, int n, DoVat* dsdv){
	pair ans[n+1][W+1];
	int k, v;
	
	for(k = 1; k<=n ; k++){
		for(v = 0; v <= W; v++){
			ans[k][v].f = 0;
			ans[k][v].x = 0;
		}
	}
	for(v = 0; v <= W; v++){
		ans[1][v].x = v / dsdv[0].TL;
		ans[1][v].f = ans[1][v].x * dsdv[0].GT;
	}
	
	
	for(k = 2; k <= n; k++){
		for(v = 0; v <= W; v++){
			int maxF = ans[k-1][v].f;
			int maxX = 0;
			int xK, yK = (v / dsdv[k-1].TL);
			for(xK = 1 ; xK <= yK; xK ++){
				if (maxF < ans[k-1][v - xK * (int)dsdv[k-1].TL].f + xK* dsdv[k-1].GT){
					maxF = ans[k-1][v - xK * (int)dsdv[k-1].TL].f + xK* dsdv[k-1].GT;
					maxX = xK;
				}
			}
			ans[k][v].f = maxF;
			ans[k][v].x = maxX;
		}
	}
	v = W;
	for (k = n; k >= 1; k--){
		dsdv[k-1].soDV_Dc_Chon = ans[k][v].x;
		v -= dsdv[k-1].soDV_Dc_Chon * dsdv[k-1].TL;
	}
	
//	printf("\n");
//	for(k = 1; k<=n ; k++){
//		for(v = 0; v <= W; v++){
//			printf("%d-%d ", ans[k][v].f, ans[k][v].x);
//		}
//		printf("\n");
//	}
	
}


int main(){
	DoVat* dsdv;
	float W;
	int n;
	dsdv = readFromFile(&W, &n);
	DP(W, n, dsdv);
	inDSDV(dsdv,n, W);
}
