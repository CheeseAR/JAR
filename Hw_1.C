#include<stdio.h>
#include<windows.h>
#include<time.h>

int main()
{
	srand(time(0));
	
	float** pStudentScore = 0;
	int classCnt = 0;
	int StudentsPerClass = 0;
	float totalScore = 0.0f;
	float averageGrade = 0.0f;
	int n = 0, m = 0;

	int select = 0; //��ȣ ������ ���� ����
	int highClass = 0; //��������� ���� ���� ���� �����ϴ� ����
	int* highStudent = 0; //��������� ���� ���� �л��� �ݰ� ��ȣ�� ����
	float highAverage = 0.0f; //��������� ���� ���� ���� �������
	float highAveragePersonal = 0.0f; //��������� ���� ���� �л��� �������

	printf("1�г⿡ ��� ���� �ֽ��ϱ� : ");
	scanf_s(" %d", &classCnt);
	printf("�ѹݴ� ����� �л��� �ֽ��ϱ� : ");
	scanf_s(" %d", &StudentsPerClass);
	printf("==============================\n");
	
	//�����Ҵ�
	if (pStudentScore == 0)
	{
		pStudentScore = (float**)malloc(classCnt * sizeof(float*));
		for (n = 0; n < classCnt; n++)
		{
			pStudentScore[n] = (float*)malloc(StudentsPerClass * sizeof(float));
		}
	}

	if (highStudent == 0)
	{
		highStudent = (int*)malloc(2 * sizeof(int));
	}

	for (n = 0; n < classCnt; n++)
	{
		totalScore = 0; //��������� ���� �ݸ��� ������� �ϱ⶧���� �Ѱ��� ���� ó���Ҷ� ���� �ʱ�ȭ�� ���ش�
		for (m = 0; m < StudentsPerClass; m++)
		{
			pStudentScore[n][m] = rand() % 46 + 55; //�����ǰ� 45~100�������� ���� �־��ش�.
			totalScore += pStudentScore[n][m];    //�� �л����� ��������� ����������� �����ش�.
			printf("%d�� %d��° �л��� ������� %1.2f�Դϴ�.\n", n + 1, m + 1, pStudentScore[n][m]);
			
			//1�г� �л��� �ְ����� �л��� ���ϴ� �ڵ�
			if (highAveragePersonal >= pStudentScore[n][m]) //����Ǿ��ִ� ��������� �ְ����� ��������� �л��� ����������� ���ų� ������
			{
				highAveragePersonal = highAveragePersonal; //�ְ����� ��������� �ٲ��� �ʴ´�.
				highStudent[0] = highStudent[0];		  //�ְ����� �л��� �ݵ� �ٲ��� �ʴ´�.
				highStudent[1] = highStudent[1];		  //�ְ����� �л��� ��ȣ�� �ٲ��� �ʴ´�.
			}

			else if (highAveragePersonal < pStudentScore[n][m]) //����Ǿ��ִ� ��������� �ְ����� ��������� �л��� ����������� ������
			{
				highAveragePersonal = pStudentScore[n][m];      //�ְ����� ��������� ������� �л��� ��������� ��ü���ش�.
				highStudent[0] = n + 1; //�ε����� +1�� ���ش�. ��   �ݵ� ������� �л��� ��������� ��ü���ش�.
				highStudent[1] = m + 1; //�ε����� +1�� ���ش�. ��ȣ  ��ȣ�� ������� �л��� ��������� ��ü���ش�.
			}
		}
		averageGrade = totalScore / StudentsPerClass; //�� ���� ��������� ���ϱ� �ѹ��� ��� �л����� ��������� ���� ���� �ѹ��� �л����� �����ش�.  

		//1�г���� ����� ���� ���� ���� ���ϴ� �ڵ�
		if (highAverage >= averageGrade) //����Ǿ��ִ� ��������� �ְ����� ��������� ���� ����������� ���ų� ������
		{
			highAverage = highAverage;   //�ְ����� ��������� �ٲ��� �ʴ´�
			highClass = highClass;		//�ְ����� ����� ������ �ݵ� �ٲ��� �ʴ´�.
		}
		else if (highClass < averageGrade) //����Ǿ��ִ� ��������� �ְ����� ��������� ���� ����������� ������
		{
			highAverage = averageGrade;  //�ְ����� ��������� ���� ���� ����������� ��ü���ش�.
			highClass = n + 1; //�ε����� +1�� ���ش�	�ְ����� ����� ������ �ݵ� ���� ���� ���� ��ȣ�� ��ü���ش�.
		}

		printf("==============================\n");
		printf("%d���� ��������� %1.2f���Դϴ�.\n", n + 1, averageGrade);
		printf("==============================\n");
	}
	printf("1. 1�г� ���� ����� ���� ���� ��\n");
	printf("2. 1�г� �л��� �ְ����� �л�\n");
	printf("==============================\n");
	printf("��ȣ�� �����ϼ��� : ");
	scanf_s(" %d", &select);
	switch (select)
	{
	case 1:
		printf("%d���� %1.2f������ ����� ���� �����ϴ�.\n", highClass, highAverage);
		break;
	case 2:
		printf("%d���� %d��° �л��� %1.2f������ 1�г��� �ְ� ���� �л��Դϴ�.\n", highStudent[0], highStudent[1], highAveragePersonal);
		break;
	}

	//�����Ҵ� ����
	if (highStudent != 0)
	{
		free(highStudent);
	}

	if (pStudentScore != 0)
	{
		for (n = 0; n < classCnt; n++)
		{
			free(pStudentScore[n]);
		}
		free(pStudentScore);
	}
	system("pause");
	return 0;
}