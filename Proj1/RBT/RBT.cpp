#include<stdio.h>
#include<stdlib.h>

#include "RBT.h"


RBT RBT_initTree(){
    RBT T=(RBT)malloc(sizeof(RBTnode));
    T->Parent=NULL;
    T->Lchild=NULL;
    T->Rchild=NULL;
    return T;
}

RBT RBT_Insert(RBT T,ElemType data){
    if(!T){
        T=RBT_initTree();
        T->Data=data;
        T->Color=RED;
    }
    else{
        if(T->Data>data){
            T->Lchild=RBT_Insert(T->Lchild,data);
            T->Lchild->Parent=T;
        }
        else if(T->Data<data){
            T->Rchild=RBT_Insert(T->Rchild,data);
            T->Rchild->Parent=T;
        }
        else{
            printf("插入了已有元素\n");
        }
    }
    return T;
}

RBT RBT_InsertFixup(RBT T,ElemType data){
    if(!T->Lchild&&!T->Rchild){
        T->Color=BLACK;
    }
    else{
        RBT I=RBT_Query(T,data);
        while(I->Parent&&I->Color==RED){
            RBT p=I->Parent,gp=I->Parent->Parent;
            if(p->Color==BLACK){
                return T;
            }
            else{
                if(gp->Lchild==p){
                    if(gp->Rchild&&gp->Rchild->Color==RED){
                        RBT_InsertCase1(I);
                        I=gp;
                        if(!I->Parent){
                            I->Color=BLACK;
                        }
                    }
                    else{
                        if(I==p->Lchild){
                            RBT_InsertCase2(I);
                            if(!p->Parent){
                                T=p;
                            }
                            I=p;
                        }
                        else{
                            RBT_InsertCase3(I);
                            if(!I->Parent){
                                T=I;
                            }
                        }
                    }
                }
                else{
                    if(gp->Lchild&&gp->Lchild->Color==RED){
                        RBT_InsertCase1(I);
                        I=gp;
                        if(!I->Parent){
                            I->Color=BLACK;
                        }
                    }
                    else{
                        if(I==p->Lchild){
                            RBT_InsertCase4(I);
                            if(!I->Parent){
                                T=I;
                            }
                        }
                        else{
                            RBT_InsertCase5(I);
                            if(!p->Parent){
                                T=p;
                            }
                            I=p;
                        }
                    }
                }
            }
        }
    }
    return T;
}

RBT RBT_Query(RBT T,ElemType data){
    if(!T){
        printf("空树！\n");
        return T;
    }
    RBT ret=T;
    while(ret){
        if(ret->Data>data){
            ret=ret->Lchild;
        }
        else if(ret->Data<data){
            ret=ret->Rchild;
        }
        else{
            return ret;
        }
    }
    if(!ret){
        printf("树中无该元素！\n");
    }
    return NULL;
}

void RBT_InsertCase1(RBT I){
    I->Parent->Parent->Color=RED;
    I->Parent->Parent->Lchild->Color=BLACK;
    I->Parent->Parent->Rchild->Color=BLACK;
}

void RBT_InsertCase2(RBT I){
    RBT P=I->Parent,GP=I->Parent->Parent;
    RBT A=P->Rchild;
    GP->Lchild=A;
    if(A){
        A->Parent=GP;
    }
    P->Parent=GP->Parent;
    if(GP->Parent){
        if(GP==GP->Parent->Rchild){
            GP->Parent->Rchild=P;
        }
        else{
            GP->Parent->Lchild=P;
        }
    }
    P->Rchild=GP;
    GP->Parent=P;
    P->Color=BLACK;
    GP->Color=RED;
}

void RBT_InsertCase3(RBT I){
    RBT P=I->Parent,GP=I->Parent->Parent;
    RBT B=I->Lchild,C=I->Rchild;
    P->Rchild=B;
    if(B){
        B->Parent=P;
    }
    GP->Lchild=C;
    if(C){
        C->Parent=GP;
    }
    I->Parent=GP->Parent;
    if(GP->Parent){
        if(GP==GP->Parent->Rchild){
            GP->Parent->Rchild=I;
        }
        else{
            GP->Parent->Lchild=I;
        }
    }
    I->Lchild=P;
    P->Parent=I;
    I->Rchild=GP;
    GP->Parent=I;
    I->Color=BLACK;
    GP->Color=RED;
}

void RBT_InsertCase4(RBT I){
    RBT P=I->Parent,GP=I->Parent->Parent;
    RBT B=I->Lchild,C=I->Rchild;
    GP->Rchild=B;
    if(B){
        B->Parent=GP;
    }
    P->Lchild=C;
    if(C){
        C->Parent=P;
    }
    I->Parent=GP->Parent;
    if(GP->Parent){
        if(GP==GP->Parent->Rchild){
            GP->Parent->Rchild=I;
        }
        else{
            GP->Parent->Lchild=I;
        }
    }
    I->Rchild=P;
    P->Parent=I;
    I->Lchild=GP;
    GP->Parent=I;
    I->Color=BLACK;
    GP->Color=RED;
}

