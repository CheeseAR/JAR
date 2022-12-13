#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>


#define MAP_WIDTH  19 //���� ����
#define MAP_HEIGHT 17 //���� ����

#define LEFT  75
#define RIGHT  77
#define UP  72
#define DOWN  80
#define ESC  27

#define HEAD   0 //���� �Ӹ�

//������ ����


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
int snakeY[255]; //���� ��ǥ
int length; //���Ǳ���
int dir; //�������� ����
int speed; 
int isStart;
int key;
int foodX;
int foodY;
int isTry = 0;


//���� ũ��� �Ӹ�,����,������ �����ش� 
int main()
{

	Initialized();
	setcursortype(NO_CURSOR);
	while (true)
	{

		KeyProcess();
		if (!isStart)
			continue; //�ؿ� �ĸ��� ���� �ڵ�� �ö󰣴�.
		GameProcess();
		DrawSnake(); //���ǿ� ���� ������ �ȵǰ� �Ѵ�.
		Sleep(speed); //�������� ���� ��Ű�� ������ �ӵ��� ������
	}
	return 0;
}


void GameProcess()
{
	if (snakeX[HEAD] == foodX && snakeY[HEAD] == foodY) //���̸� ������Ȳ
	{
		length++; //���� ���̰� �����
		snakeX[length - 1] = snakeX[length - 2];//������ǥ�� ���������� ������ (0,0)���� �Ǳ⶧���� ������ǥ�� �������־ (0,0)��ġ�� ���� ������� ���� �ذ����ش�.
		snakeY[length - 1] = snakeY[length - 2];
		gotoxy(snakeX[length-2], snakeY[length-2]);
		printf("��");
		speed -= 10;
		if (speed < 20) //���̸� ������ ���� �ӵ��� ����
			speed = 20;
		CreatFood();
	}
	if (snakeX[HEAD] <= 0 || snakeX[HEAD] >= MAP_WIDTH - 1 ||
		snakeY[HEAD] <= 0 || snakeY[HEAD] >= MAP_HEIGHT - 1)//���� �ε����� ���ӿ���
	{
		Initialized(); //���ӿ���(�ʱ�ȭȭ��)

	}
	for (int i = 1; i < length; i++)
	{
		if (snakeX[HEAD] == snakeX[i] && snakeY[HEAD] == snakeY[i])
		{	//�Ӹ��� ������ ��ġ��
			Initialized(); //���ӿ���

			break;
		}
	}
}


void gotoxy(int x, int y)
{
	COORD pos = { 2 * x,y };//x�� �̵��� y���̵����� 2��ª��.
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
				(dir == DOWN && key != UP)) //180���� �����ϼ��� ����

			{
				if (isStart == 0) //Ű�� ������ �������� �����ض�
					isStart = 1;
				dir = key;
			}
		}
	}
}

void Initialized() //���� �ʱ�ȭ
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
	printf("��"); //���� �ʱ�ȭ
	snakeX[HEAD] = MAP_WIDTH / 2 - 4; //���� �Ӹ��� ���߾����κ��� �ڷ� 4ĭ ������ �־���
	snakeY[HEAD] = MAP_WIDTH / 2; //���� �Ӹ��� ���߾����κ��� �ڷ� 4ĭ ������ �־���
	gotoxy(snakeX[HEAD], snakeY[HEAD]);
	printf("��");//���� �Ӹ�
	for (int i = 1; i < length; i++)//�Ӹ�����
	{
		snakeX[i] = snakeX[HEAD] - i;
		snakeY[i] = snakeY[HEAD]; //�Ӹ� ������ Y�� ����.
		gotoxy(snakeX[i], snakeY[i]);
		printf("��");//���� ����
	}
}


void DrawSnake()
{

	speed = 300;
	//���� ������,�Ӹ�-���� ������ �̵�,�Ӹ��� ������ġ�� ���� ���� �տ� �ϳ��������, �Ӹ��ڸ��� ������ �´�. �ǵ޺κ��� ��������� �������.
	//���� ������
	gotoxy(snakeX[HEAD], snakeY[HEAD]);
	printf("��");
	gotoxy(snakeX[length - 1], snakeY[length - 1]);
	printf("  "); //���� 2�� 

	for (int i = length - 1; i > 0; i--)
	{	//�ڿ������� üũ
		snakeX[i] = snakeX[i - 1];   // �Ǹ������κ�
		snakeY[i] = snakeY[i - 1];	// �ϳ��� �� ������
	}
	switch (dir)
	{
	case LEFT:
		snakeX[HEAD]--; //�������� �̵��� HEAD�� X��ǥ�� 1�� �پ���
		break;
	case RIGHT:
		snakeX[HEAD]++;
		break;
	case UP:
		snakeY[HEAD]--; //�������� �̵��� HEAD�� Y��ǥ�� 1�� �پ���.
		break;
	case DOWN:
		snakeY[HEAD]++;
		break;
	}
	gotoxy(snakeX[HEAD], snakeY[HEAD]);
	printf("��");

}

void DrawMap()
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		gotoxy(x, 0);//x�� x���� y�� 0 ,������ ��
		printf("��");//�ʱ׸���
		gotoxy(x, MAP_HEIGHT - 1); //�ǾƷ� ��
		printf("��");
	}
	for (int y = 1; y < MAP_HEIGHT - 1; y++)
	{ //������ �ǾƷ����� ����
		gotoxy(0, y);
		printf("��");
		gotoxy(MAP_WIDTH - 1, y);
		printf("��");
	}
}

void CreatFood()
{   //������ ��ǥ�� �������� ���ϱ� ���� 1.�ʾȿ� ���������ش�. 2.���� �����̶� ��ġ�� �ʰ� ���ش�.
	do
	{
		isTry = 0;//���̸� �ٽ� �׷��ش�.
		//0~18������ 1~17���� �����Ѱ��� ���;� �Ѵ�
		foodX = rand() % (MAP_WIDTH - 2) + 1;
		foodY = rand() % (MAP_HEIGHT - 2) + 1;
		for (int i = 0; i < length; i++)
		{
			if (foodX == snakeX[i] && foodY == snakeY[i])
			{// ����� ���̰� ��ġ�� ���
				isTry = 1; // 1 == true
				break;
			}
		}
	} while (isTry); //isTry�� 1(true)�̸� �ݺ����ش�.

	gotoxy(foodX, foodY); //�ݺ����� �������Դٸ� �ݺ������� ������ ������ x,y��ǥ������ �̵��� ���̸� �׷��ش�.
	printf("��");
}

void setcursortype(CURSOR_TYPE c)//Ŀ�� ����� �Լ�
{
	CONSOLE_CURSOR_INFO cursorInfo; //����ü (Ŀ���� ������ 2���� ����������)

	switch (c)
	{
	case NO_CURSOR:
		cursorInfo.dwSize = 1; //ũ�⸦ �󸶷� �Ұ��̴�(dwsize)
		cursorInfo.bVisible = FALSE; //���̰� �ϴ� ���� ����(bVisible), 0=�Ⱥ���
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