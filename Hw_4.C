#include<stdio.h>
#include<Windows.h>
#include<time.h>

int MemorySet(int** arr, int count);

int main()
{
	//���� �Է¹޾Ƽ� �����Ҵ��� ���ִ� �Լ������
	int** arr = 0;
	int count = 0;
	int n = 0;
	printf("��� �����Ҵ� �Ͻðڽ��ϱ�?:");
	scanf_s(" %d", &count);
	printf("���: %d\n", MemorySet(arr, count));
	system("pause");
	return 0;
}

//�Լ�
int MemorySet(int** arr, int count)
{
	arr = 0;
	if (arr == 0) //�����Ҵ�
	{
		arr = (int**)malloc(count * sizeof(int*));
		if (arr != 0) //�����Ҵ��� �ߵǾ��ٸ�
		{
			for (int n = 0; n < count; n++)
			{
				printf("�����Ҵ�� �迭���ּ�(%d):%u\n", n + 1, &arr[n]); //�����Ҵ�� �ּҰ��� ���
			}
			return 1; //�����Ҵ� ������ 1�� �Բ� ���
		}
		else
		{
			return 0; //�����Ҵ� ���н� 0���
		}
	}

	if (arr != 0) //�����Ҵ� ����
	{
		free(arr);
	}
}