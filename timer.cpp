#include <stdio.h>
#pragma warning (disable : 4996)
#include <time.h>
int main() {
	int j = 1;
	clock_t start, finish;
	double duration = 0.0;
	while (j) {
		printf("\nTimer�� �����Ϸ��� enterŰ�� �Է��ϼ���>");
		getchar();
		start = clock();
		printf("\n���� ��, �ٽ� ����Ű�� �Է��ϸ� ������� ��µ˴ϴ�>");
		getchar();
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("\n\n\t%f ��\n", duration);
		printf("\n������� enterŰ��, ����� 0�� enterŰ�� �Է��ϼ���>");
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