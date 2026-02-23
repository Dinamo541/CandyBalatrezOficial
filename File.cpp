#include "File.h"

File::File() : id(""), name(""), score("") {}
File::File(std::string newId, std::string newName, std::string newScore)
: id(newId), name(newName), score(newScore) {}
File::~File() {}

void File::setId(std::string newId) { id = newId; }
void File::setName(std::string newName) { name = newName; }
void File::setScore(std::string newScore) { score = newScore; }

std::string File::getId() { return id; }
std::string File::getName() { return name; }
std::string File::getScore() { return score; }
int File::getScoreToCompare() {
    try {
        return std::stoi(score);
    }
    catch (...) {
        return 0;
    }
}