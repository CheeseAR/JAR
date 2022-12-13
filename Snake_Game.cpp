#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>


#define MAP_WIDTH  19 //맵의 넓이
#define MAP_HEIGHT 17 //맵의 높이

#define LEFT  75
#define RIGHT  77
#define UP  72
#define DOWN  80
#define ESC  27

#define HEAD   0 //뱀의 머리

//지렁이 게임


enum CURSOR_TYPE
{
	NO_CURSOR,
	SOLID_CURSOR,
	NORMAL_CURSOR

};

void gotoxy(int x, int y);
void KeyProcess();
void DrawMap();
void Initialized();
void DrawSnake();
void CreatFood();
void GameProcess();
void setcursortype(CURSOR_TYPE c);

int snakeX[255];
int snakeY[255]; //뱀의 좌표
int length; //뱀의길이
int dir; //지렁이의 방향
int speed; 
int isStart;
int key;
int foodX;
int foodY;
int isTry = 0;


//뱀의 크기는 머리,몸통,꼬리로 나눠준다 
int main()
{

	Initialized();
	setcursortype(NO_CURSOR);
	while (true)
	{

		KeyProcess();
		if (!isStart)
			continue; //밑에 식말고 위의 코드로 올라간다.
		GameProcess();
		DrawSnake(); //조건에 따라 실행이 안되게 한다.
		Sleep(speed); //슬립값을 감소 시키면 게임의 속도가 빨라짐
	}
	return 0;
}


void GameProcess()
{
	if (snakeX[HEAD] == foodX && snakeY[HEAD] == foodY) //먹이를 먹은상황
	{
		length++; //뱀의 길이가 길어짐
		snakeX[length - 1] = snakeX[length - 2];//꼬리좌표를 설정해주지 않으면 (0,0)으로 되기때문에 꼬리좌표를 변경해주어서 (0,0)위치의 벽이 사라지는 것을 해결해준다.
		snakeY[length - 1] = snakeY[length - 2];
		gotoxy(snakeX[length-2], snakeY[length-2]);
		printf("◆");
		speed -= 10;
		if (speed < 20) //먹이를 먹으면 뱀의 속도를 조절
			speed = 20;
		CreatFood();
	}
	if (snakeX[HEAD] <= 0 || snakeX[HEAD] >= MAP_WIDTH - 1 ||
		snakeY[HEAD] <= 0 || snakeY[HEAD] >= MAP_HEIGHT - 1)//벽에 부딪히면 게임오버
	{
		Initialized(); //게임오버(초기화화면)

	}
	for (int i = 1; i < length; i++)
	{
		if (snakeX[HEAD] == snakeX[i] && snakeY[HEAD] == snakeY[i])
		{	//머리와 몸통이 겹치면
			Initialized(); //게임오버

			break;
		}
	}
}


