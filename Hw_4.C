#include<stdio.h>
#include<Windows.h>
#include<time.h>

int MemorySet(int** arr, int count);

int main()
{
	//값을 입력받아서 동적할당을 해주는 함수만들기
	int** arr = 0;
	int count = 0;
	int n = 0;
	printf("몇개를 동적할당 하시겠습니까?:");
	scanf_s(" %d", &count);
	printf("결과: %d\n", MemorySet(arr, count));
	system("pause");
	return 0;
}

//함수
int MemorySet(int** arr, int count)
{
	arr = 0;
	if (arr == 0) //동적할당
	{
		arr = (int**)malloc(count * sizeof(int*));
		if (arr != 0) //동적할당이 잘되었다면
		{
			for (int n = 0; n < count; n++)
			{
				printf("동적할당된 주소(%d):%u\n", n + 1, &arr[n]); //동적할당된 주소값을 출력
			}
			return 1; //동적할당 성공시 1도 함께 출력
		}
		else
		{
			return 0; //동적할당 실패시 0출력
		}
	}

	if (arr != 0) //동적할당 해지
	{
		free(arr);
	}
}