#ifndef __LIST_H__
#define __LIST_H__
#include <cstring>
#include <cstdio>

template<class T> struct LNode{
 T data;      //数据域
 struct LNode *next; //指针域
};

; template<class T>
int InitLinklist(struct LNode<T>* &L) {
    L = new LNode<T>;
    L->next = NULL;
    return 0;
}

template<class T>
void CreateLinklist(struct LNode<T>* &L, const T data) {
    LNode<T> * p = L;
    while(p->next) {
        p = p->next;
    }
    InitLinklist(p->next);
    p->next->data = data;
}

template<class T>
int InsertLinklist(struct LNode<T>* &L, int i, T e) {
    // i必须是正数。
    if(i < 0) {
        return 1;
    }
    int l = 0;
    LNode<T> * p = L;
    while(p->next) {
        p = p->next;
        if(l++ == i - 1) {
            // 在 i - 1 之后插入新的元素
            LNode<T> * u = new LNode<T>;
            u->data = e;
            u->next = p->next;
            p->next = u;
            return 0;
        }
    }
    // i 太大
    return 1;
}
template<class T>
int DelLinklist(struct LNode<T>* &L, int i, T &e) {
    // i必须是正数。
    if(i < 0) {
        return 1;
    }
    int l = 0;
    LNode<T> * p = L;
    while(p->next) {
        if(l++ == i - 1) {
            e = p->next->data;
            if(p->next) // 如果是最后一个元素
                p->next = p->next->next;
            else
                p->next = NULL;
            return 0;
        }
        p = p->next;
    }
    // i 太大
    return 1;
}

template<class T>
int GetDataLinklist(struct LNode<T>* &L, int i, T &e) {
    // i必须是正数。
    if(i < 0) {
        return 1;
    }
    int l = 0;
    LNode<T> * p = L;
    while(p->next) {
        p = p->next;
        if(l++ == i) {
            // 当循环次数为 i 时
            e = p->data;
            return 0;
        }
    }
    // i 太大
    return 1;
}

template<class T>
int CountLinklist(struct LNode<T>* &L) {
    int i = 0;
    LNode<T> *p = L;
    while(p->next) {
        p = p->next;
        i++;
    }
    return i;
}
#endif // __LIST_H__