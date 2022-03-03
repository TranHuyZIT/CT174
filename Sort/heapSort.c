#include "header.c"
void pushDown(recordtype a[], int first, int last){
	int r = first;
	while (r <= (last - 1)/2){
		if (last == 2*r + 1){
			if (a[r].key < a[last].key) swap(&a[r],&a[last]);
			r = last;
		}
		else{
			if(a[r]. key < a[2*r + 1].key && a[2*r + 1].key > a[2*r + 2].key){
				swap(&a[r], &a[2*r + 1]);
				r = 2*r + 1;	
			}
			else{
				if(a[r]. key < a[2*r + 2].key && a[2*r + 2].key > a[2*r + 1].key){
					swap(&a[r], &a[2*r + 2]);
					r = r*2 + 2;
				}
				else{
					r = last;
				}
			}
		}
		
	}
}

void heapSort(recordtype a[], int n){
	int i;
	for(i = (n-2)/2 ; i >= 0; i--){
		pushDown(a, i, n- 1);
	}
	
	for(i = n- 1; i >= 2; i--){
		swap(&a[0], &a[i]);
		pushDown(a, 0, i - 1);
	}
	swap(&a[0], &a[1]);
}

int main(){
	recordtype a[100002];
	int n;
	readData(a, &n);
	time_t timeStart = time(NULL);
	heapSort(a, n);
	time_t timeEnd = time(NULL);
	printData(a, n);
	printf("\nTime Taken: %lf secs", timeEnd - timeStart);
	return 0;
}

