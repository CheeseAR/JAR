#include<stdio.h>
#include<Windows.h>
#include<conio.h>

#define MAP_WIDTH	10  //���� ũ��
#define MAP_HEIGHT	10

#define ROAD 0
#define WALL 1
#define GEM 2
//�ٴ��� 0,��1,����2

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define EXIT 27

//���Ӹ����
int Select;
int playerX;	//�÷��̾��� ��ġ
int playerY;	//�÷��̾��� ��ġ ,����(0,0) �÷��̾�� �濡�� ��ġ�� �� �ִ�.
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


		//_sleep(300); //�������� ȭ�� (�����Ÿ��� ȭ��)�� ��ȭ���ֱ� 300=>0.3��
		//system("cls"); //ȭ���� ������.
	}
	return 0;
	//������ ��Ģ 1.���� ����� �ȵȴ�. 2.�����δ� ���� ����. 3.������ ã���� ������ ����ȴ�.
}


//���ϴ� ��ǥ�� �̵�
void gotoxy(int x, int y)
{
	COORD pos = { 2 * x,y };//x�� �̵��� y���̵����� 2��ª��.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setcursortype(CURSOR_TYPE c)//Ŀ�� ����� �Լ�
{
	CONSOLE_CURSOR_INFO cursorInfo; //����ü (Ŀ���� ������ 2���� ����������)

	switch (c)
	{
	case NO_CURSOR:
		cursorInfo.dwSize = 1; //ũ�⸦ �󸶷� �Ұ��̴�(dwsize)
		cursorInfo.bVisible = FALSE; //���̰� �ϴ� ���� ����(bVisible),0=�Ⱥ���
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
	Select = -1;//���� ���ö� ���� Ű���� ��Ī�Ǵ°� ���� �� -1�ʱ�ȭ ���ش� 
	if (_kbhit()) //Ű���� ���� ������
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
			gotoxy(x, y); //���𰡸� �׸������� Ŀ���� �� ��ġ�� �����ش�.
			if (map[y][x] == ROAD)//0����
			{
				if (playerX == x && playerY == y)
				{
					printf("��"); //��� �÷��̾��� ��ġ�� ��ġ�� ���� �÷��̾ ǥ�����ش�.
				}
				else
				{
					printf("��");//Ư�����ڴ� 2����Ʈ
				}
			}
			else if (map[y][x] == WALL)//1�� ��
			{
				printf("��");
			}
			else if (map[y][x] == GEM)
			{
				printf("��");
			}
		}//�ʱ׸���
	}
}


void GameProcess()
{
	switch (Select)
	{
	case UP: //���� ������
		if (playerY - 1 >= 0)//���� ����� �ȵȴ�.
		{
			if (map[playerY - 1][playerX] == ROAD)
			{
				playerY--; //���϶��� �����ϼ� �ֵ��� ����
			}
			else if (map[playerY - 1][playerX] == GEM) //������ ã���� ������ ����ȴ�.
			{
				playerX = 0;
				playerY = 0;
			}
		}
		break;

	case DOWN:
		if (playerY + 1 < MAP_HEIGHT)//���� ����� �ȵȴ�.
		{
			if (map[playerY + 1][playerX] == ROAD)
			{
				playerY++; //���϶��� �����ϼ� �ֵ��� ����
			}
			else if (map[playerY + 1][playerX] == GEM) //������ ã���� ������ ����ȴ�.
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
			exit(0); //��������
		break;
	}

}