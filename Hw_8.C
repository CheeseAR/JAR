#include<stdio.h>

					// ���Ͽ� ������ �Է��ϰų� �����ϴ� ���α׷�
enum subject
{
	���� = 0,
	����,
	����,
	�����
};

int main()
{
	FILE* pf = 0;
	fopen_s(&pf, "Data\\studentInfo.txt", "wt");	// Data��� �����ȿ� studentInfo��� �ؽ�Ʈ���������� �ؽ�Ʈ ���� �������� �����ش�. 

	int cnt = 0;
	int choiceNumber = 0;		// ������ �Է��Ұ����� �����Ұ����� �����ϴ� ����
	char name[20] = { 0, };
	int class = 0;
	int number = 0;
	int score[3] = { 0, };

	while (1)
	{
		printf("\n1.���� �Է�\n9.����\n");
		printf("����: ");
		scanf_s(" %d", &choiceNumber);
		if (choiceNumber == 1)
		{
			cnt++;								// ������ �Է��� �����ϸ� �Էµ� �л��� ���� �ϳ��� �����Ѵ�.
			printf("�̸��� �Է��ϼ���: ");
			scanf_s(" %s", name, sizeof(name));
			if (cnt == 1)
			{
				fprintf(pf, "\n%s  ", name);	// �����ٿ� ����� ������ �Է��ߴ°� ���ڸ� �ۼ��ϱ� ���� ù��° ������ �Է��Ҷ� ������ ����ش�.
			}
			else
			{
				fprintf(pf, "%s  ", name);
			}
			printf("���� �Է��ϼ���: ");
			scanf_s(" %d", &class);				// ������ �޾Ƽ�
			fprintf(pf, "%d  ", class);			// �Է¹��� ������ ���Ͽ��� �Է����ش�.
			printf("��ȣ�� �Է��ϼ���: ");
			scanf_s(" %d", &number);
			fprintf(pf, "%d  ", number);
			printf("���������� �Է��ϼ���: ");
			scanf_s(" %d", &score[����]);
			fprintf(pf, "%d  ", score[����]);
			printf("���������� �Է��ϼ���: ");
			scanf_s(" %d", &score[����]);
			fprintf(pf, "%d  ", score[����]);
			printf("���������� �Է��ϼ���: ");
			scanf_s(" %d", &score[����]);
			fprintf(pf, "%d\n", score[����]);
		}
		else if (choiceNumber == 9)		// ���Ḧ �����Ѵٸ�
		{
			fseek(pf, 0, SEEK_SET);		// ������ �Ǿ�ĭ�� ����� �л������� �ԷµǾ����� ������ش�.
			fprintf(pf, "%d", cnt);
			fclose(pf);					// ������ �����ٸ� �� �ݾ��ش�.
			return 0;
		}
	}
}