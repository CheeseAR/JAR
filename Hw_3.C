#include<stdio.h>
#include<Windows.h>
#include<time.h>

int CalcDate(int month, int day);

int main()
{
	//�Է¹��� �ΰ��� ���� ���̸� �����ִ� �Լ��� �����

	int month = 0;
	int day = 0;
	int totaldate[2] = { 0, }; //�Է¹��� �ΰ��� ���� 365���� ���° ������ �����ϴ� �迭 
	int result = 0;
	int n = 0;
	for (int n = 0; n < 2; n++) //�ΰ��� ���� �Է¹޴´�.
	{
		printf("�Է��ϰ��� �ϴ� ��¥�� �Է��ϼ���(�� ��) : ");
		scanf_s(" %d %d", &month, &day);
		totaldate[n] = CalcDate(month, day);
	}
	if (totaldate[0] > totaldate[1]) //�Է¹��� �ΰ��� ���� �� ū������ ���� ���� ���ش�.
	{
		result = totaldate[0] - totaldate[1];
		printf("�� ��¥�� ���̴� %d�Դϴ�.\n", result);
	}
	else
	{
		result = totaldate[1] - totaldate[0];
		printf("�� ��¥�� ���̴� %d�Դϴ�.\n", result);
	}
	
	system("pause");
	return 0;
}
//�Լ�
int CalcDate(int month, int day)
{
	int n = 0;
	int lastday[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; //12���� ���� ������ ���� ���� ��)1���� 31�ϱ��� 2���� 28�ϱ���,��� ���ϸ� 365
	int totalday = 0;
	if (month == 1) //1���� ���
	{
		return day;	//�Է¹��� ���� ������ �����ش�
	}
	else
	{
		for (n = 0; n < month - 1; n++) //1���� �ƴ� ��� 
		{
			totalday += lastday[n]; //ù��°���� �ϼ����� �ڱ��ڽ��� �ٷ� �� ���� ���� ������ŭ �����ش�

		} //�ε����� �ϳ� �����Ƿ� (n)�ε��������δ� �� ���� �ϼ��� ���������� �ʴ� ������ �ۼ�

		totalday += day; //���� �ϼ��� �� ���������� �ش� ���� �ϼ��� �����ش�.
		return totalday;
	}
}