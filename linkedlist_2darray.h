#pragma once

#include <iostream>
#include <assert.h>
#include <iostream>

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

    // get the k'th node of list
    node* getKthNode(int index);
    // overload operator [] to get the content of k'th node
    char &operator[] (int index);

    // get size of list
    int getSize();
    // init the len of list
    void initLen(int len);

    void addBegin(char ch);
    void deleteBegin();
    void addEnd(char ch);
    void deleteEnd();
    void addNode(int index, char ch);
    void deleteNode(int index);
};

struct node_2d {
    linked_list row;
    node_2d* nextRow;

    node_2d();
};

struct linked_list_2d {
    node_2d* pHeadRow;
    int size;

    linked_list_2d();
    ~linked_list_2d();
    void free();

    node_2d* getKthRow(int index);
    linked_list &operator[] (int index);

    int getSize();
    void initLen(int len);
    void init2DArray(int m, int n);

    void addBegin();
    void deleteBegin();
    void addRow(int index);
    void deleteRow(int index);
};