void gotoxy(int x, int y)
{
	COORD pos = { 2 * x,y };//x축 이동이 y축이동보다 2배짧다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void KeyProcess()
{
	int key = 0;
	if (_kbhit())
	{
		key = _getch();
		if (key == 224)
		{
			key = _getch();
			if ((dir == LEFT && key != RIGHT) ||
				(dir == RIGHT && key != LEFT) ||
				(dir == UP && key != DOWN) ||
				(dir == DOWN && key != UP)) //180도로 움직일수가 없다

			{
				if (isStart == 0) //키가 눌리면 움직임을 시작해라
					isStart = 1;
				dir = key;
			}
		}
	}
}

void Initialized() //뱀의 초기화
{
	system("cls");
	DrawMap();
	isStart = 0;
	length = 4;
	dir = RIGHT;
	speed = 300;
	foodX = MAP_WIDTH / 2 + 4;
	foodY = MAP_WIDTH / 2;
	gotoxy(foodX, foodY);
	printf("♥"); //먹이 초기화
	snakeX[HEAD] = MAP_WIDTH / 2 - 4; //뱀의 머리는 정중앙으로부터 뒤로 4칸 물러나 있었다
	snakeY[HEAD] = MAP_WIDTH / 2; //뱀의 머리는 정중앙으로부터 뒤로 4칸 물러나 있었다
	gotoxy(snakeX[HEAD], snakeY[HEAD]);
	printf("◎");//뱀의 머리
	for (int i = 1; i < length; i++)//머리제외
	{
		snakeX[i] = snakeX[HEAD] - i;
		snakeY[i] = snakeY[HEAD]; //머리 높이의 Y는 같다.
		gotoxy(snakeX[i], snakeY[i]);
		printf("◆");//뱀의 몸통
	}
}


void DrawSnake()
{

	speed = 300;
	//뱀의 움직임,머리-몸통 순서로 이동,머리는 현재위치에 가는 방향 앞에 하나더생기고, 머리자리에 몸통이 온다. 맨뒷부분은 결과적으로 사라진다.
	//뱀의 움직임
	gotoxy(snakeX[HEAD], snakeY[HEAD]);
	printf("◆");
	gotoxy(snakeX[length - 1], snakeY[length - 1]);
	printf("  "); //공백 2개 

	for (int i = length - 1; i > 0; i--)
	{	//뒤에서부터 체크
		snakeX[i] = snakeX[i - 1];   // 맨마지막부분
		snakeY[i] = snakeY[i - 1];	// 하나씩 다 땡겨짐
	}
	switch (dir)
	{
	case LEFT:
		snakeX[HEAD]--; //왼쪽으로 이동시 HEAD의 X좌표가 1씩 줄어든다
		break;
	case RIGHT:
		snakeX[HEAD]++;
		break;
	case UP:
		snakeY[HEAD]--; //위쪽으로 이동시 HEAD의 Y좌표는 1씩 줄어든다.
		break;
	case DOWN:
		snakeY[HEAD]++;
		break;
	}
	gotoxy(snakeX[HEAD], snakeY[HEAD]);
	printf("◎");

}

void DrawMap()
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		gotoxy(x, 0);//x는 x부터 y는 0 ,맨위에 벽
		printf("▨");//맵그리기
		gotoxy(x, MAP_HEIGHT - 1); //맨아래 벽
		printf("▨");
	}
	for (int y = 1; y < MAP_HEIGHT - 1; y++)
	{ //맨위랑 맨아래제외 옆벽
		gotoxy(0, y);
		printf("▨");
		gotoxy(MAP_WIDTH - 1, y);
		printf("▨");
	}
}

void CreatFood()
{   //먹이의 좌표를 랜덤으로 구하기 조건 1.맵안에 나오게해준다. 2.뱀의 몸통이랑 겹치지 않게 해준다.
	do
	{
		isTry = 0;//먹이를 다시 그려준다.
		//0~18범위중 1~17까지 랜덤한값이 나와야 한다
		foodX = rand() % (MAP_WIDTH - 2) + 1;
		foodY = rand() % (MAP_HEIGHT - 2) + 1;
		for (int i = 0; i < length; i++)
		{
			if (foodX == snakeX[i] && foodY == snakeY[i])
			{// 몸통과 먹이가 겹치는 경우
				isTry = 1; // 1 == true
				break;
			}
		}
	} while (isTry); //isTry가 1(true)이면 반복해준다.

	gotoxy(foodX, foodY); //반복문을 빠져나왔다면 반복문에서 구해준 랜덤한 x,y좌표값으로 이동해 먹이를 그려준다.
	printf("♥");
}

void setcursortype(CURSOR_TYPE c)//커서 숨기는 함수
{
	CONSOLE_CURSOR_INFO cursorInfo; //구조체 (커서의 정보가 2개로 나눠져있음)

	switch (c)
	{
	case NO_CURSOR:
		cursorInfo.dwSize = 1; //크기를 얼마로 할것이다(dwsize)
		cursorInfo.bVisible = FALSE; //보이게 하는 것의 여부(bVisible), 0=안보임
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