#ifndef LEARNINGSFML_BIRDGAME_VARIABLES_H
#define LEARNINGSFML_BIRDGAME_VARIABLES_H

#include "../devices/ConfigLinkManager.h"


inline class Variables : public ConfigLinkManager {
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

    Variables() : ConfigLinkManager("bird_game.json") {
        link("bird.gravity", bird.gravity, 3000);
        link("bird.height", bird.height, 60);
        link("bird.jump_height", bird.jump_height, 120);
        link("bird.position", bird.start_x, 300);
        link("bird.width", bird.width, 80);

        link("pipes.offset_y", pipe.offset_y, 60);
        link("pipes.spacing_x", pipe.spacing_x, 290);
        link("pipes.spacing_y", pipe.spacing_y, 220);
        link("pipes.speed", pipe.speed, 280);
        link("pipes.width", pipe.width, 180);
    };
} bg;


#endif //LEARNINGSFML_BIRDGAME_VARIABLES_H
