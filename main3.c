#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include "assert.h"
#include"head3.h"


struct Node
{
	int Element;
	Position Right;
	Position Left;
	int position;
};
int PUBLIC_NumberNodeID = 0;
short PUBLIC_TargetArray[3][3] = { 1,2,3,4,5,6,7,8,0 };//目标矩阵
int PUBLIC_TreeDepth = 0;//搜索深度
int PUBLIC_NumberInputArray[3][3];//
Type_NumberNode  InputNode;
int PUBLIC_IsFinDCorret = 0;  //1:找到，0:没有
char Last;

void main()
{
	
	double duration;
	clock_t start, finish;
	List list, position;
	system("color 0a");
	printf("1.startgame 2.help 3.findpath\n ");
	printf("if you can't find the solution for the problem you can choose 3, we will help you find correct path\n");
	int m;
	scanf_s("%d", &m);
	switch (m)
	{
	case 1:
		system("cls");
		printf("please press 'CapsLock' first!\n");
		printf("please press 'CapsLock' first!\n");
		printf("please press 'CapsLock' first!\n");
		printf("'W' means moving up\n");
		printf("'S' means moving down\n");
		printf("'A' means moving left\n");
		printf("'D' means moving right\n");
		printf("'F' means help you find solution,this is a good fountion!!!\n");
		int k = 3;
		list = Creatmatrix(k);
		start = clock();
		StartGame(list, k);
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		printf("\nTotal time： %f seconds\n", duration);
		printf("\n\n\n");
		system("pause");
      break;
	case 2:
		system("cls");
		help();
		break;
	case 3:
		system("cls");
		while (1)
		{
			Start();
		}
		break;
	default:
		printf("error\n");
		break;
	}
	getchar();
	return 0;
}

void help()
{
	//printf("\nGame Notes: \n1.Before starting game, please press 'CapsLock' first\n2.During the process of the game, effective operation keys are 'W''S''A''D',which are used to realize the movement of the number under,above,on the right side of and on the left of 0 respectively\n");
	printf("'W' means moving up\n");
	printf("'S' means moving down\n");
	printf("'A' means moving left\n");
	printf("'D' means moving right\n");
	printf("'F' means help you find solutions\n");
	printf("If you want to quit the game, please press'Q'\n");
	printf("You win when all the numbers except 0 are placed from left to right,from top to bottom,from smallest to largest,with 0 ending in the bottom right corner");
	
	
}


	

	void  StartGame(List L, int number)
{
	
	char PutIn = 'A';
	int win = 0;
	List P5,P0;//初始 ，中间量
	P5 = Creatmatrix(number);
	Printmatrix(P5, number);
	RandomMove(P5, number *1000, number);
	MoveBack(P5, number);
	Printmatrix(P5, number);
	P0 = P5;
	
	

	 while (!win)
	{
		win = 1;

		if (_kbhit())
		{
			PutIn = _getch();
		}

		switch (PutIn)//控制零的移动并且可选择是否需要搜索帮助
		{
		case 'W':
			Up(P5, number);
			system("cls");
			Printmatrix(P5, number);
			break;
		case 'S':
			Down(P5, number);
			system("cls");
			Printmatrix(P5, number);
			break;
		case 'A':
			Left(P5, number);
			system("cls");
			Printmatrix(P5, number);
			break;
		case 'D':
			Right(P5, number);
			system("cls");
			Printmatrix(P5, number);
			break;
		case'Q':
			exit(0);
		case'F':
			while (1)
			{
				Start();//运用dfs算法找到解决路径，可根据玩家要求步数完成搜索
			}
			break;

			
		}

		PutIn = '\0';

		while (P0->Right != NULL)
		{
			if (P0->Element != P0->position)
				win = 0;

			P0 = P0->Right;
		}

		P0 = P5;

	}

	printf("\nYou win this game!");

}
	List CreatList()
	{
		PtrToNode F_List;
		F_List = malloc(sizeof(struct Node));

		if (F_List == NULL)
		{
			printf("\nOut of place!!");
			Sleep(1000);
			exit(0);
		}
		else
		{
			F_List->Element = 1;
			F_List->Left = NULL;
			F_List->Right = NULL;
			F_List->position = 1;
			return F_List;
		}

	}

	List  Creatmatrix(int number)
	{
		int t = 2;
		PtrToNode Tmp;
		List L = CreatList(), Header;

		Header = L;


		while (t <= number*number)
		{
			Tmp = malloc(sizeof(struct Node));//内存

			if (Tmp == NULL)
			{
				printf("\nOut of place!!");
				Sleep(1000);
				exit(0);
			}

			else
			{
				if (t < number*number)
				{
					Tmp->Element = t;
					Tmp->position = Tmp->Element;
					Tmp->Right = NULL;
					L->Right = Tmp;
					Tmp->Left = L;
					L = Tmp;
				}
				else
				{
					Tmp->Element = 0;
					Tmp->position = number*number;
					Tmp->Right = NULL;
					L->Right = Tmp;
					Tmp->Left = L;
				}
			}
			t++;
		}



		return Header;
	}

