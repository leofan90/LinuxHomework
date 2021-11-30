//
//  main.c
//  MemoryManagment
//
//  Created by LEO on 2021/11/30.
//  Copyright © 2021 LEO. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct LNode{
    int size;
    int first_address;
    char state;
    bool segment;
    struct LNode *next;
} LinkNode;

void CreateListR(LinkNode* L, int* s, int* a, int n){
    LinkNode *f, *b; //front and back
    L = (LinkNode *)malloc(sizeof(LinkNode));
    b = L;
    for (int i = 0; i < n; i++) {
        f = (LinkNode *)malloc(sizeof(LinkNode));
        f -> size = s[i];
        f -> first_address = a[i];
        f -> state = 'F';
        f -> segment = false;
        b -> next = f;
        b = f;
    }
    b -> next = NULL;
}

bool ListInsert(LinkNode *L, int i, int ns, int na){
    int j = 0;
    LinkNode *p = L, *s;
    if (i < 0) {
        printf("输入错误");
        printf("\n");
        return false;
    }
    while (j < i - 1 && p != NULL) {
        j++;
        p = p -> next;
    }
    if (p == NULL) {
        printf("未找到插入点");
        printf("\n");
        return false;
    }
    else{
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s -> size = ns;
        s -> first_address = na;
        s -> state = 'F';
        s -> segment = false;
        s -> next = p -> next;
        p -> next = s;
        return true;
    }
}
bool ListDelete(LinkNode *L, int i){
    int j = 0;
    LinkNode *p = L, *q;
    if (i <= 0) {
        printf("输入错误");
        printf("\n");
        return false;
    }
    while (j < i - 1 && p != NULL) {
        j++;
        p = p -> next;
    }
    if (p == NULL) {
        printf("未找到删除点");
        printf("\n");
        return false;
    }
    else{
        q = p -> next;
        if (q == NULL) {
            printf("未找到删除点");
            printf("\n");
            return false;
        }
        p -> next = q -> next;
        free(q);
        return true;
    }
}

bool new_malloc(LinkNode *L, int s){
    int i = 1;
    LinkNode *p = L -> next;
    while (p != NULL && (p -> size < s || p -> state == 'T')) {
        p = p -> next;
        i++;
    }
    if (p == NULL) {
        printf("无法申请空间");
        printf("\n");
        return false;
    }
    else{
        if (p -> size - s != 0) {
            p -> segment = true;
            ListInsert(L, i + 1, p -> size - s, p -> first_address + s);
        }
        p -> state = 'T';
        p -> size = s;
        printf("你申请的空间地址为 %d", p -> first_address);
        printf("\n");
        return true;
    }
}

void combine(LinkNode *L){
    int i = 1;
    LinkNode *p = L -> next;
    while (p -> segment == true && (p -> next) -> state == 'F') {
        p -> size += (p -> next) -> size;
        p -> segment = (p -> next) -> segment;
        ListDelete(L, i + 1);
    }
}

bool new_free(LinkNode *L, int a){
    int i = 1;
    LinkNode *p = L -> next;
    while (p != NULL && (p -> first_address != a || p -> state == 'F')) {
        p = p -> next;
        i++;
    }
    if (p == NULL) {
        printf("无法回收空间");
        printf("\n");
        return false;
    }
    else{
        p -> state = 'F';
        while (p -> segment == true && (p -> next) -> state == 'F') {
            p -> size += (p -> next) -> size;
            p -> segment = (p -> next) -> segment;
            ListDelete(L, i + 1);
        }
        combine(L);
        printf("空间已回收");
        printf("\n");
        return true;
    }
}

int main(int argc, const char * argv[]) {
    int x;
    int a[1] = {0};
    int s[1] ={4096};
    LinkNode *L = NULL;
    CreateListR(L, s, a, sizeof(a) / sizeof(a[0]));
    while(1){
        printf("请选择 1:申请 2:回收 3:退出");
        printf("\n");
        scanf("%d", &x);
        printf("\n");
        if (x == 1) {
            printf("请输入要申请的内存空间大小");
            printf("\n");
            scanf("%d", &x);
            printf("\n");
            new_malloc(L, x);
        }
        else if (x == 2){
            printf("请输入要回收的内存首地址空间");
            printf("\n");
            scanf("%d", &x);
            printf("\n");
            new_free(L, x);
        }
        else{
            printf("\n");
            break;
        }
    }
    return 0;
}
