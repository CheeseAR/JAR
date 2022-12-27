#include<stdio.h>
#include<Windows.h>
#include<time.h>

//�л��� ����ü�� ���� ������ ������ �Է��ϰų� ������ ���� �־��ְ� �Լ��� ����� �Լ��� ���� ���ǿ� �°� ������ִ� ���α׷�

enum eSubject
{
	���� = 0,
	����,
	����
};

typedef struct arr
{
	enum eSubject score[3]; //���� ���� ���� ������ �����ϴ� �迭
	enum eSubject Rank[3];	//�� ������ ������ �����ϴ� �迭

}_ARR, * _LPARR;

//����ü
typedef struct Student
{
	char name[20];
	int class;
	int number;
	float averageScore;
	int totalRank;
	_ARR array;
}_STUDENT, * _LPSTUDENT;

//�Լ������
int GetInputInt(const char* dialog, int no);
int RankInput(_LPSTUDENT student, int count, int index);
void ShowInput(_LPSTUDENT student, int count);
void showTotalRank(_LPSTUDENT student, int count);
void showSubjectRank(_LPSTUDENT student, int count, int Index);
void showAverageUp(_LPSTUDENT student, int count);

int main()
{
	srand(time(0));
	_STUDENT student[5];			
	_LPSTUDENT pStudent = 0;
	int n = 0, m = 0;
	int rank[5] = { 1,1,1,1,1 };  //5���� �л��� �� ������ ���ϱ� ���� ��� ������ 1�� �������ش�.
	int InputNumber = 0;		  //� ������ �������� �����ϴ� ����
	printf("5���� �л��� ������ �Է��ϰڽ��ϴ�.\n");
	for (n = 0; n < 5; n++)
	{
		pStudent = &student[n];
		//�л��� �̸��� �� ��ȣ�� �Է¹޴´�.
		printf("%d�� �л��� �̸��� �Է��ϼ��� : ", n + 1);
		scanf_s(" %s", pStudent->name, sizeof(pStudent->name));
		pStudent->class = GetInputInt("%d�� �л��� ���� �Է��ϼ��� : ", n + 1);
		pStudent->number = GetInputInt("%d�� �л��� �й��� �Է��ϼ���: ", n + 1);
		//����, ����, ���� ������ 45~100�������� ������ ���� �������ش�.

		pStudent->array.score[����] = rand() % 56 + 45; // �������� ����
		pStudent->array.score[����] = rand() % 56 + 45; // �������� ����
		pStudent->array.score[����] = rand() % 56 + 45; // �������� ����
		pStudent->averageScore = (pStudent->array.score[����] + pStudent->array.score[����] + pStudent->array.score[����]) / 3;
		//�л��� (����,����,����)������ ���� ����� �����ش�.
	}
	//��ü ������ ���ϱ�
	for (n = 0; n < 5; n++)
	{
		for (m = 0; m < 5; m++)
		{							//���� rank[5]�� ��� 1�� �ʱ�ȭ �Ǿ��ִ�.
			if (student[n].averageScore < student[m].averageScore) // �ε����� 0���� �л��� ��� �л��� ������ �ڽ��� ������ ū���� �����Ѵٸ�
			{	
				rank[n] = rank[n] + 1;  //�ڽ��� �ε��� rank��(rank[n])�� 1�� ���������ش�.
			}
		}
	}
	for (n = 0; n < 5; n++)
	{
		student[n].totalRank = rank[n]; //����ü���� ��ü������ �����ϴ� ���� ��� ���� ������ �������ش�.
	}

	RankInput(student, 5, ����); //���� ������ �������ش�.
	RankInput(student, 5, ����);	//���� ������ �������ش�.
	RankInput(student, 5, ����);	//���� ������ �������ش�.
	
	ShowInput(student,5);	//5���� �Էµ� ������ �����ش�.
	
	printf("1.��ü ����� ���� ������ ȭ�鿡 ���\n");
	printf("2.���������� ���� ������ ȭ�鿡 ���\n");
	printf("3.���������� ���� ������ ȭ�鿡 ���\n");
	printf("4.���������� ���� ������ ȭ�鿡 ���\n");
	printf("5.�ټ����� ����� ����̻��� �л��� ȭ�鿡 ���\n");
	printf("��ȣ�� �Է��ϼ��� : ");
	scanf_s(" %d", &InputNumber);

	switch (InputNumber)
	{
	case 1:
		showTotalRank(student, 5);
		break;
	case 2:
		showSubjectRank(student, 5, ����);
		break;
	case 3:
		showSubjectRank(student, 5, ����);
		break;
	case 4:
		showSubjectRank(student, 5, ����);
		break;
	case 5:
		showAverageUp(student, 5);
		break;
	}


	system("pause");
	return 0;
}

