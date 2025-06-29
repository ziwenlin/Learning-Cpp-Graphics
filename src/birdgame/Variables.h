#ifndef VARIABLES_H
#define VARIABLES_H


inline class Variables {
public:
    static constexpr int pipe_count = 4;
    static constexpr float screen_y = 800.f;
    static constexpr float screen_x = 1280.f;

    struct Pipe {
        float speed = 400;
        float width = 200;
        float spacing_x = 400;
        float spacing_y = 250;
        float offset_y = 40;
    } pipe;

    struct Bird {
        float start_x = 300;
        float width = 40;
        float height = 25;
        float gravity = 200;
        float jump_height = 200;
    } bird;

private:
    const char *path_config = "bird_game.json";

public:
    void load();

    void save();

private:
} bg;


#endif //VARIABLES_H
