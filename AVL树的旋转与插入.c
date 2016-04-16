#include<stdio.h>
#include<stdlib.h>
#define LOCAL
#define Null -1
typedef struct AVLNode{
	int Data;
	struct AVLNode *Left;
	struct AVLNode *Right;
	int Height;
}AVLTree;
AVLTree *SingleLeftRotation( AVLTree *);//���� 
AVLTree *SingleRightRotation(AVLTree *);//�ҵ��� 
AVLTree *DoubleLeftRightRotation (AVLTree *);//LR˫�� 
AVLTree *DoubleRightLeftRotation (AVLTree *);//RL ˫�� 
AVLTree *Insert( AVLTree *, int);//ƽ��������Ĳ���
AVLTree *CreatAVLTree();//ƽ��������Ĵ��� 
int GetHeight(AVLTree *);//���ĸ߶� 
int main()
{
	AVLTree *T=CreatAVLTree();
	AVLTree *R=Insert(T,12);
	return 0;
}
AVLTree *CreatAVLTree()
{
	AVLTree *T=(AVLTree *)malloc(sizeof(AVLTree));
	return T;	
} 
int Max ( int a, int b )
{
	return a > b ? a : b;
}
int GetHeight(AVLTree *A)
{
	int H;
	int LeftHeight,RightHeight;
	if(!A)
	{
		H=0;
	}
	else
	{
		LeftHeight=GetHeight(A->Left);
		RightHeight=GetHeight(A->Right);
	}
	H=Max(LeftHeight,RightHeight);
	return H+1;
}
//���� 
AVLTree *SingleLeftRotation( AVLTree *A)//LL����   ����ߵ��������� ���� 
{ 
	/* ע�⣺A������һ�����ӽ��B */
	/* 1.��A��B��������2.����A��B�ĸ߶ȣ�3.�����µĸ����B */   
	//1.  
    AVLTree *B = A->Left;
    A->Left = B->Right;//��B�����������ӵ�A���������� 
    B->Right = A;//��A���ӵ�B���������� 
    //2. 
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;//ԭʼ���� 
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;//���º����� 
    //3. 
    return B;
}
AVLTree *SingleRightRotation(AVLTree *A)//RR����    ���ұߵ��������� �ҵ��� 
{
	AVLTree *B = A->Right;
    A->Right = B->Left;//��B�����������ӵ�A���������� 
    B->Left = A;//��A���ӵ�B���������� 
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;//ԭʼ���� 
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;//���º�����
    return B;
}

//˫�� 
AVLTree *DoubleLeftRightRotation (AVLTree *A)//LR˫��     ����ߵ���������  ����˫�� 
{ 
	/* ע�⣺A������һ�����ӽ��B����B������һ�����ӽ��C */
	/* ��A��B��C�����ε����������µĸ����C */
	
    /* ��B��C���ҵ�����C������ */
/*   AVLTree *B=A->Left; AVLTree *C=SingleRightRotation(B)��A����������B����������ת; A->Left=C����ת��Ľڵ����ӵ�A����������;  ����ע��*/
    A->Left=SingleRightRotation(A->Left);
    /* ��A��C��������C������ */
    return SingleLeftRotation(A);
}
AVLTree *DoubleRightLeftRotation (AVLTree *A)//RL ˫��     ���ұߵ���������   ����˫�� 
{
	/* ע�⣺A������һ�����ӽ��B����B������һ�����ӽ��C */
	/* ��A��B��C�����ε����������µĸ����C */
	
	//��B��C��������C������ 
	A->Right=SingleLeftRotation(A->Right);
	//��A��C���ҵ�����C������ 
	return SingleRightRotation(A);
}
AVLTree *Insert(AVLTree *T,int X)
{ 
	/* ��X����AVL��T�У����ҷ��ص������AVL�� */
    if (!T)  /* ��������������½�����һ�������� */
	{
        T = (AVLTree *)malloc(sizeof(AVLTree));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (�������) ���� */
    else if ( X < T->Data )/* ����T�������� */
	{
        T->Left = Insert( T->Left, X);
        if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )/* �����Ҫ���� */
        {
        	if ( X < T->Left->Data )/* ���� */
        	{
        		T = SingleLeftRotation(T);
			}
			else/* ��-��˫�� */
			{
				T = DoubleLeftRightRotation(T);
			}
		}
    } /* else if (����������) ���� */
    else if (X >T->Data) /* ����T�������� */
	{
        T->Right = Insert( T->Right, X );
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )/* �����Ҫ���� */
            if ( X > T->Right->Data )/* �ҵ��� */
            {
            	T = SingleRightRotation(T); 
			}
            else/* ��-��˫�� */
            {
            	T=DoubleRightLeftRotation(T);
			}
    } /* else if (����������) ���� */
    /* else X == T->Data��������� */
    /* �����˸������� */
    T->Height = Max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;
    return T;
}
