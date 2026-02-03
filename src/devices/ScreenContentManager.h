#ifndef LEARNINGSFML_SCREENCONTENTMANAGER_H
#define LEARNINGSFML_SCREENCONTENTMANAGER_H
#include "../system/FileHandler.h"


class ScreenContentManager {
public:
    static constexpr char CONTENTS[] = "contents";
    static constexpr char STYLES[] = "styles";

private:
    FileHandler m_file;

public:
    void setPath(const char *path);

    void load();

    void save();
};
#endif //LEARNINGSFML_SCREENCONTENTMANAGER_H
