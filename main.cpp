#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue> 
#include <locale.h>
using namespace std;
void BFSD(int** G, int* vis, int num, int n, int* dist) {
	queue <int> q;
	int i;
	q.push(num);
	vis[num] = 0;
	dist[num] = 0;
	while (!q.empty()) {
		num = q.front();
		q.pop();
	
		for (i = 0; i < n; i++) {
			if (vis[i] == 0 && G[num][i] > 0 && dist[i] > dist[num] + G[num][i]) {
				q.push(i);
				vis[i] = 1;
				dist[i] = dist[num] + G[num][i];

			}
		}
	}
}

int main(void) {
	setlocale(LC_ALL, "Rus");
	int** a;
	int** c;
	int* ecc;
	int* deg;
	int N, rad, D;
	rad = 1000;
	D = 0;
	printf("Введите N: ");
	scanf("%d", &N);
	a = (int**)malloc(N * sizeof(int));
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		int* b = (int*)malloc(N * sizeof(int));
		for (int j = 0; j < N; j++) {
			b[j] = 0;
		}
		a[i] = b;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i != j) {
				int num = rand() % 10;
				a[i][j] = num;
				a[j][i] = num;
			}
		}
	}
	printf("Неориентированный граф");
	printf("\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}

	int len = N;
	deg = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < len; i++) {
		deg[i] = 0;
	}
	int* dist = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < len; i++) {
		dist[i] = 1000;
	}
	int* visits = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < len; i++) {
		visits[i] = 0;
	}
	ecc = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < len; i++) {
		ecc[i] = 0;
	}

	for (int i = 0; i < len; i++) {
		//printf("%s%d %s ", "расстояние до ", i, "=");
		//printf("%d ", dist[i]);
		for (int k = 0; k < len; k++) {
			visits[k] = 0;
			dist[k] = 1000;
		}
		BFSD(a, visits, i, len, dist);

		for(int j=0;j<len;j++){
			if ((ecc[i] < dist[j]) && (dist[j] != 0)) {
				ecc[i] = dist[j];
		}
		}
	}
	printf("Эксцентриситеты:");
	printf("\n");
	for (int i = 0; i < len; i++) {
		printf("%d ", ecc[i]);
	}
	for (int i = 0; i < len; i++) {
		if (ecc[i] < rad && ecc[i]!=0) {
			rad = ecc[i];
		}
		if (ecc[i] > D) {
			D = ecc[i];
		}
	}
	printf("\n");
	printf("Радиус и диаметр:");
	printf("\n");
	printf("%d %d ", rad, D);
	printf("\n");
	printf("Периферийные вершины:");
	printf("\n");
	for (int i = 0; i < len; i++) {
			if (ecc[i] == D) {
				printf("%d ", i);
			}
	}
	printf("\n");
	printf("Центральные вершины:");
	printf("\n");
	for (int i = 0; i < len; i++) {
		if (ecc[i] == rad) {
			printf("%d ", i);
		}
	}
	printf("\n");
	printf("Степени:");
	printf("\n");
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (a[i][j] > 0) {
				deg[i] += 1;
			}
		}
	}
	for (int i = 0; i < len; i++) {
		{
			printf("%d ", deg[i]);
		}
	}
	printf("\n");
	printf("Изолированная вершина:");
	printf("\n");
	for (int i = 0; i < len; i++) {
		if (deg[i] == 0) {
			printf("%d ", i);
		}
	}
	printf("\n");
	printf("Концевая вершина:");
	printf("\n");
	for (int i = 0; i < len; i++) {
		if (deg[i] == 1) {
			printf("%d ", i);
		}
	}
	printf("\n");
	printf("Доминирующая вершина:");
	printf("\n");
	for (int i = 0; i < len; i++) {
		if (deg[i] == len-1) {
			printf("%d ", i);
	}
	}
}

