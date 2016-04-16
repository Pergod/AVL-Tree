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
AVLTree *SingleLeftRotation( AVLTree *);//左单旋 
AVLTree *SingleRightRotation(AVLTree *);//右单旋 
AVLTree *DoubleLeftRightRotation (AVLTree *);//LR双旋 
AVLTree *DoubleRightLeftRotation (AVLTree *);//RL 双旋 
AVLTree *Insert( AVLTree *, int);//平衡二叉树的插入
AVLTree *CreatAVLTree();//平衡二叉树的创建 
int GetHeight(AVLTree *);//树的高度 
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
//单旋 
AVLTree *SingleLeftRotation( AVLTree *A)//LL单旋   （左边的左子树） 左单旋 
{ 
	/* 注意：A必须有一个左子结点B */
	/* 1.将A与B做左单旋，2.更新A与B的高度，3.返回新的根结点B */   
	//1.  
    AVLTree *B = A->Left;
    A->Left = B->Right;//将B的右子树连接到A的左子树上 
    B->Right = A;//将A连接到B的右子树上 
    //2. 
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;//原始树高 
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;//更新后树高 
    //3. 
    return B;
}
AVLTree *SingleRightRotation(AVLTree *A)//RR单旋    （右边的右子树） 右单旋 
{
	AVLTree *B = A->Right;
    A->Right = B->Left;//将B的左子树连接到A的右子树上 
    B->Left = A;//将A连接到B的左子树上 
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;//原始树高 
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;//更新后树高
    return B;
}

//双旋 
AVLTree *DoubleLeftRightRotation (AVLTree *A)//LR双旋     （左边的右子树）  左右双旋 
{ 
	/* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
	/* 将A、B与C做两次单旋，返回新的根结点C */
	
    /* 将B与C做右单旋，C被返回 */
/*   AVLTree *B=A->Left; AVLTree *C=SingleRightRotation(B)将A的左子树（B）进行右旋转; A->Left=C将旋转后的节点连接到A的左子树上;  代码注释*/
    A->Left=SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}
AVLTree *DoubleRightLeftRotation (AVLTree *A)//RL 双旋     （右边的左子树）   右左双旋 
{
	/* 注意：A必须有一个右子结点B，且B必须有一个左子结点C */
	/* 将A、B与C做两次单旋，返回新的根结点C */
	
	//将B与C做左单旋，C被返回 
	A->Right=SingleLeftRotation(A->Right);
	//将A与C做右单旋，C被返回 
	return SingleRightRotation(A);
}
AVLTree *Insert(AVLTree *T,int X)
{ 
	/* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if (!T)  /* 若插入空树，则新建包含一个结点的树 */
	{
        T = (AVLTree *)malloc(sizeof(AVLTree));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (插入空树) 结束 */
    else if ( X < T->Data )/* 插入T的左子树 */
	{
        T->Left = Insert( T->Left, X);
        if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )/* 如果需要左旋 */
        {
        	if ( X < T->Left->Data )/* 左单旋 */
        	{
        		T = SingleLeftRotation(T);
			}
			else/* 左-右双旋 */
			{
				T = DoubleLeftRightRotation(T);
			}
		}
    } /* else if (插入左子树) 结束 */
    else if (X >T->Data) /* 插入T的右子树 */
	{
        T->Right = Insert( T->Right, X );
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )/* 如果需要右旋 */
            if ( X > T->Right->Data )/* 右单旋 */
            {
            	T = SingleRightRotation(T); 
			}
            else/* 右-左双旋 */
            {
            	T=DoubleRightLeftRotation(T);
			}
    } /* else if (插入右子树) 结束 */
    /* else X == T->Data，无须插入 */
    /* 别忘了更新树高 */
    T->Height = Max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;
    return T;
}
