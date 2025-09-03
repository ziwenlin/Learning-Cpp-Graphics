#ifndef VARIABLES_H
#define VARIABLES_H
#include <nlohmann/json.hpp>


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

    int ptr_counter = 0;
    static constexpr int ptr_size = 100;
    float *ptr_vars[ptr_size]{};
    std::string ptr_paths[ptr_size];

public:
    Variables();

    ~Variables();

    void load();

    void save();

    void print() const;

private:
    void link(const std::string &path, float &location, float value);

    static void print_helper(nlohmann::basic_json<> j, std::string path);

    static nlohmann::basic_json<> &get_helper(nlohmann::basic_json<> &j, const std::string &path, const float &number);

    static void load_helper(nlohmann::basic_json<> &j, const std::string &path, float &number);

    static void save_helper(nlohmann::basic_json<> &j, const std::string &path, const float &number);
} bg;


#endif //VARIABLES_H
