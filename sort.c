/*
* int arr[5] = {5, 3, 8, 1, 2, 7}
* n = 5;


선택 정렬 

int m, temp, i, j;
for(i = 0; i < n - 1; i++) {
	m = i;
	for(j = i + 1; j < n; j++)
		if(a[j] < a[m]) m = j;
		temp = a[m];
		a[m] = a[i];
		a[i] = temp;
}


삽입 정렬

int temp, i, j;
for(i = 1; i < n; i++) {
	temp = a[i];
	for(j = i - 1; j >= 0 && a[j] > temp; j--)
		a[j + 1] = a[j];
	a[j + 1] = temp;
}


버블 정렬

int temp;
for(int i = n - 1; i > 0; i--) {
	for(j = 0; j < i; j++) {
		if(a[j] > a[j + 1]) {
			temp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = temp;
		}
	}
}


셸 정렬

int gap = n / 2, key, i, j;
while(1) {
	if(gap % 2 == 0) gap++;
	for(i = gap; i < n; i++) {
		key = a[i];
		for(j = i - gap; j >= 0; j -= gap) {
			if(key < a[j]) 
				a[j + gap] = a[j];
			else
				break;
		}
		a[j + gap] = key;
	}
	if(gap == 1) break;
	gap /= 2;
}
*/
