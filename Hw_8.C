#include<stdio.h>

					// 파일에 정보를 입력하거나 종료하는 프로그램
enum subject
{
	국어 = 0,
	영어,
	수학,
	과목수
};

int main()
{
	FILE* pf = 0;
	fopen_s(&pf, "Data\\studentInfo.txt", "wt");	// Data라는 폴더안에 studentInfo라는 텍스트문서파일을 텍스트 쓰기 전용으로 열어준다. 

	int cnt = 0;
	int choiceNumber = 0;		// 정보를 입력할것인지 종료할것인지 선택하는 변수
	char name[20] = { 0, };
	int class = 0;
	int number = 0;
	int score[3] = { 0, };

	while (1)
	{
		printf("\n1.정보 입력\n9.종료\n");
		printf("선택: ");
		scanf_s(" %d", &choiceNumber);
		if (choiceNumber == 1)
		{
			cnt++;								// 정보를 입력을 선택하면 입력된 학생의 수가 하나씩 증가한다.
			printf("이름을 입력하세요: ");
			scanf_s(" %s", name, sizeof(name));
			if (cnt == 1)
			{
				fprintf(pf, "\n%s  ", name);	// 맨윗줄에 몇명의 정보를 입력했는가 숫자를 작성하기 위해 첫번째 정보를 입력할때 한줄을 띄워준다.
			}
			else
			{
				fprintf(pf, "%s  ", name);
			}
			printf("반을 입력하세요: ");
			scanf_s(" %d", &class);				// 정보를 받아서
			fprintf(pf, "%d  ", class);			// 입력받은 정보를 파일에도 입력해준다.
			printf("번호를 입력하세요: ");
			scanf_s(" %d", &number);
			fprintf(pf, "%d  ", number);
			printf("국어점수를 입력하세요: ");
			scanf_s(" %d", &score[국어]);
			fprintf(pf, "%d  ", score[국어]);
			printf("영어점수를 입력하세요: ");
			scanf_s(" %d", &score[영어]);
			fprintf(pf, "%d  ", score[영어]);
			printf("수학점수를 입력하세요: ");
			scanf_s(" %d", &score[수학]);
			fprintf(pf, "%d\n", score[수학]);
		}
		else if (choiceNumber == 9)		// 종료를 선택한다면
		{
			fseek(pf, 0, SEEK_SET);		// 맨윗줄 맨앞칸에 몇명의 학생정보가 입력되었는지 출력해준다.
			fprintf(pf, "%d", cnt);
			fclose(pf);					// 파일을 열었다면 꼭 닫아준다.
			return 0;
		}
	}
}