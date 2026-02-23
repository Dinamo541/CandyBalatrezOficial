#include "Table.h"

Table::Table() : FNFirst(""), FNSecond(""), FNThird("") {}
Table::Table(std::string newFNfirst, std::string newFNSecond, std::string newFNThird)
: FNFirst(newFNfirst), FNSecond(newFNSecond), FNThird(newFNThird) {
    inFileFirst();
    inFileSecond();
    inFileThird();
}
Table::~Table() {
    saveFirst();
    saveSecond();
    saveThird();
    deleteListRecursive(first);
    deleteListRecursive(second);
    deleteListRecursive(third);
}

void Table::inFileFirst() {
    std::string line;
    try {
        inFile = std::ifstream(FNFirst);
        if (inFile.is_open()) {
            size_t id = 1;
            while (std::getline(inFile, line)) {
                if (line.empty()) { ++id; continue; }

                size_t dot = line.find('.');
                if (dot == std::string::npos) { ++id; continue; }

                std::string idStr = line.substr(0, dot);

                size_t start = dot + 1;
                size_t comma1 = line.find(',', start);
                if (comma1 == std::string::npos) { ++id; continue; }
                std::string name = line.substr(start, comma1 - start);

                size_t comma2 = line.find(',', comma1 + 1);
                std::string score;
                if (comma2 == std::string::npos) score = line.substr(comma1 + 1);
                else score = line.substr(comma1 + 1, comma2 - (comma1 + 1));

                addFirstN(new Nodo<File>(new File(idStr, name, score)));
                ++id;
            }
            inFile.close();
        } else {
            throw(-1);
        }
    } catch (int error) {
        if (error == -1) {
            std::cerr << "No se pudo abrir el archivo para leer.\n";
        }
    }
}
void Table::addFirstN(Nodo<File>* newNodo) {
    if (first == nullptr) {
        first = newNodo;
    } else {
        Nodo<File>* current = first;
        while (current->getNext() != nullptr) current = current->getNext();
        
        current->setNext(newNodo);
    } 
}
void Table::inFileSecond() {
    std::string line;
    try {
        inFile = std::ifstream(FNSecond);
        if (inFile.is_open()) {
            size_t id = 1;
            while (std::getline(inFile, line)) {
                if (line.empty()) { ++id; continue; }

                size_t dot = line.find('.');
                if (dot == std::string::npos) { ++id; continue; }

                std::string idStr = line.substr(0, dot);

                size_t start = dot + 1;
                size_t comma1 = line.find(',', start);
                if (comma1 == std::string::npos) { ++id; continue; }
                std::string name = line.substr(start, comma1 - start);

                size_t comma2 = line.find(',', comma1 + 1);
                std::string score;
                if (comma2 == std::string::npos) score = line.substr(comma1 + 1);
                else score = line.substr(comma1 + 1, comma2 - (comma1 + 1));

                addSecondN(new Nodo<File>(new File(idStr, name, score)));
                ++id;
            }
            inFile.close();
        } else {
            throw(-1);
        }
    } catch (int error) {
        if (error == -1) {
            std::cerr << "No se pudo abrir el archivo para leer.\n";
        }
    }
}
void Table::addSecondN(Nodo<File>* newNodo) {
    if (second == nullptr) {
        second = newNodo;
    } else {
        Nodo<File>* current = second;
        while (current->getNext() != nullptr) current = current->getNext();
        current->setNext(newNodo);
    } 
}
void Table::inFileThird() {
    std::string line;
    try {
        inFile = std::ifstream(FNThird);
        if (inFile.is_open()) {
            size_t id = 1;
            while (std::getline(inFile, line)) {
                if (line.empty()) { ++id; continue; }

                size_t dot = line.find('.');
                if (dot == std::string::npos) { ++id; continue; }

                std::string idStr = line.substr(0, dot);

                size_t start = dot + 1;
                size_t comma1 = line.find(',', start);
                if (comma1 == std::string::npos) { ++id; continue; }
                std::string name = line.substr(start, comma1 - start);

                size_t comma2 = line.find(',', comma1 + 1);
                std::string score;
                if (comma2 == std::string::npos) score = line.substr(comma1 + 1);
                else score = line.substr(comma1 + 1, comma2 - (comma1 + 1));

                addThirdN(new Nodo<File>(new File(idStr, name, score)));
                ++id;
            }
            inFile.close();
        } else {
            throw(-1);
        }
    } catch (int error) {
        if (error == -1) {
            std::cerr << "No se pudo abrir el archivo para leer.\n";
        }
    }
}
void Table::addThirdN(Nodo<File>* newNodo) {
    if (third == nullptr) {
        third = newNodo;
    } else {
        Nodo<File>* current = third;
        while (current->getNext() != nullptr) current = current->getNext();
        current->setNext(newNodo);
    } 
}

