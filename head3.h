#ifndef _List_H_
#define _List_H_




struct Node; //�ṹ��
typedef struct Node *PtrToNode;//һ��ָ��
typedef PtrToNode List;//����
typedef PtrToNode Position;//λ�ýṹ

extern void Printmatrix(List L, int numebr);//��ӡ����
extern void RandomMove(List L, int number);//����ƶ�
extern void MoveBack(List L, int number);//��0�ƶ������½�
extern void StartGame(List L, int number);//��Ϸ��ʼ����������;����С�� 

extern int Right(List L, int number);//�����ƶ� 
extern int Left(List L, int number);//�����ƶ�
extern int Up(List L, int number);//�����ƶ� 
extern int Down(List L, int number);//�����ƶ�

extern List CreatList();//������ͷ 
extern List Creatmatrix(int number);//��������

extern Position FindZero(List L);//Ѱ��0��λ�� 
extern Position FindPosite(List L, int number);//Ѱ��ĳ��λ��
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
