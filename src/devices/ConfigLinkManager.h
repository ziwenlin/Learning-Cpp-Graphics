#ifndef LEARNINGSFML_CONFIG_LINK_MANAGER_H
#define LEARNINGSFML_CONFIG_LINK_MANAGER_H
#include <string>
#include <nlohmann/json.hpp>


class ConfigLinkManager {
    const char *path_config;

    static constexpr int ptr_size = 100;

    int ptr_counter = 0;
    std::array<float *, ptr_size> ptr_vars{};
    std::array<const char *, ptr_size> ptr_paths{};

public:
    explicit ConfigLinkManager(const std::string &path);

    ~ConfigLinkManager();

    void load();

    void save();

    void print() const;

protected:
    void link(const std::string &path, float &location, const float &value);

private:
    static void print_helper(nlohmann::basic_json<> json, std::string path);

    static auto get_helper(nlohmann::basic_json<> &json, const std::string &path, const float &number) -> nlohmann::basic_json<> &;

    static void load_helper(nlohmann::basic_json<> &json, const std::string &path, float &number);

    static void save_helper(nlohmann::basic_json<> &json, const std::string &path, const float &number);
};


#endif //LEARNINGSFML_CONFIG_LINK_MANAGER_H
