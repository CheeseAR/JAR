#include<stdio.h>
#include<Windows.h>
#include<time.h>

//학생의 구조체를 만들어서 각각의 정보를 입력하거나 랜덤한 값을 넣어주고 함수를 만들어 함수를 통해 조건에 맞게 출력해주는 프로그램

enum eSubject
{
	국어 = 0,
	영어,
	수학
};

typedef struct arr
{
	enum eSubject score[3]; //국어 영어 수학 점수를 저장하는 배열
	enum eSubject Rank[3];	//각 과목의 석차를 저장하는 배열

}_ARR, * _LPARR;

//구조체
typedef struct Student
{
	char name[20];
	int class;
	int number;
	float averageScore;
	int totalRank;
	_ARR array;
}_STUDENT, * _LPSTUDENT;

//함수선언부
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
	int rank[5] = { 1,1,1,1,1 };  //5명의 학생의 각 순위를 구하기 위해 모든 순위를 1로 저장해준다.
	int InputNumber = 0;		  //어떤 정보를 볼것인지 선택하는 변수
	printf("5명의 학생의 정보를 입력하겠습니다.\n");
	for (n = 0; n < 5; n++)
	{
		pStudent = &student[n];
		//학생의 이름과 반 번호를 입력받는다.
		printf("%d번 학생의 이름을 입력하세요 : ", n + 1);
		scanf_s(" %s", pStudent->name, sizeof(pStudent->name));
		pStudent->class = GetInputInt("%d번 학생의 반을 입력하세요 : ", n + 1);
		pStudent->number = GetInputInt("%d번 학생의 학번을 입력하세요: ", n + 1);
		//국어, 영어, 수학 점수는 45~100점사이의 임의의 값을 저장해준다.

		pStudent->array.score[국어] = rand() % 56 + 45; // 국어점수 저장
		pStudent->array.score[영어] = rand() % 56 + 45; // 영어점수 저장
		pStudent->array.score[수학] = rand() % 56 + 45; // 수학점수 저장
		pStudent->averageScore = (pStudent->array.score[국어] + pStudent->array.score[영어] + pStudent->array.score[수학]) / 3;
		//학생의 (국어,영어,수학)세과목에 대한 평균을 구해준다.
	}
	//전체 순위를 구하기
	for (n = 0; n < 5; n++)
	{
		for (m = 0; m < 5; m++)
		{							//현재 rank[5]는 모두 1로 초기화 되어있다.
			if (student[n].averageScore < student[m].averageScore) // 인덱스가 0번인 학생을 모든 학생과 비교한후 자신의 값보다 큰값이 존재한다면
			{	
				rank[n] = rank[n] + 1;  //자신의 인덱스 rank값(rank[n])을 1씩 증가시켜준다.
			}
		}
	}
	for (n = 0; n < 5; n++)
	{
		student[n].totalRank = rank[n]; //구조체에서 전체순위를 저장하는 값에 방금 구한 순위를 저장해준다.
	}

	RankInput(student, 5, 국어); //국어 순위를 저장해준다.
	RankInput(student, 5, 영어);	//영어 순위를 저장해준다.
	RankInput(student, 5, 수학);	//수학 순위를 저장해준다.
	
	ShowInput(student,5);	//5명의 입력된 정보를 보여준다.
	
	printf("1.전체 등수가 높은 순으로 화면에 출력\n");
	printf("2.국어점수가 높은 순으로 화면에 출력\n");
	printf("3.영어점수가 높은 순으로 화면에 출력\n");
	printf("4.수학점수가 높은 순으로 화면에 출력\n");
	printf("5.다섯명의 평균중 평균이상인 학생만 화면에 출력\n");
	printf("번호를 입력하세요 : ");
	scanf_s(" %d", &InputNumber);

	switch (InputNumber)
	{
	case 1:
		showTotalRank(student, 5);
		break;
	case 2:
		showSubjectRank(student, 5, 국어);
		break;
	case 3:
		showSubjectRank(student, 5, 영어);
		break;
	case 4:
		showSubjectRank(student, 5, 수학);
		break;
	case 5:
		showAverageUp(student, 5);
		break;
	}


	system("pause");
	return 0;
}

//함수정의부
int GetInputInt(const char* dialog, int no) //int값을 입력해서 저장하기 위한 함수
{
	int input;
	printf(dialog, no);
	scanf_s(" %d", &input);
	return input;
}

int RankInput(_LPSTUDENT student, int count, int index) //국어, 영어, 수학의 각 순위를 구하는 함수  
//count값에는 몇개의 배열인지 입력해주고 index에는 국어, 영어, 수학 중 해당하는 인덱스 번호를 입력해준다.
{
	int rank[5] = { 1,1,1,1,1 }; //위의 메인함수에서 구한 전체 순위방법과 동일하게 작성해준다.
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
void ShowInput(_LPSTUDENT student, int count) // 내가 입력한 정보와 랜덤한 값들이 잘 들어갔는 지 확인하기 위해 정보를 보여주기 위한 함수
//count에는 몇개의 배열인지 입력해준다.
{	int n = 0;
	printf("===============================================\n");
	for (n = 0; n < count; n++)
	{
		printf("%d번\n", n + 1);
		printf("이름: %s\n", student[n].name);
		printf("학급: %d반, 학번: %d\n", student[n].class, student[n].number);
		printf("국어: %d점, 영어: %d점, 수학: %d점\n", student[n].array.score[국어], student[n].array.score[영어], student[n].array.score[수학]);
		printf("평균점수 : %1.1f점\n", student[n].averageScore);
		printf("===============================================\n");
	}
	return;
}
void showTotalRank(_LPSTUDENT student, int count)//전체등수를 차례대로 출력해주는 함수
//count에는 몇개의 배열인지 입력해준다.
{
	int n = 0, m = 0;
	for (n = 0; n < count; n++)
	{
		for (m = 0; m < count; m++)
		{
			if (student[m].totalRank == n + 1)
			{
				printf("%d등 %s\n", n + 1, student[m].name);
			}
		}
	}
	return;
}

void showSubjectRank(_LPSTUDENT student, int count, int Index) //각 과목별 등수 순서대로 출력해주는 함수
//count에는 몇개의 배열인지 입력해준다.index에는 국어, 영어, 수학에 해당하는 값을 넣어준다.
{
	int n = 0, m = 0;
	for (n = 0; n < count; n++)
	{
		for (m = 0; m < count; m++)
		{
			if (student[m].array.Rank[Index] == n + 1)
			{
				printf("%d등 %s\n", n + 1, student[m].name);
			}
		}
	}
	return;
}

void showAverageUp(_LPSTUDENT student, int count) //5명의 전체평균의 평균보다 높은 평균을 받은 학생을 출력해주는 함수
//count에는 몇개의 배열인지 입력해준다.
{
	float average = 0.0f;
	int n = 0;
	for (n = 0; n < count; n++)
	{
		average += student[n].averageScore;
	}
	average = average / count;
	printf("%d명의 평균은 %1.1f입니다.\n", count, average);
	printf("===============================================\n");
	printf("평균이상의 학생은 ");
	for (n = 0; n < count; n++)
	{
		if (student[n].averageScore > average)
		{
			printf(" %d번 %s ", n + 1, student[n].name);
		}

	}
	printf("입니다.\n");
	printf("===============================================\n");
	return;
}