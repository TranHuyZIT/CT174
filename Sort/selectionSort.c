#include "header.c"
void selectionSort(recordtype a[], int n){
	int i, lowIdx, lowKey;
	for(i = 0 ; i <= n - 2; i++){
		lowIdx = i;
		lowKey = a[i].key;
		int j;
		for(j = i + 1; j <= n - 1; j++){
			if (a[j].key < lowKey){
				lowKey = a[j].key;
				lowIdx = j;
			}
		}
		swap(&a[i], &a[lowIdx]);
	}
}

int main(){
	recordtype a[100003];
	int n;
	readData(a, &n);
	time_t timeStart = time(NULL);
	selectionSort(a, n);
	time_t timeEnd = time(NULL);
	printData(a, n);
	printf("\nTime Taken: %ld secs", timeEnd - timeStart);
	return 0;
}