//�Լ����Ǻ�
int GetInputInt(const char* dialog, int no) //int���� �Է��ؼ� �����ϱ� ���� �Լ�
{
	int input;
	printf(dialog, no);
	scanf_s(" %d", &input);
	return input;
}

int RankInput(_LPSTUDENT student, int count, int index) //����, ����, ������ �� ������ ���ϴ� �Լ�  
//count������ ��� �迭���� �Է����ְ� index���� ����, ����, ���� �� �ش��ϴ� �ε��� ��ȣ�� �Է����ش�.
{
	int rank[5] = { 1,1,1,1,1 }; //���� �����Լ����� ���� ��ü ��������� �����ϰ� �ۼ����ش�.
	int n = 0, m = 0;
	for (n = 0; n < count; n++)
	{
		for (m = 0; m < count; m++)
		{
			if (student[n].array.score[index] < student[m].array.score[index])
				rank[n] = rank[n] + 1;
		}
	}
	for (n = 0; n < count; n++)
	{
		student[n].array.Rank[index] = rank[n];
	}
	return 0;
}
void ShowInput(_LPSTUDENT student, int count) // ���� �Է��� ������ ������ ������ �� ���� �� Ȯ���ϱ� ���� ������ �����ֱ� ���� �Լ�
//count���� ��� �迭���� �Է����ش�.
{	int n = 0;
	printf("===============================================\n");
	for (n = 0; n < count; n++)
	{
		printf("%d��\n", n + 1);
		printf("�̸�: %s\n", student[n].name);
		printf("�б�: %d��, �й�: %d\n", student[n].class, student[n].number);
		printf("����: %d��, ����: %d��, ����: %d��\n", student[n].array.score[����], student[n].array.score[����], student[n].array.score[����]);
		printf("������� : %1.1f��\n", student[n].averageScore);
		printf("===============================================\n");
	}
	return;
}
void showTotalRank(_LPSTUDENT student, int count)//��ü����� ���ʴ�� ������ִ� �Լ�
//count���� ��� �迭���� �Է����ش�.
{
	int n = 0, m = 0;
	for (n = 0; n < count; n++)
	{
		for (m = 0; m < count; m++)
		{
			if (student[m].totalRank == n + 1)
			{
				printf("%d�� %s\n", n + 1, student[m].name);
			}
		}
	}
	return;
}

void showSubjectRank(_LPSTUDENT student, int count, int Index) //�� ���� ��� ������� ������ִ� �Լ�
//count���� ��� �迭���� �Է����ش�.index���� ����, ����, ���п� �ش��ϴ� ���� �־��ش�.
{
	int n = 0, m = 0;
	for (n = 0; n < count; n++)
	{
		for (m = 0; m < count; m++)
		{
			if (student[m].array.Rank[Index] == n + 1)
			{
				printf("%d�� %s\n", n + 1, student[m].name);
			}
		}
	}
	return;
}

void showAverageUp(_LPSTUDENT student, int count) //5���� ��ü����� ��պ��� ���� ����� ���� �л��� ������ִ� �Լ�
//count���� ��� �迭���� �Է����ش�.
{
	float average = 0.0f;
	int n = 0;
	for (n = 0; n < count; n++)
	{
		average += student[n].averageScore;
	}
	average = average / count;
	printf("%d���� ����� %1.1f�Դϴ�.\n", count, average);
	printf("===============================================\n");
	printf("����̻��� �л��� ");
	for (n = 0; n < count; n++)
	{
		if (student[n].averageScore > average)
		{
			printf(" %d�� %s ", n + 1, student[n].name);
		}

	}
	printf("�Դϴ�.\n");
	printf("===============================================\n");
	return;
}