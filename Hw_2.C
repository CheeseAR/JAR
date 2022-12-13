#include<stdio.h>
#include<Windows.h>
#include<time.h>


int main()
{
	srand(time(0));
	int subjectCnt = 3; //국어,영어,수학
	int** scores[6] = { 0, };
	int studentCnt[6];
	int selectClass = 0;
	int n = 0, m = 0, l = 0;

	for (n = 0; n < 6; n++) //studentCnt[6] : 6개의 반에 임의의 학생수 5~10사이의 임의의 값을 넣어준다.
	{
		studentCnt[n] = rand() % 6 + 5;
	}

	for (n = 0; n < 6; n++) //동적할당을 해준다.
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
				//6반에 임의의 학생명수(5~10)가 있고 그 학생들의 국어,영어,수학 점수를 47~100사이의 랜덤한 값으로 넣어준다.
			}
		}
	}

	for (n = 0; n < 6; n++) //5-10사이의 값이 잘 들어갔나 확인 해준다.
	{
		printf("%d\t", studentCnt[n]);
	}

	printf("\n몇반의 학생들 점수를 보시겠습니까?(1-6):");
	scanf_s(" %d", &selectClass);

	printf("%d반은 %d명의 학생이 있습니다.\n", selectClass, studentCnt[selectClass - 1]);//인덱스가 하나 작기 때문에 선택한값에 맞춰 주려면-1을 해준다. 

	for (n = 0; n < 6; n++)
	{
		if (n == selectClass - 1)
		{
			for (m = 0; m < studentCnt[selectClass - 1]; m++)
			{
				printf("%d번 학생의 국어 점수 : %d\n", m + 1, scores[n][m][0]);
				printf("%d번 학생의 영어 점수 : %d\n", m + 1, scores[n][m][1]);
				printf("%d번 학생의 수학 점수 : %d\n", m + 1, scores[n][m][2]);
				printf("=======================\n");
			}
		}
	}

	//동적할당해지
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