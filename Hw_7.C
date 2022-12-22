#include<stdio.h>
#include<Windows.h>
#include<time.h>

enum MonsterType	// 몬스터의 타입설정
{
	동물 = 0,
	노바족,
	설인,
	정체불명
};

enum Rare			// 몬스터의 희귀도설정
{
	일반 = 0,
	희귀,
	정예,
	보스
};

enum CharacterType		// 캐릭터의 타입설정
{
	인간 = 1,
	엘프족,
	레프족,
	아니마족
};

enum CharacterJob		// 캐릭터의 직업설정
{
	전사 = 1,
	마법사,
	궁수
};

typedef struct Base			// 캐릭터와 몬스터의 공통적으로 들어가는 BASE구조체
{
	char name[20];
	int att;
	int def;
	int HP;
}_BASE, * _LPBASE;

typedef struct Monster			// 몬스터의 구조체
{
	enum MonsterType MyType;
	char Rare[10];
	enum Rare MyRare;
	_LPBASE base;
	struct Monster* prev;
	struct Monster* next;
}_MONSTER, * _LPMONSTER;

typedef struct Character		// 캐릭터의 구조체
{
	enum CharacterType MyType;
	enum CharacterJob MyJob;
	_BASE base;
}_CHARACTER, * _LPCHARACTER;

//함수 선언부
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

	//플레이어의 정보를 직접 입력받는다.

	printf("플레이어의 이름을 입력하세요 : ");
	scanf_s(" %s", player.base.name, sizeof(player.base.name));
	printf("1.인간  2.엘프족  3.레프족  4.아니마족\n");
	player.MyType = GetInputInt("플레이어의 종족을 골라주세요 : ");
	printf("1.전사  2.마법사  3.궁수\n");
	player.MyJob = GetInputInt("플레이어의 직업을 골라주세요 : ");
	player.base.att = GetInputInt("공격력을 입력하세요 : ");
	player.base.def = GetInputInt("방어력을 입력하세요 : ");
	player.base.HP = GetInputInt("HP(체력)을 입력하세요 : ");

	for (n = 0; n < 4; n++)		//몬스터 구조체에서 BASE구조체를 포인터참조를 하고 있기 때문에 동적할당을 해준다.
	{
		mon[n].base = (_LPBASE)malloc(sizeof(_BASE));
	}
	// 몬스터들의 정보를 입력해준다.

	strcpy_s(mon[0].base->name, sizeof(mon[0].base->name), "리본돼지");
	strcpy_s(mon[1].base->name, sizeof(mon[1].base->name), "예티");
	strcpy_s(mon[2].base->name, sizeof(mon[2].base->name), "핑크빈");
	strcpy_s(mon[3].base->name, sizeof(mon[3].base->name), "매그너스");

	mon[0].MyType = 동물;
	mon[1].MyType = 설인;
	mon[2].MyType = 정체불명;
	mon[3].MyType = 노바족;

	mon[0].MyRare = 일반;
	mon[1].MyRare = 희귀;
	mon[2].MyRare = 정예;
	mon[3].MyRare = 보스;

	mon[0].base->att = rand() % 61 + 20;	//일반몬스터의 공격력은 20~80중 랜덤한 값으로 넣어준다.
	mon[1].base->att = rand() % 61 + 90;	//희귀몬스터의 공격력은 90~150중 랜덤한 값을 넣어준다.
	mon[2].base->att = rand() % 121 + 200;	//정예몬스터의 공격력은 200~320중 랜덤한 값을 넣어준다.
	mon[3].base->att = rand() % 151 + 350;	//보스몬스터의 공격력은 350~500중 랜덤한 값을 넣어준다.

	mon[0].base->def = rand() % 31 + 20;	//일반몬스터의 방어력은 20~50중 랜덤한 값으로 넣어준다.
	mon[1].base->def = rand() % 61 + 60;	//희귀몬스터의 방어력은 60~120중 랜덤한 값으로 넣어준다.
	mon[2].base->def = rand() % 91 + 130;	//정예몬스터의 방어력은 130~220중 랜덤한 값으로 넣어준다.
	mon[3].base->def = rand() % 121 + 230;	//보스몬스터의 방어력은 230~350중 랜덤한 값으로 넣어준다.

	mon[0].base->HP = rand() % 51 + 50;		//일반몬스터의 HP는 50~100중 랜덤한 값으로 넣어준다.
	mon[1].base->HP = rand() % 101 + 100;	//희귀몬스터의 HP는 100~200중 랜덤한 값으로 넣어준다.
	mon[2].base->HP = rand() % 151 + 200;	//정예몬스터의 HP는 200~350중 랜덤한 값으로 넣어준다.
	mon[3].base->HP = rand() % 151 + 350;	//보스몬스터의 HP는 350~500중 랜덤한 값으로 넣어준다.

	//일반-희귀-정예-보스 몬스터 순서로 연결시켜준다.
	mon[0].prev = 0;
	mon[0].next = &mon[1];
	mon[1].prev = &mon[0];
	mon[1].next = &mon[2];
	mon[2].prev = &mon[1];
	mon[2].next = &mon[3];
	mon[3].prev = &mon[2];
	mon[3].next = 0;

	//보스몬스터부터 차례대로 잘 연결이 되었는지 보여준다.
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

	//pMon에 제일 처음 순서인 일반몬스터를 넣어주어서 내가 만든 캐릭터와 몬스터들의 전투를 시작한다.
	pMon = &mon[0];

	Attack(pMon, player);

	if (mon[n].base != 0)			//동적할당해지
	{
		for (n = 0; n < 4; n++)		
		{
			free(mon[n].base);
		}
	}

	system("pause");
	return 0;
}

