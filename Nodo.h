#pragma once
#include <iostream>

template <class T>
class Nodo {
private:
    Nodo<T>* next;
    T* data;

    Nodo(const Nodo&) = delete;
    Nodo& operator=(const Nodo&) = delete;

public:
    Nodo() : next(nullptr), data(nullptr) {}
    Nodo(Nodo<T>* newNext) : next(newNext), data(nullptr) {}
    Nodo(T* newData) : next(nullptr), data(newData) {}
    Nodo(Nodo<T>* newNext, T* newData) : next(newNext), data(newData) {}
    ~Nodo() {
        next = nullptr;
        data = nullptr;
    }

    void setNext(Nodo<T>* newNext) { next = newNext; }
    void setData(T* newData) { data = newData; }

    Nodo<T>* getNext() { return next; }
    T* getData() { return data; }
};