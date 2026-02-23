#pragma once
#include <iostream>
#include <fstream>
#include "Nodo.h"
#include "File.h"

class Table {
private:
    Nodo<File>* first = nullptr;
    Nodo<File>* second = nullptr;
    Nodo<File>* third = nullptr;
    std::ifstream inFile;
    std::ofstream outFile;
    std::string FNFirst;
    std::string FNSecond;
    std::string FNThird;

public:
    Table();
    Table(std::string newFNfirst, std::string newFNSecond, std::string newFNThird);
    ~Table();

    void inFileFirst();
    void addFirstN(Nodo<File>* newNodo);
    void inFileSecond();
    void addSecondN(Nodo<File>* newNodo);
    void inFileThird();
    void addThirdN(Nodo<File>* newNodo);

    void addToFirstOrdererByScore(File* newFile);
    void addToSecondOrdererByScore(File* newFile);
    void addToThirdOrdererByScore(File* newFile);
    void renumber(Nodo<File>* current);

    void saveFirst();
    void saveSecond();
    void saveThird();
    
    File* getFileByIndexFi(std::string id);
    File* getFileByIndexSe(std::string id);
    File* getFileByIndexTh(std::string id);

    void deleteListRecursive(Nodo<File>* current);
};