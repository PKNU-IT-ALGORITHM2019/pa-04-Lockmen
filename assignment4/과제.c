//���� �˰��� �ڵ�


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000    //�������� ���� ����
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))    //SWAP�Լ� ����
int original[MAX_SIZE];    //�����Լ��� ���� �����͸� ������ ���� �迭
int list[MAX_SIZE];    //�� ���� �˰��򿡼� ����� ������ �迭
int n, n1, n2; //�������� ������ �޴� �������� ����
int sorted[MAX_SIZE]; //�պ����Ŀ��� ����� �����͸� ������ �迭
clock_t start, finish, used_time = 0;    //���� �ð� ������ ���� ����
int number[MAX_SIZE];
//�պ�����
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

//������
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


//���� ����
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

//���� ����
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

//���� ����
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
	for (i = (n / 2); i >= 1; i--)   // �ʱ� ���� �����
		adjust(list, i, n);
	for (i = (n - 1); i >= 1; i--) {  // ���� ������ �� ��° �ܰ�
		temp = list[i + 1];      // ������ ���� �Ѹ� ����� ��ȯ
		list[i + 1] = list[1];
		list[1] = temp;
		adjust(list, 1, i);     // i���� Ű�� ���Ͽ� adjust ����
	}
}

void adjust(int *list, int i, int n)
// i : adjust �˰����� �����ϴ� ����� �ε��� 
// n : ��ü ����� ���� 
{
	int j, k, done;

	done = 0;     // ���� ������ �ʾ����� ǥ�� 
	k = list[i];    // �Ѹ� ����� ��, �� �Űܾ� �� ������ �� 
	j = 2 * i;       // i ����� �� �� ��� 

	while ((j <= n) && (!done)) {    // �ڽĳ�尡 �ְ� not done�� ������ �ݺ� 
		if (j < n)      // j + 1 <= n �� ���������ε� �� �� ����� ���縦 �˻� 
			if (list[j] < list[j + 1])
				j++;        // �� ���� �� ū ��带 ���� 

		if (k >= list[j])
			done = 1;     // �� ��庸�� ũ�Ƿ� ������ �ߴ� 

		else {
			list[j / 2] = list[j];       // �� ��带 �γ��� ���� �ø�, 
										 // �� ��忡 k ���� ���� �ʴ� ������ ���߿� 
										 // ������ �� ���� ������ ���� ������. 
			j *= 2;
		}
	}
	list[j / 2] = k;   // ������ ������ ã�Ƴ� ��ġ�� �� ó�� ������ �Ѹ� ����� ���� ���� 
}

//��������
int compare(void*first, void*second)
{
	if (*(int*)first > *(int*)second)
		return 1;
	else if (*(int*)first < *(int*)second)
		return -1;
	else
		return 0;
}


//���� �迭�� �����ϴ� �Լ�
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

//���� �ð��� ���� �� ����ϴ� �Լ�
void CalcTime(void)
{
	used_time = finish - start;
	printf("�Ϸ�!\n�ҿ� �ð� : %f sec\n\n", (float)used_time / CLOCKS_PER_SEC);
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


	printf("�������� ���� : %d\n\n", n);



	printf("(random)���� ���� ��");
	CopyArr();
	start = clock();
	selection_sort(list, n);
	finish = clock();
	CalcTime();

	printf("(reverse)���� ���� ��");
	CopyArr1();
	start = clock();
	selection_sort(list, n);
	finish = clock();
	CalcTime();






	printf("----------------------------------------------------------------\n");


	printf("(random)���� ���� ��");
	CopyArr();
	start = clock();
	insertion_sort(list, n);
	finish = clock();
	CalcTime();

	printf("(reverse)���� ���� ��");
	CopyArr1();
	start = clock();
	insertion_sort(list, n);
	finish = clock();
	CalcTime();



	printf("----------------------------------------------------------------\n");



	printf("(random)���� ���� ��...");
	CopyArr();
	start = clock();
	bubble_sort(list, n);
	finish = clock();
	CalcTime();

	printf("(reverse)���� ���� ��...");
	CopyArr1();
	start = clock();
	bubble_sort(list, n);
	finish = clock();
	CalcTime();



	printf("----------------------------------------------------------------\n");

	CopyArr();
	start = clock();
	printf("(random)�պ� ���� ��... ");
	merge_sort(list, 0, n);
	finish = clock();
	CalcTime();

	CopyArr1();
	start = clock();
	printf("(reverse)�պ� ���� ��... ");
	merge_sort(list, 0, n);
	finish = clock();
	CalcTime();

	printf("----------------------------------------------------------------\n");

	CopyArr();
	start = clock();
	printf("(random)�� ���� ��... ");
	quick_sort(list, 0, n);
	finish = clock();
	CalcTime();

	CopyArr1();
	start = clock();
	printf("(reverse)�� ���� ��... ");
	quick_sort(list, 0, n);
	finish = clock();
	CalcTime();



	printf("----------------------------------------------------------------\n");
	CopyArr();
	start = clock();
	printf("(random)����Ʈ ���� ��... ");
	heap_sort(list, n);
	finish = clock();
	CalcTime();

	CopyArr1();
	start = clock();
	printf("(reverse)����Ʈ ���� ��... ");
	heap_sort(list, n);
	finish = clock();
	CalcTime();

	printf("----------------------------------------------------------------\n");
	CopyArr();
	start = clock();
	printf("(random)���̺귯�� �˰��� ���� ��... ");
	qsort(list, n, sizeof(int), compare);
	finish = clock();
	CalcTime();

	CopyArr1();
	start = clock();
	printf("(reverse)���̺귯�� �˰��� ���� ��... ");
	qsort(list, n, sizeof(int), compare);
	finish = clock();
	CalcTime();

	system("pause");

}