void Table::addToFirstOrdererByScore(File* newFile) {
    if (newFile == nullptr) return;
    Nodo<File>* newNodo = new Nodo<File>(newFile);
    if (first == nullptr) {
        first = newNodo;
        renumber(first);
        return;
    }
    File* headData = first->getData();
    if (headData == nullptr || headData->getScoreToCompare() < newFile->getScoreToCompare()) {
        newNodo->setNext(first);
        first = newNodo;
        renumber(first);
        return;
    }
    Nodo<File>* current = first;
    while (current->getNext() != nullptr) {
        Nodo<File>* next = current->getNext();
        File* nextData = next ? next->getData() : nullptr;
        if (nextData == nullptr) break;
        if (nextData->getScoreToCompare() >= newFile->getScoreToCompare()) {
            current = next;
            continue;
        }
        break;
    }
    newNodo->setNext(current->getNext());
    current->setNext(newNodo);
    renumber(first);
}
void Table::addToSecondOrdererByScore(File* newFile) {
    if (newFile == nullptr) return;
    Nodo<File>* newNodo = new Nodo<File>(newFile);
    if (second == nullptr) {
        second = newNodo;
        renumber(second);
        return;
    }
    File* headData = second->getData();
    if (headData == nullptr || headData->getScoreToCompare() < newFile->getScoreToCompare()) {
        newNodo->setNext(second);
        second = newNodo;
        renumber(second);
        return;
    }
    Nodo<File>* current = second;
    while (current->getNext() != nullptr) {
        Nodo<File>* next = current->getNext();
        File* nextData = next ? next->getData() : nullptr;
        if (nextData == nullptr) break;
        if (nextData->getScoreToCompare() >= newFile->getScoreToCompare()) {
            current = next;
            continue;
        }
        break;
    }
    newNodo->setNext(current->getNext());
    current->setNext(newNodo);
    renumber(second);
}
void Table::addToThirdOrdererByScore(File* newFile) {
    if (newFile == nullptr) return;
    Nodo<File>* newNodo = new Nodo<File>(newFile);
    if (third == nullptr) {
        third = newNodo;
        renumber(third);
        return;
    }
    File* headData = third->getData();
    if (headData == nullptr || headData->getScoreToCompare() < newFile->getScoreToCompare()) {
        newNodo->setNext(third);
        third = newNodo;
        renumber(third);
        return;
    }
    Nodo<File>* current = third;
    while (current->getNext() != nullptr) {
        Nodo<File>* next = current->getNext();
        File* nextData = next ? next->getData() : nullptr;
        if (nextData == nullptr) break;
        if (nextData->getScoreToCompare() >= newFile->getScoreToCompare()) {
            current = next;
            continue;
        }
        break;
    }
    newNodo->setNext(current->getNext());
    current->setNext(newNodo);
    renumber(third);
}
void Table::renumber(Nodo<File>* current) {
    for (int i = 1; i < 11 && current != nullptr; ++i) {
        File* f = current->getData();
        if (f) f->setId(std::to_string(i));
        current = current->getNext();
    }
}

void Table::saveFirst() {
    try {
        outFile = std::ofstream(FNFirst);
        if (outFile.is_open()) {
            Nodo<File>* current = first;
            for (int i = 0 ; i < 10 && current != nullptr; i++) {
                File* file = current->getData();
                outFile << file->getId() << "." << file->getName() << "," << file->getScore();
                if (i != 9 && current->getNext() != nullptr) {
                    outFile << std::endl;
                }
                current = current->getNext();
            }
            outFile.close();
        } else {
            throw(-1);
        }
    } catch (int error) {
        if (error == -1) {
            std::cerr << "No se pudo abrir el archivo para leer.\n";
        }
    }
}
void Table::saveSecond() {
    try {
        outFile = std::ofstream(FNSecond);
        if (outFile.is_open()) {
            Nodo<File>* current = second;
            for (int i = 0 ; i < 10 && current != nullptr; i++) {
                File* file = current->getData();
                outFile << file->getId() << "." << file->getName() << "," << file->getScore();
                if (i != 9 && current->getNext() != nullptr) {
                    outFile << std::endl;
                }
                current = current->getNext();
            }
            outFile.close();
        } else {
            throw(-1);
        }
    } catch (int error) {
        if (error == -1) {
            std::cerr << "No se pudo abrir el archivo para leer.\n";
        }
    }
}
void Table::saveThird() {
    try {
        outFile = std::ofstream(FNThird);
        if (outFile.is_open()) {
            Nodo<File>* current = third;
            for (int i = 0 ; i < 10 && current != nullptr; i++) {
                File* file = current->getData();
                outFile << file->getId() << "." << file->getName() << "," << file->getScore();
                if (i != 9 && current->getNext() != nullptr) {
                    outFile << std::endl;
                }
                current = current->getNext();
            }
            outFile.close();
        } else {
            throw(-1);
        }
    } catch (int error) {
        if (error == -1) {
            std::cerr << "No se pudo abrir el archivo para leer.\n";
        }
    }
}
File* Table::getFileByIndexFi(std::string id) {
    Nodo<File>* current = first;
    while (current != nullptr && current->getData()->getId() != id) current = current->getNext();
    if (current == nullptr) return nullptr;
    return current->getData();
}
File* Table::getFileByIndexSe(std::string id) {
    Nodo<File>* current = second;
    while (current != nullptr && current->getData()->getId() != id) current = current->getNext();
    if (current == nullptr) return nullptr;
    return current->getData();
}
File* Table::getFileByIndexTh(std::string id) {
    Nodo<File>* current = third;
    while (current != nullptr && current->getData()->getId() != id) current = current->getNext();
    if (current == nullptr) return nullptr;
    return current->getData();
}

void Table::deleteListRecursive(Nodo<File>* current) {
    if (current != nullptr) {
        deleteListRecursive(current->getNext());
        delete current;
    }
}