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

	int select = 0; //번호 선택을 위한 변수
	int highClass = 0; //평균점수가 가장 높은 반을 저장하는 변수
	int* highStudent = 0; //평균점수가 가장 높은 학생의 반과 번호를 저장
	float highAverage = 0.0f; //평균점수가 가장 높은 반의 평균저장
	float highAveragePersonal = 0.0f; //평균점수가 가장 높은 학생의 평균저장

	printf("1학년에 몇개의 반이 있습니까 : ");
	scanf_s(" %d", &classCnt);
	printf("한반당 몇명의 학생이 있습니까 : ");
	scanf_s(" %d", &StudentsPerClass);
	printf("==============================\n");
	
	//동적할당
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
		totalScore = 0; //평균점수의 합을 반마다 구해줘야 하기때문에 한개의 반을 처리할때 마다 초기화를 해준다
		for (m = 0; m < StudentsPerClass; m++)
		{
			pStudentScore[n][m] = rand() % 46 + 55; //임의의값 45~100점사이의 값을 넣어준다.
			totalScore += pStudentScore[n][m];    //각 학생들의 평균점수를 총평균점수에 더해준다.
			printf("%d반 %d번째 학생의 평균점수 %1.2f입니다.\n", n + 1, m + 1, pStudentScore[n][m]);
			
			//1학년 학생중 최고점인 학생을 구하는 코드
			if (highAveragePersonal >= pStudentScore[n][m]) //저장되어있는 평균점수의 최고점이 현재저장된 학생의 평균점수보다 높거나 같으면
			{
				highAveragePersonal = highAveragePersonal; //최고점의 평균점수는 바뀌지 않는다.
				highStudent[0] = highStudent[0];		  //최고점의 학생의 반도 바뀌지 않는다.
				highStudent[1] = highStudent[1];		  //최고점의 학생의 번호도 바뀌지 않는다.
			}

			else if (highAveragePersonal < pStudentScore[n][m]) //저장되어있는 평균점수의 최고점이 현재저장된 학생의 평균점수보다 작으면
			{
				highAveragePersonal = pStudentScore[n][m];      //최고점의 평균점수를 현재들어온 학생의 평균점수로 교체해준다.
				highStudent[0] = n + 1; //인덱스상 +1을 해준다. 반   반도 현재들어온 학생의 평균점수로 교체해준다.
				highStudent[1] = m + 1; //인덱스상 +1을 해준다. 번호  번호도 현재들어온 학생의 평균점수로 교체해준다.
			}
		}
		averageGrade = totalScore / StudentsPerClass; //각 반의 평균점수를 구하기 한반의 모든 학생들의 평균점수를 더한 값을 한반의 학생수로 나눠준다.  

		//1학년반중 평균이 제일 높은 반을 구하는 코드
		if (highAverage >= averageGrade) //저장되어있는 평균점수의 최고점이 현재저장된 반의 평균점수보다 높거나 같으면
		{
			highAverage = highAverage;   //최고점의 평균점수는 바뀌지 않는다
			highClass = highClass;		//최고점의 평균을 저장한 반도 바뀌지 않는다.
		}
		else if (highClass < averageGrade) //저장되어있는 평균점수의 최고점이 현재저장된 반의 평균점수보다 낮으면
		{
			highAverage = averageGrade;  //최고점의 평균점수는 현재 들어온 반평균점수로 교체해준다.
			highClass = n + 1; //인덱스상 +1을 해준다	최고점의 평균을 저장한 반도 현재 들어온 반의 번호로 교체해준다.
		}

		printf("==============================\n");
		printf("%d반의 평균점수는 %1.2f점입니다.\n", n + 1, averageGrade);
		printf("==============================\n");
	}
	printf("1. 1학년 반중 평균이 제일 높은 반\n");
	printf("2. 1학년 학생중 최고점인 학생\n");
	printf("==============================\n");
	printf("번호를 선택하세요 : ");
	scanf_s(" %d", &select);
	switch (select)
	{
	case 1:
		printf("%d반이 %1.2f점으로 평균이 제일 높습니다.\n", highClass, highAverage);
		break;
	case 2:
		printf("%d반의 %d번째 학생이 %1.2f점으로 1학년중 최고 점인 학생입니다.\n", highStudent[0], highStudent[1], highAveragePersonal);
		break;
	}

	//동적할당 해지
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
