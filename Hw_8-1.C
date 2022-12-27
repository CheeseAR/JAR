#include<stdio.h>

enum subject
{
	���� = 0,
	����,
	����,
	�����
};

typedef struct studentInfo		//�л������� ����ü�� �����Ѵ�.
{
	char name[20];
	int class;
	int number;
	enum subject score[3];

}_STUDENTINFO, * _LPSTUDENTINFO;

int main()
{
	FILE* pf = 0;
	fopen_s(&pf, "Data\\studentInfo.txt", "rt+");  //rt�� �б����������� �ڿ� "+"�� ������ �б�,���� ��� �����ϴ�.
	int cnt = 0;
	int n = 0;
	int choiceNumber = 0;
	_STUDENTINFO student[10];				//�л�����ü�� ����� �迭�� ������ش�.

			//������ �ԷµǾ� �ִ� ������ �����Ѵٸ�
	if (pf != 0)					
	{
		while (feof(pf) == 0)
		{
			fscanf_s(pf, "%d", &cnt);		//�Ǿ��� �Ǿ�ĭ�� �л����� �޾ƿͼ� cnt�� �������ش�.
			for (n = 0; n < cnt; n++)		//cnt��ŭ �ݺ����ش�.
			{
				fscanf_s(pf, "%s", student[n].name, sizeof(student[n].name));   //���Ͽ� �ԷµǾ��ִ� ���� �л��� �迭�� �޾ƿ´�.
				fscanf_s(pf, "%d", &student[n].class);
				fscanf_s(pf, "%d", &student[n].number);
				fscanf_s(pf, "%d", &student[n].score[����]);
				fscanf_s(pf, "%d", &student[n].score[����]);
				fscanf_s(pf, "%d", &student[n].score[����]);
			}
		}
	}
	while (1)
	{

		printf("1.�����Է�\n2.�������\n9.����\n");
		printf("��ȣ�� �Է��ϼ���: ");
		scanf_s(" %d", &choiceNumber);

		if (choiceNumber == 1)							//1 �����Է��� �����ϸ� ������ �ִ� ���� �ڿ� ���� �Էµȴ�.
		{
			printf("�̸��� �Է��ϼ���: ");
			scanf_s("%s", student[cnt].name, sizeof(student[cnt].name));		//������ �Է¹ް�
			fprintf(pf, "%s  ", student[cnt].name);								//���Ͽ��� ������ �Է����ش�.
			printf("���� �Է��ϼ���: ");
			scanf_s("%d", &student[cnt].class);
			fprintf(pf, "%d  ", student[cnt].class);
			printf("��ȣ�� �Է��ϼ���: ");
			scanf_s("%d", &student[cnt].number);
			fprintf(pf, "%d  ", student[cnt].number);
			printf("���������� �Է��ϼ���: ");
			scanf_s("%d", &student[cnt].score[����]);
			fprintf(pf, "%d  ", student[cnt].score[����]);
			printf("���������� �Է��ϼ���: ");
			scanf_s("%d", &student[cnt].score[����]);
			fprintf(pf, "%d  ", student[cnt].score[����]);
			printf("���������� �Է��ϼ���: ");
			scanf_s("%d", &student[cnt].score[����]);
			fprintf(pf, "%d\n", student[cnt].score[����]);
			cnt++;			//���Է����ص� cnt(�л���)�� 1���������ش�.
		}
		else if (choiceNumber == 2)		//2 ��������� �����ϸ�
		{
			if (pf == 0)				//���� ������ ����� ���� ���� ���ٸ�
			{
				printf("\n-----------------------\n");
				printf("\n������ ���� �Է��ϼ���\n");				//������ ���� �Է��϶�� �޽����� �Բ�
				printf("\n-----------------------\n\n");	
				fopen_s(&pf, "Data\\studentInfo.txt", "wt+");	//������ ���� ������ش�.
				fprintf(pf, "\n");								//������ ���� ����ٸ� ������ �л����� �ԷµǾ�� �ϹǷ� ��ĭ�� ����ش�.
			}

			else					//������ �ԷµǾ��ִٸ� ���ݱ��� �ԷµǾ��ִ� ������ ������ش�.
			{

				for (n = 0; n < cnt; n++)
				{
					printf("===========================================\n");
					printf("%d��° �л��� ����\n", n + 1);
					printf("�̸�: %s\n", student[n].name);
					printf("��: %d\n", student[n].class);
					printf("��ȣ: %d\n", student[n].number);
					printf("��������: %d  ", student[n].score[����]);
					printf("��������: %d  ", student[n].score[����]);
					printf("��������: %d\n", student[n].score[����]);
					if (n == cnt - 1)
					{
						printf("===========================================\n");
					}
				}

			}
		}

		else if (choiceNumber == 9)				//9 ���Ḧ �����Ѵٸ�
		{
			fseek(pf, 0, SEEK_SET);				//�Ǿ��� �Ǿ�ĭ���� �̵��ؼ�
			fprintf(pf, "%d", cnt);				//���ο� �л����� �Է����ش�. ���ο� �л����� �Է��� �Ǹ� ������ ���� �ڸ��� �ִ� �л����� ������� �ȴ�.
			fclose(pf);							//������ �������� ������ �ݾ��ش�.
			return 0;							//���α׷��� �������ش�.
		}
	}

}