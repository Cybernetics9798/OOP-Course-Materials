#include "objPosDLinkedList.h"
#include <iostream>
using namespace std;

// Develop the objPos Doubly Linked List here.  
// Use the Test cases Test.cpp to complete the Test-Driven Development

objPosDLinkedList::objPosDLinkedList()
{
    DNode* DummyH = new DNode();
    DNode* DummyT = new DNode();

    listHead = DummyH;
    listTail = DummyT;
    DummyH->next = DummyT;
    DummyH->prev = nullptr;
    DummyT->prev = DummyH;
    DummyT->next = nullptr;

    persistHead = listHead;
    listSize = 0;
}

objPosDLinkedList::~objPosDLinkedList()
{
    DNode* readerHead;
    readerHead = listHead;
    while(readerHead != nullptr)
    {
        DNode* temp;
        temp = readerHead->next;
        delete readerHead;
        readerHead = temp;
    }
}

int objPosDLinkedList::getSize()
{
    return listSize;
}

bool objPosDLinkedList::isEmpty()
{
    if(listSize == 0)
    {
        return true;
    }
    return false;
}

void objPosDLinkedList::insertHead(const objPos &thisPos)
{
    DNode* newNode = new DNode();
    newNode->data = thisPos;
    newNode->prev = listHead;
    newNode->next = NULL;

    DNode* prevHead;
    prevHead = listHead->next;
    listHead->next = newNode;
    newNode->next = prevHead;
    prevHead->prev = newNode;

    listSize++;
}

void objPosDLinkedList::insertTail(const objPos &thisPos)
{
    DNode* newNode = new DNode();
    newNode->data = thisPos;
    newNode->prev = NULL;
    newNode->next = listTail;

    DNode* prevTail;
    prevTail = listTail->prev;
    listTail->prev = newNode;
    newNode->next = listTail;
    newNode->prev = prevTail;
    prevTail->next = newNode;

    listSize++;
}

void objPosDLinkedList::insert(const objPos &thisPos, int index)
{
    if(index < 0 || index > listSize)
    {
        cout << "Invalid index" << endl;
        return;
    }
    else if(index == 0)
    {
        insertHead(thisPos);
    }
    else if(index == listSize)
    {
        insertTail(thisPos);
    }
    else
    {
        DNode* newNode = new DNode();
        newNode->data = thisPos;
        DNode* readerHead;
        readerHead = listHead->next;
        for(int i = 0; i < index; i++)
        {
            readerHead = readerHead->next;
        }
        DNode* prevNode;
        prevNode = readerHead;
        DNode* nextNode;
        nextNode = readerHead->next;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = nextNode;
        nextNode->prev = newNode;

        listSize++;
    }
}

objPos objPosDLinkedList::getHead() const
{
    return listHead->next->data;
}

objPos objPosDLinkedList::getTail() const
{
    return listTail->prev->data;
}

objPos objPosDLinkedList::get(int index) const
{
    if(index <= 0)
    {
        cout << "Returning smallest index" << endl;
        return getHead();
    }else if(index > listSize - 1)
    {
        cout << "Returning largest index" << endl;
        return getTail();
    }
    else
    {
        DNode* readerHead;
        readerHead = listHead->next;
        for(int i = 0; i < index; i++)
        {
            readerHead = readerHead->next;
        }
        return readerHead->data;
    }
}

objPos objPosDLinkedList::getNext()
{
    persistHead = persistHead->next;
    if(persistHead == NULL){
        persistHead = listHead;
        return objPos(-99,0,0,0,0);
    }
    return persistHead->data;
}

void objPosDLinkedList::resetReadPos()
{
    persistHead = listHead;
}

void objPosDLinkedList::set(const objPos &thisPos, int index)
{
    if(index < 0)
    {
        cout << "Index smaller than 0" << endl;
        index = 0;
    }
    else if(index > listSize - 1)
    {
        cout << "Index larger than list size" << endl;
        index = listSize - 1;
    }

    DNode* readerHead;
    readerHead = listHead->next;
    for(int i = 0; i < index; i++)
    {
        readerHead = readerHead->next;
    }
    readerHead->data = thisPos;
}

objPos objPosDLinkedList::removeHead()
{
    if(listSize <= 0)
    {
        cout << "List is empty" << endl;
        return objPos(-99,0,0,0,0);
    }
    DNode* oldHead;
    oldHead = listHead->next;
    DNode* newHead;
    newHead = oldHead->next;
    listHead->next = newHead;
    newHead->prev = listHead;

    listSize--;
    objPos temp = oldHead->data;
    delete oldHead;
    return temp;
}

objPos objPosDLinkedList::removeTail()
{
    if(listSize == 0)
    {
        cout << "List is empty" << endl;
        return objPos(-99,0,0,0,0);
    }
    DNode* oldTail;
    oldTail = listTail->prev;
    DNode* newTail;
    newTail = oldTail->prev;
    listTail->prev = newTail;
    newTail->next = listTail;

    listSize--;
    objPos temp = oldTail->data;
    delete oldTail;
    return temp;
}

objPos objPosDLinkedList::remove(int index)
{
    if(listSize == 0)
    {
        cout << "Empty List" << endl;
        return objPos(-99,0,0,0,0);
    }
    else if(index <= 0)
    {
        cout << "Removing smallest index" << endl;
        return removeHead();
    }
    else if(index >= listSize - 1)
    {
        cout << "Removing largest index" << endl;
        return removeTail();
    }
    else
    {
        DNode* readerHead;
        readerHead = listHead->next;
        for(int i = 0; i < index; i++)
        {
            readerHead = readerHead->next;
        }

        DNode* prevNode;
        prevNode = readerHead->prev;
        DNode* nextNode;
        nextNode = readerHead->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        objPos temp = readerHead->data;
        delete readerHead;
        listSize--;
        return temp;
    }
}

void objPosDLinkedList::printList() const
{
    DNode* readerHead;
    readerHead = listHead->next;
    for(int i = 0; i < listSize; i++)
    {
        readerHead->data.printObjPos();
        readerHead = readerHead->next;
    }
}


