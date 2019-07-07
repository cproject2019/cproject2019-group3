#ifndef _List_H_
#define _List_H_




struct Node; //结构体
typedef struct Node *PtrToNode;//一个指针
typedef PtrToNode List;//链表
typedef PtrToNode Position;//位置结构

extern void Printmatrix(List L, int numebr);//打印链表
extern void RandomMove(List L, int number);//随机移动
extern void MoveBack(List L, int number);//将0移动回右下角
extern void StartGame(List L, int number);//游戏开始（输入链表和矩阵大小） 

extern int Right(List L, int number);//向右移动 
extern int Left(List L, int number);//向左移动
extern int Up(List L, int number);//向上移动 
extern int Down(List L, int number);//向下移动

extern List CreatList();//制作表头 
extern List Creatmatrix(int number);//制作数组

extern Position FindZero(List L);//寻找0的位置 
extern Position FindPosite(List L, int number);//寻找某个位置
void help();


enum enum_1
{
	OperationDown = 0,						
	OperationUp = 1,						
	OperationRight = 2,						
	OperationLeft = 3,						
	OperationNone = 4	,					
};
typedef enum enum_1  Enum_Operate;
typedef struct numberslider_struct_1 Type_NumberNode;
typedef enum enum_1  Enum_Operate;
extern int PUBLIC_KlotskiNodeID;
extern short PUBLIC_TargetArray[3][3];
extern int PUBLIC_TreeDepth;
extern int PUBLIC_KlotskiInputArray[3][3];
extern Type_NumberNode InputNode;//
struct numberslider_struct_1
{
	int NodeID;								
	int TreeDepth;							
	Enum_Operate lastOperation;				
	short Array[3][3];						
	Type_NumberNode * preNode;				
	Type_NumberNode * nextNode[4];			
};

int createChildnode(Type_NumberNode * FatherNode);
int Creatnode(Type_NumberNode * node, int Position_X, int Position_Y, Enum_Operate Operate);
Type_NumberNode * mallocnode(void);
int Createnextnode(Type_NumberNode * TreeHead, int TreeDepth);
int IfFind(Type_NumberNode * Node);
void printpath(Type_NumberNode * TailNode);
void printnode(Type_NumberNode * Node);
int pruning(Type_NumberNode * NowNode, Type_NumberNode * FatherNode); 
int Istargetmatrix(Type_NumberNode * NowNode, Type_NumberNode * LastNode);
void get_input(void);
void Start(void);




#endif    
