#include<iostream>

#include<stdio.h>

#include<conio.h>

#include<Windows.h>

#include<thread>

#include<process.h>

#pragma warning (disable : 4996)

using std::thread;

// Ű���� ��  

#define UP 0

#define DOWN 1

#define LEFT 2

#define RIGHT 3

#define SUBMIT 4 // ����(�����̽���)  



int playing = 1;

int mKey;

double game_time;

char tempMap[14][56];

int playflag = 1;

int Mx = 20;

int My = 6;

int cX = 0;

int cY = 0;



void t_fuction();

void drawUI(int pX, int pY, int pKey);

int move(char(*tMap)[56], int* pX, int* pY, int _x, int _y, int* pKey);

void gLoop(void);

void drawMap(int* pX, int* pY, char(*tMap)[56]);

void infoDraw(void);

int menuDraw(void);

void titleDraw(void);

int keyControl(void);

void setColor(int forground, int background);

void display_start();

void gaming_time(clock_t start, double* pst);

double game_setup(double* pst);

void gotoxy(int x, int y);

void init(void);


enum {
	black,
	blue,
	green,
	cyan,
	red,
	purple,
	brown,
	lightgray,
	darkgray,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightpurple,
	yellow,
	white
};

char map[14][56] = { // ����� 
				 // ���� ���ڴ� �� �迭ũ�⿡ ���߾� 56�� 
   {"1111111111111111111111111111111111111111111111111111111"}, // ���� ���̿� ���߾� 14��  
   {"1000000010000000000000000000000000000100000000000000001"},
   {"1000000010000000000000000000000000000100000000000000001"},
   {"1000100010000001111111111111111110000100000000100000001"},
   {"100010k010000001000000000000000000000100000000100000001"},
   {"100010001000k001000000000000000000k0010000l000100000001"},
   {"100010001111111100000000000000000000010000000010000k001"},
   {"1000100000000000000000000100000000000100000000100000001"},
   {"1000100000000l000000000001000000000001000000000l0000001"},
   {"1000100000000000000000000100000000000000000000001111111"},
   {"1000100010000000000000000100000000000000000000001000001"},
   {"10s010001111111111111111111111111111111111111111100q001"},
   {"10001000000k000000000000000000000l000000000000000000001"},
   {"1111111111111111111111111111111111111111111111111111111"}
};