void  Printmatrix(List L, int number)
{
	int TmpNumber = number;
	Position Posite;
	Posite = L;

	if (L->Right == NULL)
	{
		printf("\nList is Empty!!");
		Sleep(1000);
		exit(0);
	}

	while (Posite != NULL)
	{
		if (TmpNumber == 0)
		{
			printf("\n\n\n");
			TmpNumber = number;
		}

		printf("%4d     ", Posite->Element);
		Posite = Posite->Right;
		TmpNumber--;
	}
	system("color 0a");
	
}

//寻找0的位置，返回位置. 
Position  FindZero(List L)
{
	Position Tmp, Posite;
	Tmp = L;
	Posite = L;

	while (Tmp != NULL)
	{
		if (Tmp->Element == 0)
		{
			return Tmp;
			break;
		}
		else
		{
			Posite = Tmp->Right;
			Tmp = Posite;
		}
	}
}


Position FindPosite(List L, int number)
{
	Position Tmp, Posite;
	Tmp = L;
	Posite = L;

	while (Tmp != NULL)
	{
		if (Tmp->position == number)
		{
			return Tmp;
			break;
		}
		else
		{
			Posite = Tmp->Right;
			Tmp = Posite;
		}
	}
}

//0向右移动(其他数字向左)
int  Left(List L, int number)
{
	Position P;
	int p3, p6 = 0;
	P = FindZero(L);

	if (P->position % number != 0 && P->Right != NULL)
	{
		p3 = 0;
		P->Element = P->Right->Element;
		P->Right->Element = p3;
		p6 = 1;
	}

	return  p6;
}

//0向左移动(其他数字向右)
int  Right(List L, int number)
{
	Position P;
	int p3, p6 = 0;
	P = FindZero(L);

	if (P->position % number != 1 && P->Left != NULL)
	{
		p3 = 0;
		P->Element = P->Left->Element;
		P->Left->Element = p3;
		p6 = 1;
	}

	return  p6;
}

//0向下移动(其他数字向上)
int  Up(List L, int number)
{
	Position P1, P2;
	int p3, p6 = 0;
	P1 = FindZero(L);//零的位置

	if (P1->position <= number * (number - 1))
	{
		P2 = FindPosite(L, (P1->position + number));//找到零的下方数字
		p3 = 0;
		P1->Element = P2->Element;
		P2->Element = p3;
		p6 = 1;
	}

	return  p6;
}

//0向上移动(其他数字向下)
int  Down(List L, int number)
{
	Position P1, P2;
	int p3, have = 0;
	P1 = FindZero(L);

	if (P1->position >= number + 1)
	{
		P2 = FindPosite(L, (P1->position - number));
		p3 = 0;
		P1->Element = P2->Element;
		P2->Element = p3;
		have = 1;
	}

	return have;
}

//将0移动到右下角
void  MoveBack(List L, int number)
{
	int have = 0;
	Position Posite;
	Posite = FindZero(L);

	if (Posite->position == number * number)
		have = 1;

	else(!have);
	{
		while (Posite->position % number != 0)//将零移到最右端
		{
			Left(L, number);
			Posite = Posite->Right;
		}
		while (Posite->position != number * number)//将0移到最下端
		{
			Up(L, number);
			Posite = FindPosite(L, Posite->position + number);
		}
	}
}

//随机移动 
void  RandomMove(List L, int number, int Line)
{
	srand((int)time(NULL));
	int point = 1, RDnumber;

	for (; point <= number; )
	{
		RDnumber = rand() % 4;
		switch (RDnumber)
		{
		case 0:
			point += Up(L, Line);
			break;
		case 1:
			point += Down(L, Line);
			break;
		case 2:
			point += Left(L, Line);
			break;
		case 3:
			point += Right(L, Line);
			break;
		}
	}

}








