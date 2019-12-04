// 본 프로그램 소스 코드는 C언어를 통해 콘솔게임 제작을 위한 사이트(https://codevkr.tistory.com/15?category=699626)의
// 프로젝트를 참고하였습니다.

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

char map[14][56] = { // 쉬운맵  
	// 가로 숫자는 위 배열크기에 맞추어 56개  
	{"1111111111111111111111111111111111111111111111111111111"}, // 세로 길이에 맞추어 14줄   
	{"1000000010000000000000000000000000000000000000000000001"},
	{"1000000010000000000000000000000000000000000000000000001"}, // 0 : 빈 공간 
	{"1000100010000000000000000000000000000000000000000000001"}, // 1 : 벽 
	{"1000100010000000000000000000000000000000000000000000001"}, // k : 열쇠 
	{"1000100010000000000000000000000000000000000000000000001"}, // l : 잠긴 문 
	{"1000100011111100000000000000000000000000000000000000001"}, // q : 탈출구  
	{"1000100000000100000000000000000000000000000000000000001"},
	{"1000100010000100000000000000000000000000000000000000001"},
	{"10001000100k0100000000000000000000000000000000001111111"},
	{"1000100010000100000000000000000000000000000000001000001"},
	{"10s010001111111111111111111111111111111111111111100q001"},
	{"10001000l0000000000000000000000000000000000000000000001"},
	{"1111111111111111111111111111111111111111111111111111111"}
};


int keyControl(void);
void titleDraw(void);
int menuDraw(void);

void infoDraw(void);

void init();
void gotoxy(int, int);
void setColor(int, int);
void drawMap(int *pX, int *pY, char(*tMap)[56]);
int move(char(*tMap)[56], int *pX, int *pY, int _x, int _y, int *pKey);

void gLoop(void);
void drawUI(int pX, int pY, int pKey);


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
		menuCode = 5;
		system("cls");
	}

	gotoxy(12, 16);
	printf("게임이 종료되었습니다!!!");
	_getch();

	return 0;
}

void init(void)
{
	system("mode con cols=56 lines=20 | title Escape Game");

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0; // false 또는 0 : 숨기기 
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

}

// 커서 위치 이동함수  
void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// 첫번째: 텍스트, 두번째: 배경  
void setColor(int forground, int background)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}


int keyControl(void) {
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
	{ // 스페이스바(공백)이 선택 버튼  
		return SUBMIT;
	}
}

void titleDraw(void) {

	printf("\n\n\n\n"); // 맨위에 4칸 개행  
	printf("        #####    ###    ###    #    ####   ##### \n");
	printf("        #       #      #      # #   #   #  #     \n");
	printf("        ####    ####   #     #####  ####   ####  \n");
	printf("        #           #  #     #   #  #      #     \n");
	printf("        #####   ####    ###  #   #  #      ##### \n");
}

int menuDraw(void) {
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

void infoDraw(void)
{
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

void drawMap(int *pX, int *pY, char (*tMap)[56])
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
				//플레이어 X,Y 위치 저장
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
	int mKey;
	int cX, cY;
	int cKey=0;
	int playing = 1;
	char tempMap[14][56]; // 맵 임시저장할 배열  

	memcpy(tempMap, map, sizeof(tempMap));

	drawMap(&cX, &cY, tempMap);
	while (playing)
	{
		drawUI(cX, cY, cKey);
		mKey = keyControl();
		switch (mKey)
		{
		case UP:
			playing = move(tempMap, &cX, &cY, 0, -1,&cKey);
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
	//playing = 1;
}

int move(char(*tMap)[56], int *pX, int *pY, int _x, int _y, int *pKey)
{
	int playflag = 1;
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
	//	else if (mapObject == '1')
	//	{
			// 아무일도 하지 않음
	//	}
	else if (mapObject == 'k')
	{
		*pKey += 1;
		tMap[*pY + _y][*pX + _x] = '0';
		gotoxy(*pX + _x, *pY + _y);
		printf(" ");

	}
	else if (mapObject == 'l')
	{
		if (pKey > 0)
		{
			*pKey -=1;
			tMap[*pY + _y][*pX + _x] = '0';
			setColor(white, black);
			gotoxy(*pX + _x, *pY + _y);
			printf(" ");
		}

	}
	else if (mapObject == 'q')
	{
		playflag = 0;
	}

	return playflag;
}

void drawUI(int pX, int pY, int pKey)
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