void RBT_InsertCase5(RBT I){
    RBT P=I->Parent,GP=I->Parent->Parent;
    RBT B=P->Lchild;
    GP->Rchild=B;
    if(B){
        B->Parent=GP;
    }
    P->Parent=GP->Parent;
    if(GP->Parent){
        if(GP->Parent->Lchild==GP){
            GP->Parent->Lchild=P;
        }
        else{
            GP->Parent->Rchild=P;
        }
    }
    P->Lchild=GP;
    GP->Parent=P;
    GP->Color=RED;
    P->Color=BLACK;
}

RBT RBT_Delete(RBT T,ElemType data){
    RBT node=RBT_Query(T,data);
    RBT Tmp,Ch,P;
    COLOR color;
    if(!node){
        printf("删除元素未找到！\n");
        return T;
    }
    if(node->Lchild&&node->Rchild){
        Tmp=node->Lchild;
        P=node->Parent;
        while(Tmp->Rchild!=NULL){
            Tmp=Tmp->Rchild;
        }
        if(node->Parent) {
            if(node==node->Parent->Lchild){
                node->Parent->Lchild=Tmp;
            }
            else{
                node->Parent->Rchild=Tmp;
            }
        }
        else{
            T=Tmp;
        }
        P=Tmp->Parent;
        Ch=Tmp->Lchild;
        color=Tmp->Color;
        if(P==node){
            P=Tmp;
        }
        else{
            if(Ch){
                Ch->Parent=P;
            }
            P->Rchild=Ch;
            Tmp->Lchild=node->Lchild;
            node->Lchild->Parent=Tmp;
        }
        Tmp->Parent=node->Parent;
        Tmp->Color=node->Color;
        Tmp->Rchild=node->Rchild;
        node->Rchild->Parent=Tmp;
    }
    else{
        if(node->Lchild!=NULL){
            Ch=node->Lchild;
        }
        else{
            Ch=node->Rchild;
        }
        P=node->Parent;
        color=node->Color;
        if(Ch){
            Ch->Parent=P;
        }
        if(P){
            if(P->Lchild==node){
                P->Lchild=Ch;
            }
            else{
                P->Rchild=Ch;
            }
        }
        else{
            T=Ch;
        }
    }
    if(color==BLACK){
        T=RBT_DeleteFixup(T,Ch,P);
        free(node);
    }
    return T;
}

void RBT_DeleteCase1(RBT T,RBT node){
    RBT right=node->Rchild;
    if((node->Rchild=right->Lchild)){
        right->Lchild->Parent=node;
    }
    right->Lchild=node;
    if((right->Parent=node->Parent)){
        if (node == node->Parent->Rchild){
            node->Parent->Rchild=right;
        }
        else{
            node->Parent->Lchild=right;
        }
    }
    else{
        T=right;
    }
    node->Parent=right;
}

void RBT_DeleteCase2(RBT T,RBT node){
    RBT left=node->Lchild;
    if((node->Lchild=left->Rchild)){
        left->Rchild->Parent=node;
    }
    left->Rchild=node;
    if ((left->Parent=node->Parent)){
        if (node==node->Parent->Rchild){
            node->Parent->Rchild=left;
        }
        else{
            node->Parent->Lchild=left;
        }
    }
    else{
        T=left;
    }
    node->Parent=left;
}

RBT RBT_DeleteFixup(RBT T,RBT child,RBT parent){
    RBT brother;
    while((child!=T)&&(!child||child->Color==BLACK)){
        if(child==parent->Lchild)
        {
            brother=parent->Rchild;
            if (brother->Color==RED)
            {
                brother->Color=BLACK;
                parent->Color=RED;
                RBT_DeleteCase1(T, parent);
                brother=parent->Rchild;
            }
            if (!brother->Lchild&&!brother->Rchild||brother->Lchild->Color==BLACK&&brother->Rchild->Color==BLACK)
            {
                brother->Color=RED;
                child=parent;
            }
            else
            {
                if (brother->Rchild->Color==BLACK)
                {
                    brother->Lchild->Color=BLACK;
                    brother->Color=RED;
                    RBT_DeleteCase2(T,brother);
                    brother=parent->Rchild;
                }
                brother->Color=parent->Color;
                parent->Color=BLACK;
                brother->Rchild->Color=BLACK;
                RBT_DeleteCase1(T,parent);
                child=T;
            }
        }
        else
        {
            brother=parent->Lchild;
            if (brother->Color==RED)
            {
                brother->Color=BLACK;
                parent->Color=RED;
                RBT_DeleteCase2(T,parent);
                brother=parent->Lchild;
            }
            if (!brother->Rchild&&!brother->Lchild||brother->Rchild->Color==BLACK&&brother->Lchild->Color==BLACK)
            {
                brother->Color=RED;
                child=parent;
            }
            else
            {
                if (!brother->Lchild||brother->Lchild->Color==BLACK)
                {
                    brother->Rchild->Color=BLACK;
                    brother->Color=RED;
                    RBT_DeleteCase1(T,brother);
                    brother=parent->Lchild;
                }
                brother->Color=parent->Color;
                parent->Color=BLACK;
                brother->Lchild->Color=BLACK;
                RBT_DeleteCase2(T,parent);
                child=T;
            }
        }
    }
    child->Color=BLACK;
    return T;
}