void init(void)
{
	system("mode con cols=56 lines=22 | title Escape Game");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0; // false �Ǵ� 0 : �����
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void gotoxy(int x, int y) 
{
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	return;
}

void gotoxy_t(int x, int y) 
{
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	return;
}

double time_setup() 
{
	double gt;
	printf("������ ���� �ð�(�� ����)�� �Է��ϰ� Enter>");
	scanf("%lf", &gt);
	return gt;
}

void gaming_time(clock_t start, double* pst)
{
	clock_t end;
	end = clock();
	*pst = (double)(end - start) / CLK_TCK;
	gotoxy_t(12, 18);
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

void setColor(int forground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}

int keyControl(void) 
{
	char temp = _getch();
	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{ // �����̽���(����)�� ���� ��ư  
		return SUBMIT;
	}
}

void titleDraw(void) 
{
	printf("\n\n\n\n"); // ������ 4ĭ ����  
	printf("        #####    ###    ###    #    ####   ##### \n");
	printf("        #       #      #      # #   #   #  #     \n");
    	printf("        ####    ####   #     #####  ####   ####  \n");
	printf("        #           #  #     #   #  #      #     \n");
	printf("        #####   ####    ###  #   #  #      ##### \n");
}

int menuDraw(void) 
{
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y); // -2 �� ������ > �� ����ؾ��ϱ� ������  
	printf("> ���ӽ���");
	gotoxy(x, y + 1);
	printf("��������");
	gotoxy(x, y + 2);
	printf("  ����  ");
	while (1) { // ���ѹݺ�  
		int n = keyControl(); // Ű���� �̺�Ʈ�� Ű������ �޾ƿ���  
		switch (n) {
		case UP: { // �Էµ� Ű�� ���� UP�ΰ�� (w)
			if (y > 12) { // y�� 12~14������ �̵�  
				gotoxy(x - 2, y); // x-2 �ϴ� ������ ">"�� ��ĭ ������ ����ϱ�����  
				printf(" "); // ���� ��ġ�� �����  
				gotoxy(x - 2, --y); // ���� �̵��� ��ġ�� �̵��Ͽ�  
				printf(">"); // �ٽ� �׸���  
			}
			break;
		}
		case DOWN: { // �Էµ� Ű�� ���� DOWN�ΰ�� (s)
			if (y < 14) { // �ִ� 14  
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			return y - 12; // �����̽���(����)�Ǿ��� ��� y-12
			// y ���� ��ġ�� 12�����Ƿ� y-12 �� �ϸ� 0, 1, 2 �� ���ڸ� ���� �� �ִ�.
		}
		}
	}
}

void infoDraw(void)
{
	system("cls"); // ȭ�� ��� �����  
	printf("\n\n");
	printf("                        [ ���۹� ]\n\n");
	printf("                    �̵�: W, A, S, D\n");
	printf("                    ����: �����̽���\n\n\n\n\n\n\n");
	printf("               ������: programming team1\n\n");
	printf("      �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.");
	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

void drawMap(int* pX, int* pY, char(*tMap)[56])
{
	char temp;
	system("cls");
	int h, w;
	for (h = 0; h < 14; h++)
	{
		for (w = 0; w < 56; w++)
		{
			temp = tMap[h][w];
			if (temp == '0')
			{
				setColor(black, black);
				printf(" ");
			}
			else if (temp == '1')
			{
				setColor(white, white);
				printf("#");
			}
			else if (temp == 's')
			{
				*pX = w;
				*pY = h;
				setColor(cyan, black);
				printf("@");
			}
			else if (temp == 'q')
			{
				setColor(lightgreen, black);
				printf("O");
			}
			else if (temp == 'k')
			{
				setColor(yellow, black);
				printf("*");
			}
			else if (temp == 'l')
			{
				setColor(brown, black);
				printf("+");
			}
		}
		printf("\n");
	}
	setColor(white, black);
}

void gLoop(void)
{
	int cKey = 0;
	playing = 1;
	memcpy(tempMap, map, sizeof(tempMap));
	drawMap(&cX, &cY, tempMap);
	while (playing)
	{
		if (Mx == cX && My == cY)
		{
			mKey = SUBMIT;
		}
		drawUI(cX, cY, cKey);
		mKey = keyControl();
		if (playing == 0) {
			mKey = SUBMIT;
		}
		switch (mKey)
		{
		case UP:
			playing = move(tempMap, &cX, &cY, 0, -1, &cKey);
			break;
		case DOWN:
			playing = move(tempMap, &cX, &cY, 0, 1, &cKey);
			break;
		case RIGHT:
			playing = move(tempMap, &cX, &cY, 1, 0, &cKey);
			break;
		case LEFT:
			playing = move(tempMap, &cX, &cY, -1, 0, &cKey);
			break;
		case SUBMIT:
			playing = 0;
		}
	}
	return;
}

int move(char(*tMap)[56], int* pX, int* pY, int _x, int _y, int* pKey)
{
	char mapObject = tMap[*pY + _y][*pX + _x];
	setColor(white, black);
	if (mapObject == '0')
	{
		gotoxy(*pX, *pY);
		printf(" ");
		setColor(cyan, black);
		gotoxy(*pX + _x, *pY + _y);
		printf("@");
		*pX += _x;
		*pY += _y;
	}
	else if (mapObject == 'k')
	{
		*pKey += 1;
		tMap[*pY + _y][*pX + _x] = '0';
		gotoxy(*pX + _x, *pY + _y);
		printf(" ");
	}
	else if (mapObject == 'l')
	{
		if (*pKey > 0)
		{
			*pKey -= 1;
			tMap[*pY + _y][*pX + _x] = '0';
			setColor(white, black);
			gotoxy(*pX + _x, *pY + _y);
			printf(" ");
		}
	}
	else if (mapObject == 'q')
	{
		if (*pKey == 0)
		{
			playflag = 0;
		}
		else
		{
			playflag = 1;
		}
	}
	return playflag;
}

void drawUI(int pX, int pY, int pKey)
{
	setColor(white, black);
	gotoxy(0, 14);
	printf("########################################################");
	gotoxy(3, 16);
	printf("�÷��̾� ��ġ:(%02d,%02d)", pX, pY);
	setColor(yellow, black);
	gotoxy(34, 16);
	printf("����: %d��", pKey);
	setColor(white, black);
}

void t_fuction()
{
	double pst = 0;
	clock_t start;
	start = clock();
	gaming_time(start, &pst);
	gotoxy(12, 18);
	_getch();
	start = clock();
	gotoxy(12, 19);
	pst = 0;
	do
	{
		gaming_time(start, &pst);
		Sleep(100);
		if (playflag == 0)
		{
			break;
		}
		if (Mx == cX && My == cY)
		{
			break;
		}
	} while (pst < game_time);
	playing = 0;
	gotoxy(12, 20);
	printf("������ �����մϴ�. \n");
}

void Monster()
{
	int ps = 1;
	int _y = 0;
	while (1)
	{
		gotoxy(Mx, My + _y);
		printf("��");
		gotoxy(Mx, My + _y - 1);
		printf(" ");
		_y += 1;
		ps++;
		if (ps == 5)
		{
			gotoxy(Mx, 9);
			printf(" ");
			_y = -1;
			ps = 0;
		}
		Sleep(100);
		if (playing == 0)
		{
			break;
		}
		else if (playflag == 0)
		{
			break;
		}
		if (Mx == cX && My == cY)
		{
			break;
		}
	}
}

int main() {
	OutputDebugString("DEBUG0");
	game_time = time_setup();
	init();
	int menuCode;
	int playing = 1;
	while (1)
	{
		titleDraw();
		menuCode = menuDraw();
		if (menuCode == 0)
		{
			thread t1(t_fuction);
			thread t2(gLoop);
			thread t3(Monster);
			t1.join();
			t2.join();
			t3.join();
		}
		else if (menuCode == 1)
		{
			infoDraw();
		}
		else if (menuCode == 2)
		{
			break;
		}
		menuCode = 5;
		system("cls");
	}
	gotoxy(12, 16);
	printf("������ ����Ǿ����ϴ�!!!");
	_getch();

	return 0;
}
