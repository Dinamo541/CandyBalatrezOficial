#pragma once
#include <iostream>
#include <string>

class File {
private:
    std::string id;
    std::string name;
    std::string score;

    File(const File&) = delete;
    File& operator=(const File&) = delete;

public:
    File();
    File(std::string newId, std::string newName, std::string newScore);
    ~File();

    void setId(std::string newId);
    void setName(std::string newName);
    void setScore(std::string newScore);

    std::string getId();
    std::string getName();
    std::string getScore();
    int getScoreToCompare();
};