int createChildnode(Type_NumberNode * FatherNode)//从接收到的矩阵中找到0的位置并以此分情况讨论创建子节点
{
	printf("***************************************************************\n");
	printf("Fathernode's ID:%d ||| ", FatherNode->NodeID);
	switch (FatherNode->lastOperation)
	{
	case 0:
		printf("LastOperation：S(down).                 *\n");
		break;

	case 1:
		printf("LastOperation：W(up).                   *\n");
		break;
	case 2:
		printf("LastOperation：D(right).                *\n");
		break;
	case 3:
		printf("LastOperation：A(left).                 *\n");
		break;
	default:
		printf("LastOperation：NONE.                    *\n");
		break;
	}
	
	int i, j, PositionX, PositionY;
	for (i = 0;i<3;i++)
		for (j = 0;j<3;j++)
			if (FatherNode->Array[i][j] == 0)
			{
				PositionX = i;
				PositionY = j;
			};
	switch (PositionX)
	{
	case 0:
	{
		if (PositionY == 0)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				for (i = 2;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0],
					PositionX, PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[1],
					PositionX, PositionY, OperationDown);
			}
			else if (FatherNode->lastOperation == OperationLeft)
			{
				FatherNode->nextNode[0] = mallocnode();
				FatherNode->nextNode[0]->preNode = FatherNode;
				for (i = 1;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
			}
			else if (FatherNode->lastOperation == OperationUp)
			{
				FatherNode->nextNode[0] = mallocnode();
				FatherNode->nextNode[0]->preNode = FatherNode;
				for (i = 1;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationRight);
			}
		}
		else if (PositionY == 1)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<3;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationRight);
			}
			else if (FatherNode->lastOperation == OperationLeft)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				for (i = 2;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
			}
			else if (FatherNode->lastOperation == OperationRight)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				for (i = 2;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationDown);
			}
			else if (FatherNode->lastOperation == OperationUp)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				for (i = 2;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationLeft);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationRight);
			}
		}
		else if (PositionY == 2)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				for (i = 2;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
			}
			else if (FatherNode->lastOperation == OperationRight)
			{
				FatherNode->nextNode[0] = mallocnode();
				FatherNode->nextNode[0]->preNode = FatherNode;
				for (i = 1;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
			}
			else if (FatherNode->lastOperation == OperationUp)
			{
				FatherNode->nextNode[0] = mallocnode();
				FatherNode->nextNode[0]->preNode = FatherNode;
				for (i = 1;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationLeft);
			}
		}
		break;
	}
	case 1:
	{
		if (PositionY == 0)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<3;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationLeft)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				for (i = 2;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationDown)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				for (i = 2;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationDown);
			}
			else if (FatherNode->lastOperation == OperationUp)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				for (i = 2;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationUp);
			}
		}
		else if (PositionY == 1)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<4;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[3], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationLeft)
			{
				for (i = 0;i<3;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationRight)
			{
				for (i = 0;i<3;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationUp)
			{
				for (i = 0;i<3;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationUp);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationDown)
			{
				for (i = 0;i<3;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationDown);
			}
		}
		else if (PositionY == 2)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<3;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationDown)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				FatherNode->nextNode[2] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
			}
			else if (FatherNode->lastOperation == OperationUp)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				FatherNode->nextNode[2] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationUp);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
			}
			else if (FatherNode->lastOperation == OperationRight)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				FatherNode->nextNode[2] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationDown);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationUp);
			}
		}
		break;
	}
	case 2:
	{
		if (PositionY == 0)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				FatherNode->nextNode[2] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationUp);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationRight);
			}
			else if (FatherNode->lastOperation == OperationLeft)
			{
				FatherNode->nextNode[0] = mallocnode();
				FatherNode->nextNode[0]->preNode = FatherNode;
				for (i = 1;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationDown)
			{
				FatherNode->nextNode[0] = mallocnode();
				FatherNode->nextNode[0]->preNode = FatherNode;
				for (i = 1;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationRight);

			}
		}
		else if (PositionY == 1)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<3;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationLeft);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[2], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationDown)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				FatherNode->nextNode[2] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationRight);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
			}
			else if (FatherNode->lastOperation == OperationLeft)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				FatherNode->nextNode[2] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationUp);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);
			}
			else if (FatherNode->lastOperation == OperationRight)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				FatherNode->nextNode[2] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationUp);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationRight);
			}
		}
		else if (PositionY == 2)
		{
			if (FatherNode->lastOperation == OperationNone)
			{
				for (i = 0;i<2;i++)
				{
					FatherNode->nextNode[i] = mallocnode();
					FatherNode->nextNode[i]->preNode = FatherNode;
				}
				FatherNode->nextNode[3] = NULL;
				FatherNode->nextNode[2] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationUp);
				Creatnode(FatherNode->nextNode[1], PositionX,
					PositionY, OperationLeft);

			}
			else if (FatherNode->lastOperation == OperationRight)
			{
				FatherNode->nextNode[0] = mallocnode();
				FatherNode->nextNode[0]->preNode = FatherNode;
				for (i = 1;i<4;i++)
				{
					FatherNode->nextNode[i] = NULL;
				}
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationUp);
			}
			else if (FatherNode->lastOperation == OperationDown)
			{
				FatherNode->nextNode[0] = mallocnode();
				FatherNode->nextNode[0]->preNode = FatherNode;
				for (i = 1;i<4;i++)
					FatherNode->nextNode[i] = NULL;
				Creatnode(FatherNode->nextNode[0], PositionX,
					PositionY, OperationLeft);
			}
		}
		break;
	}
	}
	
	return 0;
}

