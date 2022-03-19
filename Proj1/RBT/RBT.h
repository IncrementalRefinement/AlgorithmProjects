#ifndef RBT_H
#define RBT_H


#define RED 0
#define BLACK 1
#define COLOR int
#define ElemType int

typedef struct RBTnode{
	COLOR Color;
	ElemType Data;
	struct RBTnode *Lchild,*Rchild,*Parent;
}RBTnode,*RBT;

RBT RBT_initTree();
RBT RBT_Insert(RBT T,ElemType data);
RBT RBT_InsertFixup(RBT T,ElemType data);
RBT RBT_Query(RBT T,ElemType data);
void RBT_InsertCase1(RBT I);
void RBT_InsertCase2(RBT I);
void RBT_InsertCase3(RBT I);
void RBT_InsertCase4(RBT I);
void RBT_InsertCase5(RBT I);
RBT RBT_Delete(RBT T,ElemType data);
RBT RBT_DeleteFixup(RBT T,RBT node,RBT parent);
void RBT_DeleteCase1(RBT T,RBT node);
void RBT_DeleteCase2(RBT T,RBT node);

#endif