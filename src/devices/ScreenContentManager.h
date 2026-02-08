#ifndef LEARNINGSFML_SCREENCONTENTMANAGER_H
#define LEARNINGSFML_SCREENCONTENTMANAGER_H

#include "../gui/GridFrame.h"
#include "../gui/RoundedButton.h"
#include "../gui/RoundedStatusBar.h"
#include "../system/FileHandler.h"


class ScreenContentManager : public IClickable {
    static constexpr char CONTENTS[] = "contents";
    static constexpr char STYLES[] = "styles";
    static constexpr char CONTENTS_COMPONENTS[] = "components";

protected:
    static constexpr int FRAMES_MAX = 5;
    static constexpr int ELEMENTS_MAX = 20;

private:
    FileHandler m_file;
    std::array<GridFrame, FRAMES_MAX> m_frames;
    std::array<RoundedButton, ELEMENTS_MAX> m_buttons;
    std::array<RoundedStatusBar, ELEMENTS_MAX> m_statusbars;

    int m_frame_count = 0;
    int m_button_count = 0;
    int m_statusbar_count = 0;

public:
    void setPath(const char *path);

    void load();

    void save();

    void update(const SmartMouse &mouse) override;

    void draw(sf::RenderWindow &window) const override;
};
#endif //LEARNINGSFML_SCREENCONTENTMANAGER_H
