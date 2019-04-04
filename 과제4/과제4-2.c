#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 300
#define WEBLOG 20000

typedef struct weblog {
	char *ip;
	char *time;
	char *url;
	char *status;
}weblog;

weblog arr[WEBLOG];
int ip_compare(const void *first, const void *second);
int time_compare(const void *first, const void *second);
int read_line(FILE *fp, char str[], int limit);
void print();
void read();
void sort();
int n = 0;

int read_line(FILE *fp, char str[], int limit)
{ // 한 줄 읽기 
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		if (i<limit - 1)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}


int main()
{

	char command[100];
	int isread = 0;

	while (1)
	{
		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "read") == 0)
		{
			isread = 1;
			read();
		}
		else if (strcmp(command, "sort") == 0) {

			sort();
		}
		else if (strcmp(command, "print") == 0) {

			print();
		}
		else if (strcmp(command, "exit") == 0) {

			break;
		}
	}
	return 0;
}







void sort() {

	char buffer[MAX];
	scanf("%s", buffer);
	if (strcmp(buffer, "read") == 0)
		read();
	else if (strcmp(buffer, "-t") == 0) {
		qsort(arr, n, sizeof(weblog), time_compare);

	}
	else if (strcmp(buffer, "-ip") == 0) {
		qsort(arr, n, sizeof(weblog), ip_compare);
	}

	else return;
}

void read()
{
	char fileName[MAX];
	char buffer[MAX];
	
	scanf("%s", fileName);
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("failed.\n");
		return;
	}

	read_line(fp, buffer, MAX);
	while (read_line(fp, buffer, MAX) != 0) {
		arr[n].ip = strdup(strtok(buffer, ","));
		arr[n].time = strdup(strtok(NULL, ","));
		arr[n].url = strdup(strtok(NULL, ","));
		arr[n].status = strdup(strtok(NULL, ","));
		n++;
	}
	fclose(fp);
}


int time_compare(const void *first, const void *second)
{
	weblog *pa = (weblog*)first;
	weblog *pb = (weblog*)second;

	return strcmp(pa->time, pb->time);
}

int ip_compare(const void *first, const void *second)
{
	weblog *pa = (weblog*)first;
	weblog *pb = (weblog*)second;

	return strcmp(pa->ip, pb->ip);
}


void print()
{

	char buffer[50];
	if (strcmp(buffer, "-t") == 0) {
		for (int i = 0; i<n - 1; i++) {
			printf("%s\n	IP: %s\n	URL: %s\n	Status: %s\n", arr[i].time, arr[i].ip, arr[i].url, arr[i].status);
		}
	}

	else if (strcmp(buffer, "-ip") == 0) {
		for (int i = 0; i<n - 1; i++) {
			printf("%s\n	Time: %s\n	URL: %s\n	Status: %s\n", arr[i].time, arr[i].ip, arr[i].url, arr[i].status);
		}
	}


	else
		for (int i = 0; i < n - 1; i++)
			printf("%s\n	Time: %s\n	IP: %s\n	URL: %s\n", arr[i].status, arr[i].time, arr[i].ip, arr[i].url);
}

