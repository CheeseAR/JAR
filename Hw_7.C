#include<stdio.h>
#include<Windows.h>
#include<time.h>

enum MonsterType	// ������ Ÿ�Լ���
{
	���� = 0,
	�����,
	����,
	��ü�Ҹ�
};

enum Rare			// ������ ��͵�����
{
	�Ϲ� = 0,
	���,
	����,
	����
};

enum CharacterType		// ĳ������ Ÿ�Լ���
{
	�ΰ� = 1,
	������,
	������,
	�ƴϸ���
};

enum CharacterJob		// ĳ������ ��������
{
	���� = 1,
	������,
	�ü�
};

typedef struct Base			// ĳ���Ϳ� ������ ���������� ���� BASE����ü
{
	char name[20];
	int att;
	int def;
	int HP;
}_BASE, * _LPBASE;

typedef struct Monster			// ������ ����ü
{
	enum MonsterType MyType;
	char Rare[10];
	enum Rare MyRare;
	_LPBASE base;
	struct Monster* prev;
	struct Monster* next;
}_MONSTER, * _LPMONSTER;

typedef struct Character		// ĳ������ ����ü
{
	enum CharacterType MyType;
	enum CharacterJob MyJob;
	_BASE base;
}_CHARACTER, * _LPCHARACTER;

//�Լ� �����
int GetInputInt(const char* dialog);
void MonRareOutput(_LPMONSTER pMon);
void Attack(_LPMONSTER pMon, _CHARACTER Player);

int main()
{
	rand(time(0));

	_MONSTER mon[4] = { 0, };
	_LPMONSTER pMon = 0;
	_CHARACTER player;

	int n = 0;

	//�÷��̾��� ������ ���� �Է¹޴´�.

	printf("�÷��̾��� �̸��� �Է��ϼ��� : ");
	scanf_s(" %s", player.base.name, sizeof(player.base.name));
	printf("1.�ΰ�  2.������  3.������  4.�ƴϸ���\n");
	player.MyType = GetInputInt("�÷��̾��� ������ ����ּ��� : ");
	printf("1.����  2.������  3.�ü�\n");
	player.MyJob = GetInputInt("�÷��̾��� ������ ����ּ��� : ");
	player.base.att = GetInputInt("���ݷ��� �Է��ϼ��� : ");
	player.base.def = GetInputInt("������ �Է��ϼ��� : ");
	player.base.HP = GetInputInt("HP(ü��)�� �Է��ϼ��� : ");

	for (n = 0; n < 4; n++)		//���� ����ü���� BASE����ü�� ������������ �ϰ� �ֱ� ������ �����Ҵ��� ���ش�.
	{
		mon[n].base = (_LPBASE)malloc(sizeof(_BASE));
	}
	// ���͵��� ������ �Է����ش�.

	strcpy_s(mon[0].base->name, sizeof(mon[0].base->name), "��������");
	strcpy_s(mon[1].base->name, sizeof(mon[1].base->name), "��Ƽ");
	strcpy_s(mon[2].base->name, sizeof(mon[2].base->name), "��ũ��");
	strcpy_s(mon[3].base->name, sizeof(mon[3].base->name), "�ű׳ʽ�");

	mon[0].MyType = ����;
	mon[1].MyType = ����;
	mon[2].MyType = ��ü�Ҹ�;
	mon[3].MyType = �����;

	mon[0].MyRare = �Ϲ�;
	mon[1].MyRare = ���;
	mon[2].MyRare = ����;
	mon[3].MyRare = ����;

	mon[0].base->att = rand() % 61 + 20;	//�Ϲݸ����� ���ݷ��� 20~80�� ������ ������ �־��ش�.
	mon[1].base->att = rand() % 61 + 90;	//��͸����� ���ݷ��� 90~150�� ������ ���� �־��ش�.
	mon[2].base->att = rand() % 121 + 200;	//���������� ���ݷ��� 200~320�� ������ ���� �־��ش�.
	mon[3].base->att = rand() % 151 + 350;	//���������� ���ݷ��� 350~500�� ������ ���� �־��ش�.

	mon[0].base->def = rand() % 31 + 20;	//�Ϲݸ����� ������ 20~50�� ������ ������ �־��ش�.
	mon[1].base->def = rand() % 61 + 60;	//��͸����� ������ 60~120�� ������ ������ �־��ش�.
	mon[2].base->def = rand() % 91 + 130;	//���������� ������ 130~220�� ������ ������ �־��ش�.
	mon[3].base->def = rand() % 121 + 230;	//���������� ������ 230~350�� ������ ������ �־��ش�.

	mon[0].base->HP = rand() % 51 + 50;		//�Ϲݸ����� HP�� 50~100�� ������ ������ �־��ش�.
	mon[1].base->HP = rand() % 101 + 100;	//��͸����� HP�� 100~200�� ������ ������ �־��ش�.
	mon[2].base->HP = rand() % 151 + 200;	//���������� HP�� 200~350�� ������ ������ �־��ش�.
	mon[3].base->HP = rand() % 151 + 350;	//���������� HP�� 350~500�� ������ ������ �־��ش�.

	//�Ϲ�-���-����-���� ���� ������ ��������ش�.
	mon[0].prev = 0;
	mon[0].next = &mon[1];
	mon[1].prev = &mon[0];
	mon[1].next = &mon[2];
	mon[2].prev = &mon[1];
	mon[2].next = &mon[3];
	mon[3].prev = &mon[2];
	mon[3].next = 0;

	//�������ͺ��� ���ʴ�� �� ������ �Ǿ����� �����ش�.
	pMon = &mon[3];

	for (n = 0; n < 4; n++)
	{
		MonRareOutput(pMon);
		if (n != 3)
		{
			printf("(%s)%s - ", pMon->Rare, pMon->base->name);
		}
		else if (n == 3)
		{
			printf("(%s)%s\n", pMon->Rare, pMon->base->name);
		}
		pMon = pMon->prev;
	}

	//pMon�� ���� ó�� ������ �Ϲݸ��͸� �־��־ ���� ���� ĳ���Ϳ� ���͵��� ������ �����Ѵ�.
	pMon = &mon[0];

	Attack(pMon, player);

	if (mon[n].base != 0)			//�����Ҵ�����
	{
		for (n = 0; n < 4; n++)		
		{
			free(mon[n].base);
		}
	}

	system("pause");
	return 0;
}

