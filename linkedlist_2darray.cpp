#include "linkedlist_2darray.h"

node::node(): ch('$'), nextNode(NULL) {}

linked_list::linked_list(): pHead(NULL), pTail(NULL), size(0) {}

linked_list::~linked_list() {
    free();
}

void linked_list::free() {
    while(size) 
        deleteBegin();
}

node* linked_list::getKthNode(int index) {
    if (index >= size || index < 0) 
        return NULL;
    if (index == 0)
        return pHead;

    node* result = pHead;
    for (int i = 1; i <= index; i++) 
        result = result->nextNode;
    return result;
}

char &linked_list::operator[] (int index) {
    assert(0 <= index && index < size);
    return getKthNode(index)->ch;
}  

int linked_list::getSize() {
    return size;
}

void linked_list::initLen(int len) {
    for (int i = 0; i < len; i++)
        addBegin('$');
}

void linked_list::addBegin(char ch) {
    node* newNode = new node();
    newNode->ch = ch;
    newNode->nextNode = pHead;
    pHead = newNode;
    ++size;

    if (size == 1) {
        pTail = pHead;
    }
}

void linked_list::deleteBegin() {
    if (!size) {
        return;
    }

    node* nextNode = pHead->nextNode;
    delete pHead;
    pHead = nextNode;
    --size;

    if (size == 0) {
        pTail = NULL;
    }
}

void linked_list::addEnd(char ch) {
    if (pHead == NULL) {
        addBegin(ch);
        return;
    }

    node* newNode = new node();
    newNode->ch = ch;
    pTail->nextNode = newNode;
    pTail = newNode;
    ++size;
}

void linked_list::deleteEnd() {
    if (size == 0) {
        return;
    }

    if (size == 1) {
        deleteBegin();
        return;
    }

    node* prevNode = getKthNode(size - 2);
    prevNode->nextNode = NULL;
    delete pTail;
    pTail = prevNode;
    --size;
}

void linked_list::addNode(int index, char ch) {
    if (index < 0 || index > size)
        return;
    
    if (index == 0) {
        addBegin(ch);
        return;
    }

    if (index == size) {
        addEnd(ch);
        return;
    }

    node* prevNode = getKthNode(index - 1);
    node* curNode = new node();
    curNode->ch = ch;
    curNode->nextNode = prevNode->nextNode;
    prevNode->nextNode = curNode;
    ++size;
}

void linked_list::deleteNode(int index) {
    if (index >= size || index < 0) 
        return;

    if (index == 0) {
        deleteBegin();
        return;
    }

    if (index == size - 1) {
        deleteEnd();
        return;
    }

    node* prevNode = getKthNode(index - 1);
    node* curNode = prevNode->nextNode;
    prevNode->nextNode = curNode->nextNode;
    delete curNode;
    --size;
}

node_2d::node_2d(): row(), nextRow(NULL) {}

linked_list_2d::linked_list_2d(): pHeadCol(NULL), size(0) {}
linked_list_2d::~linked_list_2d() {
    free();
}
void linked_list_2d::free() {
    while(size) 
        deleteBegin();
}

node_2d* linked_list_2d::getKthCol(int index) {
    if (index >= size || index < 0) 
        return NULL;
    if (index == 0)
        return pHeadCol;

    node_2d* result = pHeadCol;
    for (int i = 1; i <= index; i++) 
        result = result->nextRow;
    return result;
}

linked_list &linked_list_2d::operator[] (int index) {
    assert(0 <= index && index < size);
    return getKthCol(index)->row;
}  

int linked_list_2d::getSize() {
    return size;
}

void linked_list_2d::initLen(int len) {
    for (int i = 0; i < len; i++)
        addBegin();
}

void linked_list_2d::init2DArray(int m, int n) {
    for (int i = 0; i < m; i++) {
        addBegin();
        pHeadCol->row.initLen(n);
    }
}

void linked_list_2d::addBegin() {
    node_2d* newCol = new node_2d();
    newCol->nextRow = pHeadCol;
    pHeadCol = newCol;
    ++size;
}

void linked_list_2d::deleteBegin() {
    node_2d* nextRow = pHeadCol->nextRow;
    delete pHeadCol;
    pHeadCol = nextRow;
    --size;
}

void linked_list_2d::addCol(int index) {
    if (index < 0 || index > size)
        return;
    
    if (index == 0) {
        addBegin();
        return;
    }

    node_2d* prevCol = getKthCol(index - 1);
    node_2d* curCol = new node_2d();
    curCol->nextRow = prevCol->nextRow;
    prevCol->nextRow = curCol;
    ++size;
}

void linked_list_2d::deleteCol(int index) {
    if (index >= size || index < 0) 
        return;

    if (index == 0) {
        deleteBegin();
        return;
    }

    node_2d* prevNode = getKthCol(index - 1);
    node_2d* curCol = prevNode->nextRow;
    prevNode->nextRow = curCol->nextRow;
    delete curCol;
    --size;
}