#pragma once

#include <assert.h>

struct node {
    char ch;
    node* nextNode;

    node();
};

struct linked_list {
    node* pHead;
    node* pTail;
    int size;

    linked_list();
    ~linked_list();
    void free();

    node* getKthNode(int index);
    char &operator[] (int index);

    int getSize();
    void initLen(int len);

    void addBegin(char ch);
    void deleteBegin();
    void addEnd(char ch);
    void deleteEnd();
    void addNode(int index, char ch);
    void deleteNode(int index);
};

struct node_2d {
    linked_list column;
    node_2d* nextCol;

    node_2d();
};

struct linked_list_2d {
    node_2d* pHeadCol;
    int size;

    linked_list_2d();
    ~linked_list_2d();
    void free();

    node_2d* getKthCol(int index);
    linked_list &operator[] (int index);

    int getSize();
    void initLen(int len);
    void init2DArray(int m, int n);

    void addBegin();
    void deleteBegin();
    void addCol(int index);
    void deleteCol(int index);
};