int  Creatnode(Type_NumberNode * node, int Position_X, int Position_Y, Enum_Operate Operate)//初始化节点，初始化结构体，接收0的位置
{
	int i, j;
	PUBLIC_NumberNodeID++;//每一次全局变量ID加1，记录ID
	node->NodeID = PUBLIC_NumberNodeID;//该子节点的ID
	node->TreeDepth = node->preNode->TreeDepth + 1;//搜索深度为父节点加1
	node->lastOperation = Operate;//记录上一次的操作
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
			node->Array[i][j] = node->preNode->Array[i][j];//矩阵与父节点相同
		node->nextNode[i] = NULL;//下一个子节点为空
	}
	if (IfFindgoal(node))
	{
		printf("\n\n   The node is the target node and I will show you the formation process of the node in reverse order.\n");
		printpath(node);
		PUBLIC_IsFinDCorret = 1;

	}

	if (node == NULL)
		return 0;
	else
	{
		switch (Operate)//根据上一次操作改变子节点矩阵
		{
		case OperationDown:	node->Array[Position_X][Position_Y]
			= node->Array[Position_X + 1][Position_Y];
			node->Array[Position_X + 1][Position_Y] = 0;
			break;

		case OperationLeft:	node->Array[Position_X][Position_Y]
			= node->Array[Position_X][Position_Y - 1];
			node->Array[Position_X][Position_Y - 1] = 0;
			break;

		case OperationRight:node->Array[Position_X][Position_Y]
			= node->Array[Position_X][Position_Y + 1];
			node->Array[Position_X][Position_Y + 1] = 0;
			break;

		case OperationUp:	node->Array[Position_X][Position_Y]
			= node->Array[Position_X - 1][Position_Y];
			node->Array[Position_X - 1][Position_Y] = 0;
			break;

		default:
			break;
		}
	}

	printf(" ID： %d  ||||it's searth depth：%d |||| Fathernode's ID: %d     * \n", node->NodeID, node->TreeDepth, node->preNode->NodeID);
	printf("  it's matrix is：                                            *\n");
	printf("               %d %d %d                                          *\n", node->Array[0][0], node->Array[0][1], node->Array[0][2]);
	printf("               %d %d %d                                          *\n", node->Array[1][0], node->Array[1][1], node->Array[1][2]);
	printf("               %d %d %d                                          *\n", node->Array[2][0], node->Array[2][1], node->Array[2][2]);
	printf("______________________________________________________________*\n");
	if (IfFindgoal(node))
	{
		printf("\n\n   The node is the target node and I will show you the formation process of the node in reverse order.\n");
		printpath(node);
		PUBLIC_IsFinDCorret = 1;

	}
	return 0;
}

Type_NumberNode * mallocnode(void)
{
	Type_NumberNode * pReturn = (Type_NumberNode *)malloc(sizeof(Type_NumberNode));
	if ((pReturn == NULL) || (pReturn == (Type_NumberNode *)0xCDCDCDCD))
		printf("Err:Requesting memory failure for child nodes！！！\n 地址为： \n");
	else
		
		return pReturn;
	return pReturn;

}



int  Createnextnode(Type_NumberNode * TreeHead, int TreeDepth)//接受一个结构体指针叫TreeHead和深度
{
	int i;
	if (PUBLIC_IsFinDCorret)
		return 0;
	if (TreeDepth <2)
	{
		for (i = 0;i<4;i++)
		{
			TreeHead->nextNode[i] = NULL;//创建四个节点但全为空
		}
		return 0;//跳出循环
	}
	else
	{
		createChildnode(TreeHead);//创建子节点
		for (i = 0;i<4;i++)
		{
			if (TreeHead->nextNode[i] != NULL)//该子节点非空
			{
				if (TreeHead->TreeDepth >= 12)//如果其搜索深度大于12//第一类剪枝: 除去按同一个方向达到12次以上的搜索
				{
					if (pruning(TreeHead, TreeHead->preNode) == 0)//开始搜索其父节点中是否有重复的，如果有重复的
						pruning(TreeHead->nextNode[i], TreeDepth - 1);//重新生成树但搜索深度减一直到1
					else
						//tree_create_tree(TreeHead->nextNode[i], TreeDepth - 1);
						return 0;
				}
				else
					Createnextnode(TreeHead->nextNode[i], TreeDepth - 1);//创建下一个节点
			}

		}
		return 0;
	}
}

