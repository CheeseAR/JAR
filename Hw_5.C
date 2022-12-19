#include<stdio.h>
#include<Windows.h>

//원하는 학생수만큼의 학생 정보를 구조체에 입력 저장해서 출력 또는 입력한 정보를 수정 하는 프로그램

enum blood //혈액형
{
	A형 = 1,
	B형,
	O형,
	AB형
};

typedef struct Student //학생구조체
{
	char name[20];
	int number;
	enum blood Myblood;
	float height;
	float weight;

}_STUDENT, * _LPSTUDENT;

//함수선언부
int GetInputInt(const char* dialog, int no);
float GetInputFloat(const char* dialog, int no);
void ShowStudentInfo(struct Student person);

int main()
{
	int inwon = 0; //몇명의 정보를 입력할것인지 저장하는 변수
	_LPSTUDENT pStudent = { 0, };
	int n = 0;
	int choiceInfo = 0;		//어떤 학생의 정보를 출력또는 수정할것인지 선택하는 변수
	int choiceNumber = 0;	//정보를 출력할것인지 수정할것인지 빠져 나갈것인지 선택하는 변수

	printf("몇명의 학생정보를 입력하시겠습니까 : ");
	scanf_s(" %d", &inwon);
	printf("%d명의 학생정보를 입력하겠습니다.\n", inwon);

	if (pStudent == 0) //구조체포인터를 학생의 인원수만큼 동적할당해준다.
	{
		pStudent = (_LPSTUDENT)malloc(inwon * sizeof(_STUDENT));
	}
	for (n = 0; n < inwon; n++)
	{
		printf("===============================\n");
		printf("%d번째 학생의 이름을 입력하세요: ", n + 1);
		scanf_s(" %s", pStudent[n].name, sizeof(pStudent[n].name));
		pStudent[n].number = GetInputInt("%d번째 학생의 학번을 입력하세요: ", n + 1);
		pStudent[n].height = GetInputFloat("%d번째 학생의 키를 입력하세요: ", n + 1);
		pStudent[n].weight = GetInputFloat("%d번째 학생의 몸무게를 입력하세요: ", n + 1);
		printf("1. A형	2.B형	3.O형	4.AB형\n");
		pStudent[n].Myblood = GetInputInt("%d번째 학생의 혈액형을 입력하세요: ", n + 1);
	}
	printf("===============================\n");
	printf("입력이 끝났습니다.\n");
	printf("===============================\n");
	do {
		printf("1. 정보 출력\n");
		printf("2. 정보 수정\n");
		printf("3. 나가기\n");
		printf("번호를 선택하세요: ");
		scanf_s(" %d", &choiceNumber);
		if (choiceNumber == 3) //3. 나가기를 선택 한다면 반복문을 바로 빠져나갈수 있게 해준다.
		{
			return 0;
		}
		printf("===============================\n");
		for (n = 0; n < inwon; n++)
		{
			printf("%d번 %s\n", n + 1, pStudent[n]);
		}
		printf("===============================\n");

		if (choiceNumber == 1)
		{
			printf("누구의 정보를 보시겠습니까 : ");
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

			printf("누구의 정보를 수정하시겠습니까 : ");
			scanf_s(" %d", &choiceInfo);
			for (n = 0; n < inwon; n++)
			{
				if (n + 1 == choiceInfo)
				{
					printf("%d번 %s학생의 정보를 수정합니다.\n", n + 1, pStudent[n].name);
					printf("수정할 %d번 학생의 이름을 입력해주세요 : ", n + 1);
					scanf_s(" %s", pStudent[n].name, sizeof(pStudent[n].name));
					pStudent[n].number = GetInputInt("수정할 %d번 학생의 학번을 입력하세요 : ", n + 1);
					pStudent[n].height = GetInputFloat("수정할 %d번 학생의 키를 입력하세요 : ", n + 1);
					pStudent[n].weight = GetInputFloat("수정할 %d번 학생의 몸무게를 입력하세요 : ", n + 1);
					printf("1. A형	2.B형	3.O형	4.AB형\n");
					pStudent[n].Myblood = GetInputInt("수정할 %d번 학생의 혈액형을 입력하세요: ", n + 1);
				}
			}
		}
	} while (choiceNumber != 3); //3번 나가기를 입력하지 않을 동안 반복해준다.

	if (pStudent != 0)
	{
		free(pStudent);
	}

	system("pause");
	return 0;
}

//함수정의부
void ShowStudentInfo(struct Student person) //정보를 출력해주는 함수
{
	float BMI;
	printf("===============================\n");
	printf("[%s]학생 정보\n", person.name);
	printf("===============================\n");
	printf("%d학번 ", person.number);
	switch (person.Myblood)
	{
	case 1:
		printf("A형의 학생입니다.\n");
		break;
	case 2:
		printf("B형의 학생입니다.\n");
		break;
	case 3:
		printf("O형의 학생입니다.\n");
		break;
	case 4:
		printf("AB형의 학생입니다.\n");
		break;
	}
	person.height = person.height * 0.01;
	BMI = person.weight / (person.height * person.height);
	person.height = person.height * 100;
	printf("키 %1.1fCm,몸무게 %1.1fKg의 bmi수치%1.1f입니다.\n", person.height, person.weight, BMI);
	printf("===============================\n");
}
int GetInputInt(const char* dialog, int no) //int값을 입력받아서 저장해주는 함수
{
	int input;
	printf(dialog, no);
	scanf_s(" %d", &input);
	return input;
}

float GetInputFloat(const char* dialog, int no)	//float값을 입력받아서 저장해주는 함수
{
	float input;
	printf(dialog, no);
	scanf_s(" %f", &input);
	return input;
}
