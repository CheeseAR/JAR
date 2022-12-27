#include<stdio.h>

enum subject
{
	국어 = 0,
	영어,
	수학,
	과목수
};

typedef struct studentInfo		//학생정보의 구조체를 선언한다.
{
	char name[20];
	int class;
	int number;
	enum subject score[3];

}_STUDENTINFO, * _LPSTUDENTINFO;

int main()
{
	FILE* pf = 0;
	fopen_s(&pf, "Data\\studentInfo.txt", "rt+");  //rt는 읽기전용이지만 뒤에 "+"가 붙으면 읽기,쓰기 모두 가능하다.
	int cnt = 0;
	int n = 0;
	int choiceNumber = 0;
	_STUDENTINFO student[10];				//학생구조체에 연결된 배열을 만들어준다.

			//기존에 입력되어 있는 파일이 존재한다면
	if (pf != 0)					
	{
		while (feof(pf) == 0)
		{
			fscanf_s(pf, "%d", &cnt);		//맨앞줄 맨앞칸의 학생수를 받아와서 cnt에 저장해준다.
			for (n = 0; n < cnt; n++)		//cnt만큼 반복해준다.
			{
				fscanf_s(pf, "%s", student[n].name, sizeof(student[n].name));   //파일에 입력되어있는 값을 학생의 배열에 받아온다.
				fscanf_s(pf, "%d", &student[n].class);
				fscanf_s(pf, "%d", &student[n].number);
				fscanf_s(pf, "%d", &student[n].score[국어]);
				fscanf_s(pf, "%d", &student[n].score[영어]);
				fscanf_s(pf, "%d", &student[n].score[수학]);
			}
		}
	}
	while (1)
	{

		printf("1.정보입력\n2.정보출력\n9.종료\n");
		printf("번호를 입력하세요: ");
		scanf_s(" %d", &choiceNumber);

		if (choiceNumber == 1)							//1 정보입력을 선택하면 기존에 있던 정보 뒤에 값이 입력된다.
		{
			printf("이름을 입력하세요: ");
			scanf_s("%s", student[cnt].name, sizeof(student[cnt].name));		//정보를 입력받고
			fprintf(pf, "%s  ", student[cnt].name);								//파일에도 정보를 입력해준다.
			printf("반을 입력하세요: ");
			scanf_s("%d", &student[cnt].class);
			fprintf(pf, "%d  ", student[cnt].class);
			printf("번호를 입력하세요: ");
			scanf_s("%d", &student[cnt].number);
			fprintf(pf, "%d  ", student[cnt].number);
			printf("국어점수를 입력하세요: ");
			scanf_s("%d", &student[cnt].score[국어]);
			fprintf(pf, "%d  ", student[cnt].score[국어]);
			printf("영어점수를 입력하세요: ");
			scanf_s("%d", &student[cnt].score[영어]);
			fprintf(pf, "%d  ", student[cnt].score[영어]);
			printf("수학점수를 입력하세요: ");
			scanf_s("%d", &student[cnt].score[수학]);
			fprintf(pf, "%d\n", student[cnt].score[수학]);
			cnt++;			//다입력해준뒤 cnt(학생수)도 1증가시켜준다.
		}
		else if (choiceNumber == 2)		//2 정보출력을 선택하면
		{
			if (pf == 0)				//만약 정보를 출력할 파일 조차 없다면
			{
				printf("\n-----------------------\n");
				printf("\n정보를 먼저 입력하세요\n");				//정보를 먼저 입력하라는 메시지와 함께
				printf("\n-----------------------\n\n");	
				fopen_s(&pf, "Data\\studentInfo.txt", "wt+");	//파일을 새로 만들어준다.
				fprintf(pf, "\n");								//파일을 새로 만든다면 맨위에 학생수가 입력되어야 하므로 한칸을 띄워준다.
			}

			else					//정보가 입력되어있다면 지금까지 입력되어있는 정보를 출력해준다.
			{

				for (n = 0; n < cnt; n++)
				{
					printf("===========================================\n");
					printf("%d번째 학생의 정보\n", n + 1);
					printf("이름: %s\n", student[n].name);
					printf("반: %d\n", student[n].class);
					printf("번호: %d\n", student[n].number);
					printf("국어점수: %d  ", student[n].score[국어]);
					printf("영어점수: %d  ", student[n].score[영어]);
					printf("수학점수: %d\n", student[n].score[수학]);
					if (n == cnt - 1)
					{
						printf("===========================================\n");
					}
				}

			}
		}

		else if (choiceNumber == 9)				//9 종료를 선택한다면
		{
			fseek(pf, 0, SEEK_SET);				//맨앞줄 맨앞칸으로 이동해서
			fprintf(pf, "%d", cnt);				//새로운 학생수를 입력해준다. 새로운 학생수가 입력이 되면 기존에 같은 자리에 있던 학생수는 사라지게 된다.
			fclose(pf);							//파일을 열었으면 파일을 닫아준다.
			return 0;							//프로그램을 종료해준다.
		}
	}

}