//함수정의부
int GetInputInt(const char* dialog) // int값을 입력해서 저장하기 위한 함수
{
	int input;
	printf(dialog);
	scanf_s(" %d", &input);
	return input;
}

void MonRareOutput(_LPMONSTER pMon)		
//몬스터의 희귀도가 열거형으로 저장되어 숫자로 취급이 되어있는 데 각각의 몬스터가 무슨 타입인지 한글로 출력해주려고 만든 함수
{
	if (pMon->MyRare == 0)
	{
		strcpy_s(pMon->Rare, sizeof(pMon->Rare), "일반");
	}
	else if (pMon->MyRare == 1)
	{
		strcpy_s(pMon->Rare, sizeof(pMon->Rare), "희귀");
	}
	else if (pMon->MyRare == 2)
	{
		strcpy_s(pMon->Rare, sizeof(pMon->Rare), "정예");
	}
	else if (pMon->MyRare == 3)
	{
		strcpy_s(pMon->Rare, sizeof(pMon->Rare), "보스");
	}
	return;
}

void Attack(_LPMONSTER pMon, _CHARACTER Player)			//전투함수
{
	int whoAttack = 0;			//누가 공격을 할것인지 정해주기 위해 만든 변수
	int att = 0;				//얼마만큼의 공격을 해서 피해를 줄것인지 공격값을 저장하는 함수
	int isStart = 0;			//전투를 할것인지 묻기 위해 만든 변수

	//현재 몬스터의 정보를 출력해준다.
	printf("=====================현재 Monster의 정보=====================\n");
	printf("%s타입\n이름: %s, 공격력: %d, 방어력: %d, HP(체력): %d\n", pMon->Rare, pMon->base->name, pMon->base->att, pMon->base->def, pMon->base->HP);
	printf("============================================================\n");
	printf("%s타입의 Monster %s와 전투를 시작합니다.\n", pMon->Rare, pMon->base->name);
	printf("전투를 시작할까요?(0:예,1:아니요) : ");
	scanf_s(" %d", &isStart);
	if (isStart == 0)   // 0을 입력하면 전투가 시작되고 현재몬스터와 내캐릭터중 하나가 이길때까지 전투가 진행된다.
	{
		while (pMon->base->HP >= 0)							
		{
			whoAttack = rand() % 2;							//랜덤한 값을 0~1중 하나의 값으로 지정해준다.
			if (whoAttack == 0)								//0이 지정이 된다면 캐릭터의 공격이 된다.
			{
				att = rand() % 71 + 30;						//공격값은 30~100사이의 랜덤한 값으로 지정해준다.
				pMon->base->HP = pMon->base->HP - att;		//몬스터의 HP는 현재HP에서 공격값을 빼준 값이 들어가게 된다.

				printf("(Monster)%s의 HP는 %d가 되었습니다.\n", pMon->base->name, pMon->base->HP);

				if (pMon->base->HP <= 0)					//몬스터의 HP가 0보다 작거나 같으면
				{
					printf("%s타입의 %s를 무찔렀습니다!!\n\n", pMon->Rare, pMon->base->name);		//몬스터를 처치했다는 메시지를 출력해준다.
					if (pMon->next == 0)					//만약 몬스터의 next가 0(마지막 보스몬스터) 까지 처치 했다면 
					{
						printf("\n\t♣Victory~!!♧\n\n\n");		//victory문구를 출력해주고 반복문을 끝내준다.
						break;
					}
				}
			}
			else if (whoAttack == 1)						//1이 지정이 된다면 몬스터의 공격이 된다.
			{
				//몬스터는 희귀도에 따라 공격력을 다르게 계산해준다.
				if (pMon->MyType == 일반)
				{
					att = rand() % +41 + 10;			//일반몬스터 : 10~50
				}
				else if (pMon->MyType == 희귀)
				{
					att = rand() % 51 + 50;				//희귀몬스터 : 50~100
				}
				else if (pMon->MyType == 정예)
				{
					att = rand() % 51 + 100;			//정예몬스터 : 100~150
				}
				else if (pMon->MyType == 보스)
				{
					att = rand() % 51 + 150;			//보스몬스터 : 150~200
				}

				Player.base.HP = Player.base.HP - att;		//캐릭터의 HP는 현재HP에서 공격값을 빼준 값이 들어가게 된다.

				printf("(Player) %s의 HP는 %d가 되었습니다.\n", Player.base.name, Player.base.HP);
				if (Player.base.HP <= 0)					//캐릭터의 HP가 0보다 작거나 같아져서 캐릭터가 몬스터에게 졌을 경우
				{
					printf("player %s가 Monster %s에게 졌습니다!\n", Player.base.name,pMon->base->name);		//메시지를 출력해준뒤
					printf("\n\tLOSS!\n\n");
					break;												   //반복문을 빠져나온다.
				}

			}
		}

		//위의 반복문이 몬스터의 HP가 0보다 크거나 같을경우 반복되는 것이니까 0보다 작아졌을 때 위의 반복이 끝나고,
		//여기를 실행해준다. 내가만든 캐릭터가 졌을경우에는 위에 따로 반복을 나가는 break문을 적어두었다.

		if (pMon->base->HP <= 0)			//현재 몬스터의 HP가 0보다 작거나 같다면
		{
			if (pMon->next != 0)			//몬스터의 next값이 0이 아니라면(보스몬스터만 next가 0) 
			{
				Attack(pMon->next, Player);		//현재몬스터의 next몬스터를 넣어서 재귀함수를 실행시켜준다. 	
			}
		}
	}
	else if (isStart == 1) //전투를 하지 않겠다고 1을 입력할시 전투가 강제 종료된다.
	{
		printf("============================================================\n\n");
		printf("\t\t전투가 종료되었습니다.\n");
		printf("\n============================================================\n");
		return;
	}

}