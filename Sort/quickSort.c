#include "header.c"
int findPivot(recordtype a[], int l , int r){
	keytype first;
	int k = l + 1;
	first = a[l].key;
	while(k <= r && a[k].key == first){
		k++;
	}
	if (k > r) return -1;
	else{
		if (a[k]. key > first) return k;
		else return l;
	}
}

int partition(recordtype a[], int l , int r, keytype pivot){
	while(l <= r){
		while (a[l].key < pivot) l++;
		while(a[r].key >= pivot) r--;
		if (l < r){
			swap(&a[l], &a[r]);
		}
	}
	return l;
}
void quickSort(recordtype a[], int l, int r){
	int pivotIdx = findPivot(a, l , r);
	if (pivotIdx != -1){
		keytype pivot = a[pivotIdx].key;
		int k = partition(a, l, r, pivot);
		quickSort(a, l, k - 1);
		quickSort(a, k, r);
	}
}

int main(){
	recordtype a[100002];
	int n;
	readData(a, &n);
	time_t timeStart = time(NULL);
	quickSort(a, 0, n);
	time_t timeEnd = time(NULL);
	printData(a, n);
	printf("\nTime Taken: %lf secs", timeEnd - timeStart);
	return 0;
}
