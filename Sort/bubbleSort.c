#include "header.c"
void bubbleSort(recordtype a[], int n){
	int i = 1, j;
	for( i = 0 ; i <= n - 2; i++){
		for(int j = n - 1; j >= i + 1; j --){
			if (a[j-1].key > a[j]. key){
				swap(&a[j-1], &a[j]);
			}
		}
	}
}

int main(){
	recordtype a[100002];
	int n;
	readData(a, &n);
	time_t timeStart = time(NULL);
	bubbleSort(a, n);
	time_t timeEnd = time(NULL);
	printData(a, n);
	printf("\nTime Taken: %ld secs", timeEnd - timeStart);
	return 0;
}