//�Լ����Ǻ�
int GetInputInt(const char* dialog) // int���� �Է��ؼ� �����ϱ� ���� �Լ�
{
	int input;
	printf(dialog);
	scanf_s(" %d", &input);
	return input;
}

void MonRareOutput(_LPMONSTER pMon)		
//������ ��͵��� ���������� ����Ǿ� ���ڷ� ����� �Ǿ��ִ� �� ������ ���Ͱ� ���� Ÿ������ �ѱ۷� ������ַ��� ���� �Լ�
{
	if (pMon->MyRare == 0)
	{
		strcpy_s(pMon->Rare, sizeof(pMon->Rare), "�Ϲ�");
	}
	else if (pMon->MyRare == 1)
	{
		strcpy_s(pMon->Rare, sizeof(pMon->Rare), "���");
	}
	else if (pMon->MyRare == 2)
	{
		strcpy_s(pMon->Rare, sizeof(pMon->Rare), "����");
	}
	else if (pMon->MyRare == 3)
	{
		strcpy_s(pMon->Rare, sizeof(pMon->Rare), "����");
	}
	return;
}

void Attack(_LPMONSTER pMon, _CHARACTER Player)			//�����Լ�
{
	int whoAttack = 0;			//���� ������ �Ұ����� �����ֱ� ���� ���� ����
	int att = 0;				//�󸶸�ŭ�� ������ �ؼ� ���ظ� �ٰ����� ���ݰ��� �����ϴ� �Լ�
	int isStart = 0;			//������ �Ұ����� ���� ���� ���� ����

	//���� ������ ������ ������ش�.
	printf("=====================���� Monster�� ����=====================\n");
	printf("%sŸ��\n�̸�: %s, ���ݷ�: %d, ����: %d, HP(ü��): %d\n", pMon->Rare, pMon->base->name, pMon->base->att, pMon->base->def, pMon->base->HP);
	printf("============================================================\n");
	printf("%sŸ���� Monster %s�� ������ �����մϴ�.\n", pMon->Rare, pMon->base->name);
	printf("������ �����ұ��?(0:��,1:�ƴϿ�) : ");
	scanf_s(" %d", &isStart);
	if (isStart == 0)   // 0�� �Է��ϸ� ������ ���۵ǰ� ������Ϳ� ��ĳ������ �ϳ��� �̱涧���� ������ ����ȴ�.
	{
		while (pMon->base->HP >= 0)							
		{
			whoAttack = rand() % 2;							//������ ���� 0~1�� �ϳ��� ������ �������ش�.
			if (whoAttack == 0)								//0�� ������ �ȴٸ� ĳ������ ������ �ȴ�.
			{
				att = rand() % 71 + 30;						//���ݰ��� 30~100������ ������ ������ �������ش�.
				pMon->base->HP = pMon->base->HP - att;		//������ HP�� ����HP���� ���ݰ��� ���� ���� ���� �ȴ�.

				printf("(Monster)%s�� HP�� %d�� �Ǿ����ϴ�.\n", pMon->base->name, pMon->base->HP);

				if (pMon->base->HP <= 0)					//������ HP�� 0���� �۰ų� ������
				{
					printf("%sŸ���� %s�� ���񷶽��ϴ�!!\n\n", pMon->Rare, pMon->base->name);		//���͸� óġ�ߴٴ� �޽����� ������ش�.
					if (pMon->next == 0)					//���� ������ next�� 0(������ ��������) ���� óġ �ߴٸ� 
					{
						printf("\n\t��Victory~!!��\n\n\n");		//victory������ ������ְ� �ݺ����� �����ش�.
						break;
					}
				}
			}
			else if (whoAttack == 1)						//1�� ������ �ȴٸ� ������ ������ �ȴ�.
			{
				//���ʹ� ��͵��� ���� ���ݷ��� �ٸ��� ������ش�.
				if (pMon->MyType == �Ϲ�)
				{
					att = rand() % +41 + 10;			//�Ϲݸ��� : 10~50
				}
				else if (pMon->MyType == ���)
				{
					att = rand() % 51 + 50;				//��͸��� : 50~100
				}
				else if (pMon->MyType == ����)
				{
					att = rand() % 51 + 100;			//�������� : 100~150
				}
				else if (pMon->MyType == ����)
				{
					att = rand() % 51 + 150;			//�������� : 150~200
				}

				Player.base.HP = Player.base.HP - att;		//ĳ������ HP�� ����HP���� ���ݰ��� ���� ���� ���� �ȴ�.

				printf("(Player) %s�� HP�� %d�� �Ǿ����ϴ�.\n", Player.base.name, Player.base.HP);
				if (Player.base.HP <= 0)					//ĳ������ HP�� 0���� �۰ų� �������� ĳ���Ͱ� ���Ϳ��� ���� ���
				{
					printf("player %s�� Monster %s���� �����ϴ�!\n", Player.base.name,pMon->base->name);		//�޽����� ������ص�
					printf("\n\tLOSS!\n\n");
					break;												   //�ݺ����� �������´�.
				}

			}
		}

		//���� �ݺ����� ������ HP�� 0���� ũ�ų� ������� �ݺ��Ǵ� ���̴ϱ� 0���� �۾����� �� ���� �ݺ��� ������,
		//���⸦ �������ش�. �������� ĳ���Ͱ� ������쿡�� ���� ���� �ݺ��� ������ break���� ����ξ���.

		if (pMon->base->HP <= 0)			//���� ������ HP�� 0���� �۰ų� ���ٸ�
		{
			if (pMon->next != 0)			//������ next���� 0�� �ƴ϶��(�������͸� next�� 0) 
			{
				Attack(pMon->next, Player);		//��������� next���͸� �־ ����Լ��� ��������ش�. 	
			}
		}
	}
	else if (isStart == 1) //������ ���� �ʰڴٰ� 1�� �Է��ҽ� ������ ���� ����ȴ�.
	{
		printf("============================================================\n\n");
		printf("\t\t������ ����Ǿ����ϴ�.\n");
		printf("\n============================================================\n");
		return;
	}

}