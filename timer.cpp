#include <stdio.h>
#pragma warning (disable : 4996)
#include <time.h>
int main() {
	int j = 1;
	clock_t start, finish;
	double duration = 0.0;
	while (j) {
		printf("\nTimer를 시작하려면 enter키를 입력하세요>");
		getchar();
		start = clock();
		printf("\n측정 중, 다시 엔터키를 입력하면 결과값이 출력됩니다>");
		getchar();
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("\n\n\t%f 초\n", duration);
		printf("\n재시작은 enter키를, 종료는 0과 enter키를 입력하세요>");
		j = getchar();
		if (j == 48) {
			j = 0;
		}
		else {
			fflush(stdin);
			printf("\n========\n");
		}
	}
	return 0;
}