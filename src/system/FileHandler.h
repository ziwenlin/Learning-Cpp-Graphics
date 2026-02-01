#ifndef LEARNINGSFML_SYSTEM_FILE_H
#define LEARNINGSFML_SYSTEM_FILE_H
#include <fstream>


class FileHandler {
    std::ifstream ix_file;
    std::ofstream ox_file;

    const char *path_file = nullptr;

public:
    bool setPath(const char *path);

    bool read(std::string &data);

    bool write(const char *data);
};


#endif //LEARNINGSFML_SYSTEM_FILE_H
