#include<stdio.h>
#include<Windows.h>
#include<time.h>

int CalcDate(int month, int day);

int main()
{
	//입력받은 두개의 날의 차이를 구해주는 함수를 만들기

	int month = 0;
	int day = 0;
	int totaldate[2] = { 0, }; //입력받은 두개의 날을 365일중 몇번째 일인지 저장하는 배열 
	int result = 0;
	int n = 0;
	for (int n = 0; n < 2; n++) //두개의 날을 입력받는다.
	{
		printf("입력하고자 하는 날짜를 입력하세요(월 일) : ");
		scanf_s(" %d %d", &month, &day);
		totaldate[n] = CalcDate(month, day);
	}
	if (totaldate[0] > totaldate[1]) //입력받은 두개의 날중 더 큰값에서 작은 값을 빼준다.
	{
		result = totaldate[0] - totaldate[1];
		printf("두 날짜의 차이는 %d입니다.\n", result);
	}
	else
	{
		result = totaldate[1] - totaldate[0];
		printf("두 날짜의 차이는 %d입니다.\n", result);
	}
	
	system("pause");
	return 0;
}
//함수
int CalcDate(int month, int day)
{
	int n = 0;
	int lastday[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; //12개의 월의 각각의 일의 개수 예)1월은 31일까지 2월은 28일까지,모두 더하면 365
	int totalday = 0;
	if (month == 1) //1월인 경우
	{
		return day;	//입력받은 일의 개수만 더해준다
	}
	else
	{
		for (n = 0; n < month - 1; n++) //1월이 아닌 경우 
		{
			totalday += lastday[n]; //첫번째월의 일수부터 자기자신의 바로 전 달의 일의 개수만큼 더해준다

		} //인덱스는 하나 적으므로 (n)인덱스상으로는 전 달의 일수를 포함해주지 않는 것으로 작성

		totalday += day; //월의 일수를 다 더해줬으면 해당 월의 일수를 더해준다.
		return totalday;
	}
}