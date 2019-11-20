#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Ű���� ��  
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // ����(�����̽���)  

enum {
	black,//0
	blue,//1
	green,//2
	cyan,//3
	red,//4
	purple,//5
	brown,//6
	lightgray,//7
	darkgray,//8
	lightblue,//9
	lightgreen,//10
	lightcyan,//11
	lightred,//12
	lightpurple,//13
	yellow,//14
	white//15
};

char tempMap[14][56]; // �� �ӽ������� �迭  
char map[14][56] = { // �����  
                                                                 // ���� ���ڴ� �� �迭ũ�⿡ ���߾� 56��  
   {"1111111111111111111111111111111111111111111111111111111"}, // ���� ���̿� ���߾� 14��   
   {"1000000010000000000000000000000000000100000000000000001"},
   {"1000000010000000000000000000000000000100000000000000001"}, // 0 : �� ���� 
   {"1000100010000001111111111111111110000100000000100000001"}, // 1 : �� 
   {"100010k010000001000000000000000000000100000000100000001"}, // k : ���� 
   {"100010001000k001000000000000000000000100000000100000001"}, // l : ��� �� 
   {"100010001111111100000000000000000000010000000010000k001"}, // q : Ż�ⱸ  
   {"1000100000000000000000000100000000000100000000100000001"}, // t : ����
   {"10001000t00000000000000001000000000001000000000l0000001"},
   {"1000100000000000000000000100000000000000000000001111111"},
   {"1000100010000000000000000100000000000000000000001000001"},
   {"10s010001111111111111111111111111111111111111111100q001"},
   {"10001000000000000l00000000000l0000000000000000000000001"},
   {"1111111111111111111111111111111111111111111111111111111"}
};

int keyControl();
void titleDraw();
int menuDraw();
void infoDraw();

void init();
void gotoxy(int, int);
void setColor(int, int);
int maplistDraw(void);

void drawMap(void);
void move(int _x, int _y);
void gLoop(void);
void drawUI(void);

int pX, pY;
int pKey = 0;
int playing = 1;

int main(void)
{
	int menuCode;
	int playing = 1;

	init();

	while (1)
	{
		titleDraw();
		menuCode = menuDraw();

		if (menuCode == 0)
		{
			drawMap();
			gLoop();
		}

		else if (menuCode == 1)
		{
			infoDraw();
		}

		else if (menuCode == 2)
		{
			break;
		}
		//menuCode = 5;

		system("cls");
	}

	gotoxy(12, 16);
	printf("������ ����Ǿ����ϴ�!!!");
	_getch();

	return 0;
}

void init() {

	system("mode con cols=56 lines=20 | title Escape Game");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	CONSOLE_CURSOR_INFO ConsoleCursor;

	ConsoleCursor.bVisible = 0; // false �Ǵ� 0 : ����� 
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	pKey = 0;
	playing = 1;
}

// Ŀ�� ��ġ �̵��Լ�  
void gotoxy(int x, int y) {

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	COORD pos;

	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(consoleHandle, pos);
}

// ù��°: �ؽ�Ʈ, �ι�°: ���  
void setColor(int forground, int background) {

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	
	int code = forground + background * 16;

	SetConsoleTextAttribute(consoleHandle, code);
}

int keyControl() {

	char temp = _getch();

	if (temp == 'w' || temp == 'W') {
		return UP;
	}

	else if (temp == 'a' || temp == 'A') {
		return LEFT;
	}

	else if (temp == 's' || temp == 'S') {
		return DOWN;
	}

	else if (temp == 'd' || temp == 'D') {
		return RIGHT;
	}

	else if (temp == ' ') { // �����̽���(����)�� ���� ��ư  
		return SUBMIT;
	}
}

void titleDraw() {

	printf("\n\n\n\n"); // ������ 4ĭ ����  
	printf("        #####    ###    ###    #    ####   ##### \n");
	printf("        #       #      #      # #   #   #  #     \n");
	printf("        ####    ####   #     #####  ####   ####  \n");
	printf("        #           #  #     #   #  #      #     \n");
	printf("        #####   ####    ###  #   #  #      ##### \n");
}

int menuDraw() {

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

void infoDraw() {

	system("cls"); // ȭ�� ��� �����  
	printf("\n\n");
	printf("                        [ ���۹� ]\n\n");
	printf("                    �̵�: W, A, S, D\n");
	printf("                    ����: �����̽���\n\n\n\n\n\n\n");
	printf("               ������: codevkr.tistory.com\n\n");
	printf("      �����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

int maplistDraw(void) {

	int x = 24, y = 6, temp;

	system("cls");
	printf("\n\n");
	printf("                     [�� ����]\n\n");

	gotoxy(x - 2, y);
	printf("> ����");

	gotoxy(x, y + 1);
	printf("�����");

	gotoxy(x, y + 2);
	printf("�ڷ�");

	while (1)
	{
		int n = keyControl();

		switch (n)
		{
		case UP:
			if (y > 6)
			{
				gotoxy(x - 2, y);
				printf(" ");

				gotoxy(x - 2, --y);
				printf(">");
			}
			break;

		case DOWN:
			if (y < 8)
			{
				gotoxy(x - 2, y);
				printf(" ");

				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;

		case SUBMIT:
			return y - 6;
		}
	}
}

void drawMap(void) {

	char temp;
	system("cls");
	int h, w;

	for (h = 0; h < 14; h++)
	{
		for (w = 0; w < 56; w++)
		{
			temp = tempMap[h][w];

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
				pX = w;                           //�÷��̾� X,Y ��ġ ����
				pY = h;
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

			else if (temp == 't')
			{
				setColor(red, black);
				printf("X");
			}
		}

		printf("\n");
	}

	setColor(white, black);
	Sleep(3000);
}

void gLoop(void) {

	int mKey;

	memcpy(tempMap, map, sizeof(tempMap));

	drawMap();

	while (playing)
	{
		drawUI();

		mKey = keyControl();

		switch (mKey)
		{
		case UP:
			move(0, -1);
			break;

		case DOWN:
			move(0, 1);
			break;

		case RIGHT:
			move(1, 0);
			break;

		case LEFT:
			move(-1, 0);
			break;

		case SUBMIT:
			playing = 0;
		}
	}

	playing = 1;
}

void move(int _x, int _y) {

	char mapObject = tempMap[pY + _y][pX + _x];

	setColor(white, black);

	if (mapObject == '0')
	{
		gotoxy(pX, pY);
		printf(" ");

		setColor(cyan, black);
		gotoxy(pX + _x, pY + _y);
		printf("@");

		pX += _x;
		pY += _y;
	}

	//   else if (mapObject == '1')
	//   {
		  // �ƹ��ϵ� ���� ����
	//   }

	else if (mapObject == 'k')
	{
		pKey += 1;
		tempMap[pY + _y][pX + _x] = '0';

		gotoxy(pX + _x, pY + _y);
		printf(" ");
	}

	else if (mapObject == 'l')
	{
		if (pKey > 0)
		{
			pKey--;
			tempMap[pY + _y][pX + _x] = '0';

			setColor(white, black);
			gotoxy(pX + _x, pY + _y);
			printf(" ");
		}
	}

	else if (mapObject == 'q')
	{
		playing = 0;
	}

	else if (mapObject == 't')
	{
		playing = 0;
	}
}

void drawUI(void)
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