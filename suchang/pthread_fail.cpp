#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#pragma warning (disable : 4996)
void *threadRoutine(void *argumentPointer)
{
	auto gs = []() {return 10; };
	gs();
	pthread_t id = pthread_self();
	printf("thread ID (TID) :: %lu\n", id);
	double pst = 0, game_time;
	clock_t start;
	//game_time = game_setup(&pst);
	game_time = gs();
	start = clock();
	gaming_time(start, &pst);
	gotoxy(1, 15);
	printf("������ �����մϴ�. \n");
	display_start();
	start = clock();
	pst = 0;
	do
	{
		gaming_time(start, &pst);
	} while (pst < game_time);
}
void gotoxy(int x, int y);
double game_setup(double *pst);
void gaming_time(clock_t start, double *pst);
void display_start();
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	return;
}
double game_setup(double *pst)
{
	double game_time;
	printf("������ ���� �ð�(�� ����)�� �Է��ϰ� Enter>");
	scanf("%lf", &game_time);
	system("cls");
	gotoxy(1, 1);
	printf("���ѽð�:%5.1f ��", game_time);
	gotoxy(30, 1);
	printf("����ð�:%4.1F ��", *pst);
	gotoxy(38, 6);
	return game_time;
}
int main(void)
{
	pthread_t threadID;
	pthread_create(&threadID, NULL, threadRoutine, NULL);
	pthread_join(threadID, NULL);
	printf("bye");
	return 0;
}
void gaming_time(clock_t start, double *pst)
{
	clock_t end;
	end = clock();
	*pst = (double)(end - start) / CLK_TCK;
	gotoxy(30, 1);
	printf("����ð�:%4.1f��", *pst);
}
void display_start()
{
	gotoxy(1, 13);
	printf("�ƹ�Ű�� ������ ��⸦ �����մϴ�. ");
	getch();
	gotoxy(1, 12);
	printf("                                    ");
	gotoxy(1, 13);
	printf("                                    ");
}