#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// 키보드 값  
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // 선택(스페이스바)  

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

char tempMap[14][56]; // 맵 임시저장할 배열  
char map[14][56] = { // 쉬운맵  
                                                                 // 가로 숫자는 위 배열크기에 맞추어 56개  
   {"1111111111111111111111111111111111111111111111111111111"}, // 세로 길이에 맞추어 14줄   
   {"1000000010000000000000000000000000000100000000000000001"},
   {"1000000010000000000000000000000000000100000000000000001"}, // 0 : 빈 공간 
   {"1000100010000001111111111111111110000100000000100000001"}, // 1 : 벽 
   {"100010k010000001000000000000000000000100000000100000001"}, // k : 열쇠 
   {"100010001000k001000000000000000000000100000000100000001"}, // l : 잠긴 문 
   {"100010001111111100000000000000000000010000000010000k001"}, // q : 탈출구  
   {"1000100000000000000000000100000000000100000000100000001"}, // t : 지뢰
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
	printf("게임이 종료되었습니다!!!");
	_getch();

	return 0;
}

void init() {

	system("mode con cols=56 lines=20 | title Escape Game");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	CONSOLE_CURSOR_INFO ConsoleCursor;

	ConsoleCursor.bVisible = 0; // false 또는 0 : 숨기기 
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	pKey = 0;
	playing = 1;
}

// 커서 위치 이동함수  
void gotoxy(int x, int y) {

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	COORD pos;

	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(consoleHandle, pos);
}

// 첫번째: 텍스트, 두번째: 배경  
void setColor(int forground, int background) {

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	
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

	else if (temp == ' ') { // 스페이스바(공백)이 선택 버튼  
		return SUBMIT;
	}
}

void titleDraw() {

	printf("\n\n\n\n"); // 맨위에 4칸 개행  
	printf("        #####    ###    ###    #    ####   ##### \n");
	printf("        #       #      #      # #   #   #  #     \n");
	printf("        ####    ####   #     #####  ####   ####  \n");
	printf("        #           #  #     #   #  #      #     \n");
	printf("        #####   ####    ###  #   #  #      ##### \n");
}

int menuDraw() {

	int x = 24;
	int y = 12;

	gotoxy(x - 2, y); // -2 한 이유는 > 를 출력해야하기 때문에  
	printf("> 게임시작");

	gotoxy(x, y + 1);
	printf("게임정보");

	gotoxy(x, y + 2);
	printf("  종료  ");

	while (1) { // 무한반복  

		int n = keyControl(); // 키보드 이벤트를 키값으로 받아오기  

		switch (n) {

		case UP: { // 입력된 키의 값이 UP인경우 (w) 
			if (y > 12) { // y는 12~14까지만 이동  
				gotoxy(x - 2, y); // x-2 하는 이유는 ">"를 두칸 이전에 출력하기위해  
				printf(" "); // 원래 위치를 지우고  

				gotoxy(x - 2, --y); // 새로 이동한 위치로 이동하여  
				printf(">"); // 다시 그리기  
			}
			break;
		}

		case DOWN: { // 입력된 키의 값이 DOWN인경우 (s) 
			if (y < 14) { // 최대 14  
				gotoxy(x - 2, y);
				printf(" ");

				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 12; // 스페이스바(선택)되었을 경우 y-12
			// y 시작 위치가 12였으므로 y-12 를 하면 0, 1, 2 세 숫자를 받을 수 있다.
		}
		}
	}
}

void infoDraw() {

	system("cls"); // 화면 모두 지우기  
	printf("\n\n");
	printf("                        [ 조작법 ]\n\n");
	printf("                    이동: W, A, S, D\n");
	printf("                    선택: 스페이스바\n\n\n\n\n\n\n");
	printf("               개발자: codevkr.tistory.com\n\n");
	printf("      스페이스바를 누르면 메인화면으로 이동합니다.");

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
	printf("                     [맵 선택]\n\n");

	gotoxy(x - 2, y);
	printf("> 쉬움");

	gotoxy(x, y + 1);
	printf("어려움");

	gotoxy(x, y + 2);
	printf("뒤로");

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
				pX = w;                           //플레이어 X,Y 위치 저장
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
		  // 아무일도 하지 않음
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
	printf("플레이어 위치:(%02d,%02d)", pX, pY);

	setColor(yellow, black);
	gotoxy(34, 16);
	printf("열쇠: %d개", pKey);
	setColor(white, black);
}