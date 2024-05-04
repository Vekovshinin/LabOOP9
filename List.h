#pragma once
#include<iostream>
#include<vector>
using namespace std;
template <typename T>
struct Node
{
    T data;
    Node* next_ptr;

    void addData(T Data)
    {
        data = Data;
        next_ptr = nullptr;
    }
};
template <typename T>
struct List
{
    Node<T>* head;
    Node<T>* tail;
    int size;
    List() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }
    List(const List& a) {
        this->size = a.size;
        Node<T>* temp_ptr = head;
        for (Node<T>* i = a.head; i != nullptr; i = i->next_ptr) {
            temp_ptr->data = i->data;
            temp_ptr = temp_ptr->next_ptr;
        }
    }

    void pop_front()
    {
        if (head == nullptr) return;
        if (head == tail)
        {
            delete tail;
            head = tail = nullptr;
            return;
        }
        Node<T>* node = head;
        head = node->next_ptr;
        delete node;
        --size;
    }
    void push_back(T data)
    {
        Node<T>* node = new Node<T>;
        node->addData(data);
        if (head == nullptr) head = node;
        if (tail != nullptr) tail->next_ptr = node;
        tail = node;
        ++size;
    }
    void push_front(T data)
    {
        Node<T>* node = new Node<T>;
        node->addData(data);
        node->next_ptr = head;
        head = node;
        if (tail == nullptr) tail = node;
        ++size;
    }
    void pop_back()
    {
        if (tail == nullptr) return;
        if (head == tail)
        {
            delete tail;
            head = tail = nullptr;
            return;
        }
        Node<T>* node = head;
        for (; node->next_ptr != tail; node = node->next_ptr);
        node->next_ptr = nullptr;
        delete tail;
        tail = node;
        --size;
    }
    Node<T>* getAt(int k) {
        if (k < 0) return 0;

        Node<T>* node = head;
        int n = 0;
        while (node && n != k && node->next_ptr) {
            node = node->next_ptr;
            n++;
        }
        if (n == k) return node;
        else return nullptr;
    }
    void insert(int k, T data) {
        Node* left = getAt(k);
        if (left == nullptr) return;

        Node* right = left->next_ptr;
        Node<T>* node = new Node<T>;
        node->addData(data);

        left->next_ptr = node;
        node->next_ptr = right;
        if (right == nullptr) tail = node;
        size++;
    }
    void erase(int k) {
        if (k < 0) return;
        if (k == 0) {
            pop_front();
            return;
        }

        Node* left = getAt(k - 1);
        Node* node = left->next_ptr;
        if (node == nullptr) return;

        Node* right = node->next_ptr;
        left->next_ptr = right;
        if (node == tail) tail = left;
        delete node;
        --size;
    }

    ~List()
    {
        while (head != nullptr) pop_back();
    }

    T& operator [] (int a) {
        if (a >= size || a < 0) throw "Выход за границы списка!";
        return getAt(a)->data;
    }

    void operator () (int a) {
        if (a <= 0) throw "Ошибка создания списка";
        this->size = a;
        Node<T>* node = new Node<T>;
        head = node;
        Node<T>* temp_ptr = head;
        for (int i = 0; i < a - 1; ++i) {
            Node<T>* node = new Node<T>;
            temp_ptr->next_ptr = node;
            temp_ptr = temp_ptr->next_ptr;
        }
        tail = temp_ptr;
        temp_ptr->next_ptr = nullptr;
    }
    class iterator {
        Node<T>* it;
        int Size;
    public:
        iterator(List& a) {
            this->it = a.head;
            this->Size = a.size;
        }
        Node<T>* operator + (int b) {
            if (b >= Size || b < 0) throw "Выход за границы списка";
            Node<T>* iter = it;
            for (int i = 0; i < b; ++i)
                iter = iter->next_ptr;
            return iter;
        }
    };

    friend List& operator*(List& a, vector<int> b);
};
template <typename T, typename T2>
List<T>& operator*(List<T>& a, vector<T2>& b) {
    if (a.size == b.size()) {
        for (int i = 0; i < a.size; ++i) {
            a.getAt(i)->data = a.getAt(i)->data * b[i];
        }
    }
    return a;
}

