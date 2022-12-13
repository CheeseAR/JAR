#include<stdio.h>
#include<Windows.h>
#include<conio.h>

#define MAP_WIDTH	10  //맵의 크기
#define MAP_HEIGHT	10

#define ROAD 0
#define WALL 1
#define GEM 2
//바닥은 0,벽1,보석2

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define EXIT 27

//게임만들기
int Select;
int playerX;	//플레이어의 위치
int playerY;	//플레이어의 위치 ,현재(0,0) 플레이어는 길에만 위치할 수 있다.
int map[MAP_WIDTH][MAP_HEIGHT] =
{
	{0,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,1,1,0,1},
	{1,0,0,0,2,0,1,1,0,1},
	{1,1,1,1,1,0,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

enum CURSOR_TYPE
{
	NO_CURSOR,
	SOLID_CURSOR,
	NORMAL_CURSOR

};

void gotoxy(int x, int y);
void setcursortype(CURSOR_TYPE c);
void KeyProcess();
void DrawGame();
void GameProcess();



int main()
{
	setcursortype(NO_CURSOR);
	while (true) {
		KeyProcess();
		GameProcess();
		DrawGame();


		//_sleep(300); //지워지는 화면 (깜빡거리는 화면)을 완화해주기 300=>0.3초
		//system("cls"); //화면을 지워라.
	}
	return 0;
	//게임의 규칙 1.맵을 벗어나면 안된다. 2.벽으로는 들어갈수 없다. 3.보석을 찾으면 게임이 종료된다.
}


//원하는 좌표로 이동
void gotoxy(int x, int y)
{
	COORD pos = { 2 * x,y };//x축 이동이 y축이동보다 2배짧다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setcursortype(CURSOR_TYPE c)//커서 숨기는 함수
{
	CONSOLE_CURSOR_INFO cursorInfo; //구조체 (커서의 정보가 2개로 나눠져있음)

	switch (c)
	{
	case NO_CURSOR:
		cursorInfo.dwSize = 1; //크기를 얼마로 할것이다(dwsize)
		cursorInfo.bVisible = FALSE; //보이게 하는 것의 여부(bVisible),0=안보임
		break;
	case SOLID_CURSOR:
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = TRUE;
		break;
	case NORMAL_CURSOR:
		cursorInfo.dwSize = 20;
		cursorInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void KeyProcess()
{
	Select = -1;//값이 들어올때 마다 키값을 매칭되는게 없는 값 -1초기화 해준다 
	if (_kbhit()) //키보드 값이 들어오면
	{
		Select = _getch();
		if (Select == 224)
		{
			Select = _getch();
		}
	}
}

void DrawGame()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			gotoxy(x, y); //무언가를 그리기전에 커서를 그 위치로 보내준다.
			if (map[y][x] == ROAD)//0은길
			{
				if (playerX == x && playerY == y)
				{
					printf("♀"); //길과 플레이어의 위치가 겹치면 길대신 플레이어를 표시해준다.
				}
				else
				{
					printf("■");//특수문자는 2바이트
				}
			}
			else if (map[y][x] == WALL)//1은 벽
			{
				printf("▧");
			}
			else if (map[y][x] == GEM)
			{
				printf("★");
			}
		}//맵그리기
	}
}


void GameProcess()
{
	switch (Select)
	{
	case UP: //위로 움직임
		if (playerY - 1 >= 0)//맵을 벗어나면 안된다.
		{
			if (map[playerY - 1][playerX] == ROAD)
			{
				playerY--; //길일때만 움직일수 있도록 설정
			}
			else if (map[playerY - 1][playerX] == GEM) //보석을 찾으면 게임이 종료된다.
			{
				playerX = 0;
				playerY = 0;
			}
		}
		break;

	case DOWN:
		if (playerY + 1 < MAP_HEIGHT)//맵을 벗어나면 안된다.
		{
			if (map[playerY + 1][playerX] == ROAD)
			{
				playerY++; //길일때만 움직일수 있도록 설정
			}
			else if (map[playerY + 1][playerX] == GEM) //보석을 찾으면 게임이 종료된다.
			{
				playerX = 0;
				playerY = 0;
			}
		}
		break;

	case LEFT:
		if (playerX - 1 >= 0)
		{
			if (map[playerY][playerX - 1] == ROAD)
			{
				playerX--;
			}
			else if (map[playerY][playerX - 1] == GEM)
			{
				playerX = 0;
				playerY = 0;
			}
		}
		break;

	case RIGHT:
		if (playerX + 1 < MAP_WIDTH)
		{
			if (map[playerY][playerX + 1] == ROAD)
			{
				playerX++;
			}
			else if (map[playerY][playerX + 1] == GEM)
			{
				playerX = 0;
				playerY = 0;
			}
		}
		break;

	default:
		if (Select == EXIT)
			exit(0); //빠져나감
		break;
	}

}