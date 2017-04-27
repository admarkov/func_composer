//
// Created by admarkov on 27.04.17.
//

#ifndef FUNC_COMPOSER_LINKEDLIST_H
#define FUNC_COMPOSER_LINKEDLIST_H

template <class T>
class listNode {
public:
    T data;
    listNode* prev;
    listNode* next;
    listNode() : next(nullptr), prev(nullptr) {}
    listNode(T d) : data(d), next(nullptr), prev(nullptr) {}
    ~listNode() {
        delete prev;
        delete next;
    }
};

template <class T>
class linkedList {
    listNode<T>* root;
    listNode<T>* leaf;
    listNode<T>* pos;
public:
    linkedList() : root(nullptr), leaf(nullptr), pos(nullptr) {}
    listNode<T>* begin() {
        return root;
    }
    void push(T d) {
        listNode<T>* n = new listNode(d);
        leaf->next = n;
        leaf=n;
        if (pos==nullptr) pos=n;
    }
    void del(listNode<T>* n) {
        if (n->prev!=nullptr) {
            n->prev->next=n->next;
        }
        if (n->next!=nullptr) {
            n->next->prev=n->prev;
        }
        delete n;
    }
    void next() {
        pos=pos->next;
    }
    void prev() {
        pos=pos->prev;
    }
    void gotobegin() {
        pos=root;
    }
    void gotoend() {
        pos=leaf;
    }
    ~linkedList() {
        delete root;
        delete leaf;
        delete pos;
    }
};

#endif //FUNC_COMPOSER_LINKEDLIST_H
