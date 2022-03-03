#include "header.c"
void insertionSort(recordtype a[], int n){
	int i;
	for(i = 1; i <= n - 1; i++){
		int j;
		for(int j = i; j >= 0 ; j--){
			if (a[j-1].key > a[j].key){
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
	insertionSort(a, n);
	time_t timeEnd = time(NULL);
	printData(a, n);
	printf("\nTime Taken: %ld secs", timeEnd - timeStart);
	return 0;
}