int IfFindgoal(Type_NumberNode * Node)//剪枝
{
	int i, j, findgoal = 1;  //1 相等，0 不相等
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			if (Node->Array[i][j] != PUBLIC_TargetArray[i][j])
			{
				findgoal = 0;
				break;
			}
		}
		if (!findgoal)
			break;
	}
	return findgoal;
}

void printpath(Type_NumberNode * TailNode)
{
	Type_NumberNode * pPrintNode = TailNode;
	printf("\n     ");
	printf("#|A\n  ");
	printf("#|A\n  ");
	while (pPrintNode->preNode != NULL)
	{
		printnode(pPrintNode);
		pPrintNode = pPrintNode->preNode;
	}
	printf("START");
	printf("\n     Your can input other matrix\n");
	printf("***************************************************************\n");
}
void printnode(Type_NumberNode * Node)
{
	switch (Node->lastOperation)
	{
	case 0:
		printf("S(down)<-");
		break;

	case 1:
		printf("W(up)<-");
		break;
	case 2:
		printf("D(right)<-");
		break;
	case 3:
		printf("A(left)<-");
		break;
	default:
		printf("NONE.<-");
		break;
	}


}

int Istargetmatrix(Type_NumberNode * NowNode, Type_NumberNode * LastNode)
{
	int i, j;
	int IsSame = 1;
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
			if (NowNode->Array[i][j] != LastNode->Array[i][j])
			{
				IsSame = 0;
				break;
			}
		if (!IsSame)
			break;
	}
	return IsSame;
}

int pruning(Type_NumberNode * NowNode, Type_NumberNode * FatherNode) //1:存在 2：不存在
{
	if (Istargetmatrix(NowNode, FatherNode))
		return 1;
	else
	{
		if (FatherNode->preNode != NULL)
			pruning(NowNode, FatherNode->preNode);
		else
			return 0;
	}
}

void get_input(void)
{
	int i, j;
	printf("\nPlease enter the searth depth that you want to searth for Numberslider:");
	scanf_s("%d", &PUBLIC_TreeDepth);
	printf("Please enter your matrix ,examples are as follows:\n");
	printf("If the matrix you want to enter is：\n");
	printf("				1 2 3\n");
	printf("				4 5 6\n");
	printf("				7 8 0\n");
	printf("Then you should enter： 1,2,3,4,5,6,7,8,0\n");
	printf("\n  Please enter your matrix: \n");
	printf("\n  Please input the language into English, or you will be at your own risk(重要的事情说三遍): \n");
	printf("\n  Please input the language into English, or you will be at your own risk(重要的事情说三遍): \n");
	printf("\n  Please input the language into English, or you will be at your own risk(重要的事情说三遍): \n");
	scanf_s("%d,%d,%d,%d,%d,%d,%d,%d,%d",
		PUBLIC_NumberInputArray[0], PUBLIC_NumberInputArray[0] + 1, PUBLIC_NumberInputArray[0] + 2,
		PUBLIC_NumberInputArray[1], PUBLIC_NumberInputArray[1] + 1, PUBLIC_NumberInputArray[1] + 2,
		PUBLIC_NumberInputArray[2], PUBLIC_NumberInputArray[2] + 1, PUBLIC_NumberInputArray[2] + 2);

	printf("Your input is:\n");
	for (i = 0;i<3;i++)
	{
		for (j = 0;j<3;j++)
		{
			InputNode.Array[i][j] = PUBLIC_NumberInputArray[i][j];
			printf(" %d", InputNode.Array[i][j]);
		}
		printf("\n");
	}
	InputNode.lastOperation = OperationNone;
	InputNode.NodeID = 0;
	InputNode.preNode = NULL;
	InputNode.TreeDepth = 0;
	PUBLIC_NumberNodeID = 0;

}

void Start()
{

	get_input();//接收输入


	Createnextnode(&InputNode, PUBLIC_TreeDepth);//传送搜索深度，矩阵
	if (PUBLIC_IsFinDCorret)
		PUBLIC_IsFinDCorret = 0;
	else
		printf("Warring:    The correct solition path was not found at the current searth depth !  \n");
}



