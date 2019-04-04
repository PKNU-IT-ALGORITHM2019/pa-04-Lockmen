//정렬 알고리즘 코드


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000    //데이터의 개수 지정
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))    //SWAP함수 설정
int original[MAX_SIZE];    //랜덤함수로 만든 데이터를 저장할 원본 배열
int list[MAX_SIZE];    //각 정렬 알고리즘에서 사용할 데이터 배열
int n, n1, n2; //데이터의 개수를 받는 전역변수 설정
int sorted[MAX_SIZE]; //합병정렬에서 사용할 데이터를 저장할 배열
clock_t start, finish, used_time = 0;    //실행 시간 측정을 위한 변수
int number[MAX_SIZE];
//합병정렬
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left, j = mid + 1; k = left;

	while (i <= mid && j <= right)
	{
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	if (i>mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (l = i; l <= right; l++)
			sorted[k++] = list[l];

	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}
void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left<right)
	{
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

//퀵정렬
int partition(int list[], int left, int right)
{
	int pivot = list[left], tmp, low = left, high = right + 1;

	do {
		do
			low++;
		while (low <= right && list[low]<pivot);

		do
			high--;
		while (high >= left && list[high]>pivot);
		if (low<high) SWAP(list[low], list[high], tmp);
	} while (low<high);

	SWAP(list[left], list[high], tmp);
	return high;
}
void quick_sort(int list[], int left, int right)
{
	if (left<right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}
int median_of_three(int list[], int left, int right)
{
int mid;

mid = (left + right) / 2;
quick_sort(list, left, mid);
quick_sort(list, mid, right);



return mid;
}




void inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap)
	{
		key = list[i];
		for (j = i - gap; j >= first && key<list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}


//버블 정렬
void bubble_sort(int list[], int n)
{
	int i, j, tmp;

	for (i = n - 1; i>0; i--)
	{
		for (j = 0; j<i; j++)
			if (list[j]>list[j + 1])
				SWAP(list[j], list[j + 1], tmp);
	}
}

//선택 정렬
void selection_sort(int list[], int n)
{
	int i, j, least, tmp;


	for (i = 0; i<n - 1; i++)
	{
		least = i;
		for (j = i + 1; j<n; j++)
			if (list[j]<list[least]) least = j;
		SWAP(list[i], list[least], tmp);
	}
}

//삽입 정렬
void insertion_sort(int list[], int n)
{
	int i, j, key;

	for (i = 1; i<n; i++)
	{
		key = list[i];
		for (j = i - 1; j >= 0 && list[j]>key; j--)
			list[j + 1] = list[j];
		list[j + 1] = key;
	}
}



void heap_sort(int *list, int n)
{
	int i, temp;
	for (i = (n / 2); i >= 1; i--)   // 초기 히프 만들기
		adjust(list, i, n);
	for (i = (n - 1); i >= 1; i--) {  // 히프 정렬의 두 번째 단계
		temp = list[i + 1];      // 마지막 노드와 뿌리 노드의 교환
		list[i + 1] = list[1];
		list[1] = temp;
		adjust(list, 1, i);     // i개의 키에 대하여 adjust 적용
	}
}

void adjust(int *list, int i, int n)
// i : adjust 알고리즘을 시작하는 노드의 인덱스 
// n : 전체 노드의 개수 
{
	int j, k, done;

	done = 0;     // 아직 끝나지 않았음을 표시 
	k = list[i];    // 뿌리 노드의 값, 즉 옮겨야 할 원소의 값 
	j = 2 * i;       // i 노드의 좌 자 노드 

	while ((j <= n) && (!done)) {    // 자식노드가 있고 not done일 때까지 반복 
		if (j < n)      // j + 1 <= n 과 마찬가지인데 우 자 노드의 존재를 검사 
			if (list[j] < list[j + 1])
				j++;        // 자 노드들 중 큰 노드를 선택 

		if (k >= list[j])
			done = 1;     // 자 노드보다 크므로 수행을 중단 

		else {
			list[j / 2] = list[j];       // 자 노드를 부노드로 끌어 올림, 
										 // 자 노드에 k 값을 쓰지 않는 이유는 나중에 
										 // 수행이 다 끝난 다음에 쓰기 때문임. 
			j *= 2;
		}
	}
	list[j / 2] = k;   // 수행이 끝나면 찾아낸 위치에 맨 처음 저장한 뿌리 노드의 값을 저장 
}

//오름차순
int compare(void*first, void*second)
{
	if (*(int*)first > *(int*)second)
		return 1;
	else if (*(int*)first < *(int*)second)
		return -1;
	else
		return 0;
}


//원본 배열을 복사하는 함수
void CopyArr(void)
{
	int i;
	for (i = 0; i<n; i++)
		list[i] = original[i];
}

void CopyArr1(void)
{
	int i;
	for (i = 0; i<n; i++)
		list[i] = number[i];

}

//실행 시간을 측정 및 출력하는 함수
void CalcTime(void)
{
	used_time = finish - start;
	printf("완료!\n소요 시간 : %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
}




int main()
{
	int i;

	n = MAX_SIZE;
	for (i = 0; i < n; i++) {
		original[i] = rand();
	}

	for (i = 1; i <= n; i++) {
		number[i] = n - i + 1;

	}


	printf("데이터의 개수 : %d\n\n", n);



	printf("(random)선택 정렬 중");
	CopyArr();
	start = clock();
	selection_sort(list, n);
	finish = clock();
	CalcTime();

	printf("(reverse)선택 정렬 중");
	CopyArr1();
	start = clock();
	selection_sort(list, n);
	finish = clock();
	CalcTime();






	printf("----------------------------------------------------------------\n");


	printf("(random)삽입 정렬 중");
	CopyArr();
	start = clock();
	insertion_sort(list, n);
	finish = clock();
	CalcTime();

	printf("(reverse)삽입 정렬 중");
	CopyArr1();
	start = clock();
	insertion_sort(list, n);
	finish = clock();
	CalcTime();



	printf("----------------------------------------------------------------\n");



	printf("(random)버블 정렬 중...");
	CopyArr();
	start = clock();
	bubble_sort(list, n);
	finish = clock();
	CalcTime();

	printf("(reverse)버블 정렬 중...");
	CopyArr1();
	start = clock();
	bubble_sort(list, n);
	finish = clock();
	CalcTime();



	printf("----------------------------------------------------------------\n");

	CopyArr();
	start = clock();
	printf("(random)합병 정렬 중... ");
	merge_sort(list, 0, n);
	finish = clock();
	CalcTime();

	CopyArr1();
	start = clock();
	printf("(reverse)합병 정렬 중... ");
	merge_sort(list, 0, n);
	finish = clock();
	CalcTime();

	printf("----------------------------------------------------------------\n");

	CopyArr();
	start = clock();
	printf("(random)퀵 정렬 중... ");
	quick_sort(list, 0, n);
	finish = clock();
	CalcTime();

	CopyArr1();
	start = clock();
	printf("(reverse)퀵 정렬 중... ");
	quick_sort(list, 0, n);
	finish = clock();
	CalcTime();



	printf("----------------------------------------------------------------\n");
	CopyArr();
	start = clock();
	printf("(random)힙소트 정렬 중... ");
	heap_sort(list, n);
	finish = clock();
	CalcTime();

	CopyArr1();
	start = clock();
	printf("(reverse)힙소트 정렬 중... ");
	heap_sort(list, n);
	finish = clock();
	CalcTime();

	printf("----------------------------------------------------------------\n");
	CopyArr();
	start = clock();
	printf("(random)라이브러리 알고리즘 정렬 중... ");
	qsort(list, n, sizeof(int), compare);
	finish = clock();
	CalcTime();

	CopyArr1();
	start = clock();
	printf("(reverse)라이브러리 알고리즘 정렬 중... ");
	qsort(list, n, sizeof(int), compare);
	finish = clock();
	CalcTime();

	system("pause");

}