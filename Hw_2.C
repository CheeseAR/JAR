#include<stdio.h>
#include<Windows.h>
#include<time.h>


int main()
{
	srand(time(0));
	int subjectCnt = 3; //����,����,����
	int** scores[6] = { 0, };
	int studentCnt[6];
	int selectClass = 0;
	int n = 0, m = 0, l = 0;

	for (n = 0; n < 6; n++) //studentCnt[6] : 6���� �ݿ� ������ �л��� 5~10������ ������ ���� �־��ش�.
	{
		studentCnt[n] = rand() % 6 + 5;
	}

	for (n = 0; n < 6; n++) //�����Ҵ��� ���ش�.
	{
		scores[n] = (int**)malloc(studentCnt[n] * sizeof(int*));
		for (m = 0; m < studentCnt[n]; m++)
		{
			scores[n][m] = (int*)malloc(subjectCnt * sizeof(int));
		}
	}

	for (n = 0; n < 6; n++)
	{
		for (m = 0; m < studentCnt[n]; m++)
		{
			for (l = 0; l < subjectCnt; l++)
			{
				scores[n][m][l] = rand() % 54 + 47;
				//6�ݿ� ������ �л�����(5~10)�� �ְ� �� �л����� ����,����,���� ������ 47~100������ ������ ������ �־��ش�.
			}
		}
	}

	for (n = 0; n < 6; n++) //5-10������ ���� �� ���� Ȯ�� ���ش�.
	{
		printf("%d\t", studentCnt[n]);
	}

	printf("\n����� �л��� ������ ���ðڽ��ϱ�?(1-6):");
	scanf_s(" %d", &selectClass);

	printf("%d���� %d���� �л��� �ֽ��ϴ�.\n", selectClass, studentCnt[selectClass - 1]);//�ε����� �ϳ� �۱� ������ �����Ѱ��� ���� �ַ���-1�� ���ش�. 

	for (n = 0; n < 6; n++)
	{
		if (n == selectClass - 1)
		{
			for (m = 0; m < studentCnt[selectClass - 1]; m++)
			{
				printf("%d�� �л��� ���� ���� : %d\n", m + 1, scores[n][m][0]);
				printf("%d�� �л��� ���� ���� : %d\n", m + 1, scores[n][m][1]);
				printf("%d�� �л��� ���� ���� : %d\n", m + 1, scores[n][m][2]);
				printf("=======================\n");
			}
		}
	}

	//�����Ҵ�����
	if (scores[6] != 0)
	{
		for (n = 0; n < 6; n++)
		{
			for (m = 0; m < studentCnt[n]; m++)
			{
				free(scores[n][m]);
			}
			free(scores[n]);
		}
	}

	system("pause");
	return 0;
}