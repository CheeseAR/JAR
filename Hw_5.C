#include<stdio.h>
#include<Windows.h>

//���ϴ� �л�����ŭ�� �л� ������ ����ü�� �Է� �����ؼ� ��� �Ǵ� �Է��� ������ ���� �ϴ� ���α׷�

enum blood //������
{
	A�� = 1,
	B��,
	O��,
	AB��
};

typedef struct Student //�л�����ü
{
	char name[20];
	int number;
	enum blood Myblood;
	float height;
	float weight;

}_STUDENT, * _LPSTUDENT;

//�Լ������
int GetInputInt(const char* dialog, int no);
float GetInputFloat(const char* dialog, int no);
void ShowStudentInfo(struct Student person);

int main()
{
	int inwon = 0; //����� ������ �Է��Ұ����� �����ϴ� ����
	_LPSTUDENT pStudent = { 0, };
	int n = 0;
	int choiceInfo = 0;		//� �л��� ������ ��¶Ǵ� �����Ұ����� �����ϴ� ����
	int choiceNumber = 0;	//������ ����Ұ����� �����Ұ����� ���� ���������� �����ϴ� ����

	printf("����� �л������� �Է��Ͻðڽ��ϱ� : ");
	scanf_s(" %d", &inwon);
	printf("%d���� �л������� �Է��ϰڽ��ϴ�.\n", inwon);

	if (pStudent == 0) //����ü�����͸� �л��� �ο�����ŭ �����Ҵ����ش�.
	{
		pStudent = (_LPSTUDENT)malloc(inwon * sizeof(_STUDENT));
	}
	for (n = 0; n < inwon; n++)
	{
		printf("===============================\n");
		printf("%d��° �л��� �̸��� �Է��ϼ���: ", n + 1);
		scanf_s(" %s", pStudent[n].name, sizeof(pStudent[n].name));
		pStudent[n].number = GetInputInt("%d��° �л��� �й��� �Է��ϼ���: ", n + 1);
		pStudent[n].height = GetInputFloat("%d��° �л��� Ű�� �Է��ϼ���: ", n + 1);
		pStudent[n].weight = GetInputFloat("%d��° �л��� �����Ը� �Է��ϼ���: ", n + 1);
		printf("1. A��	2.B��	3.O��	4.AB��\n");
		pStudent[n].Myblood = GetInputInt("%d��° �л��� �������� �Է��ϼ���: ", n + 1);
	}
	printf("===============================\n");
	printf("�Է��� �������ϴ�.\n");
	printf("===============================\n");
	do {
		printf("1. ���� ���\n");
		printf("2. ���� ����\n");
		printf("3. ������\n");
		printf("��ȣ�� �����ϼ���: ");
		scanf_s(" %d", &choiceNumber);
		if (choiceNumber == 3) //3. �����⸦ ���� �Ѵٸ� �ݺ����� �ٷ� ���������� �ְ� ���ش�.
		{
			return 0;
		}
		printf("===============================\n");
		for (n = 0; n < inwon; n++)
		{
			printf("%d�� %s\n", n + 1, pStudent[n]);
		}
		printf("===============================\n");

		if (choiceNumber == 1)
		{
			printf("������ ������ ���ðڽ��ϱ� : ");
			scanf_s(" %d", &choiceInfo);
			for (n = 0; n < inwon; n++)
			{
				if (n + 1 == choiceInfo)
				{
					ShowStudentInfo(pStudent[n]);
				}
			}
		}
		else if (choiceNumber == 2)
		{

			printf("������ ������ �����Ͻðڽ��ϱ� : ");
			scanf_s(" %d", &choiceInfo);
			for (n = 0; n < inwon; n++)
			{
				if (n + 1 == choiceInfo)
				{
					printf("%d�� %s�л��� ������ �����մϴ�.\n", n + 1, pStudent[n].name);
					printf("������ %d�� �л��� �̸��� �Է����ּ��� : ", n + 1);
					scanf_s(" %s", pStudent[n].name, sizeof(pStudent[n].name));
					pStudent[n].number = GetInputInt("������ %d�� �л��� �й��� �Է��ϼ��� : ", n + 1);
					pStudent[n].height = GetInputFloat("������ %d�� �л��� Ű�� �Է��ϼ��� : ", n + 1);
					pStudent[n].weight = GetInputFloat("������ %d�� �л��� �����Ը� �Է��ϼ��� : ", n + 1);
					printf("1. A��	2.B��	3.O��	4.AB��\n");
					pStudent[n].Myblood = GetInputInt("������ %d�� �л��� �������� �Է��ϼ���: ", n + 1);
				}
			}
		}
	} while (choiceNumber != 3); //3�� �����⸦ �Է����� ���� ���� �ݺ����ش�.

	if (pStudent != 0)
	{
		free(pStudent);
	}

	system("pause");
	return 0;
}

//�Լ����Ǻ�
void ShowStudentInfo(struct Student person) //������ ������ִ� �Լ�
{
	float BMI;
	printf("===============================\n");
	printf("[%s]�л� ����\n", person.name);
	printf("===============================\n");
	printf("%d�й� ", person.number);
	switch (person.Myblood)
	{
	case 1:
		printf("A���� �л��Դϴ�.\n");
		break;
	case 2:
		printf("B���� �л��Դϴ�.\n");
		break;
	case 3:
		printf("O���� �л��Դϴ�.\n");
		break;
	case 4:
		printf("AB���� �л��Դϴ�.\n");
		break;
	}
	person.height = person.height * 0.01;
	BMI = person.weight / (person.height * person.height);
	person.height = person.height * 100;
	printf("Ű %1.1fCm,������ %1.1fKg�� bmi��ġ%1.1f�Դϴ�.\n", person.height, person.weight, BMI);
	printf("===============================\n");
}
int GetInputInt(const char* dialog, int no) //int���� �Է¹޾Ƽ� �������ִ� �Լ�
{
	int input;
	printf(dialog, no);
	scanf_s(" %d", &input);
	return input;
}

float GetInputFloat(const char* dialog, int no)	//float���� �Է¹޾Ƽ� �������ִ� �Լ�
{
	float input;
	printf(dialog, no);
	scanf_s(" %f", &input);
	return input;
}