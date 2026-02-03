#ifndef LEARNINGSFML_CONFIGLINKMANAGER_H
#define LEARNINGSFML_CONFIGLINKMANAGER_H
#define NAMEOF(x) #x
#include <string>
#include <nlohmann/json.hpp>

#include "../system/FileHandler.h"


class ConfigLinkManager {
    FileHandler m_file;

    static constexpr int ptr_size = 100;

    int ptr_counter = 0;
    std::array<float *, ptr_size> ptr_vars{};
    std::array<const char *, ptr_size> ptr_paths{};
    std::array<const char *, ptr_size> ptr_names{};

public:
    explicit ConfigLinkManager(const char *path);

    ~ConfigLinkManager();

    void load();

    void save();

    void print();

protected:
    void link(const char *path, const char *name, float &location, const float &value);

private:
    static auto get_helper(nlohmann::basic_json<> &json, const std::string &path, const float &number) -> nlohmann::basic_json<> &;

    static void load_helper(nlohmann::basic_json<> &json, const std::string &path, float &number);

    static void save_helper(nlohmann::basic_json<> &json, const std::string &path, const float &number);
};


#endif //LEARNINGSFML_CONFIGLINKMANAGER_H
