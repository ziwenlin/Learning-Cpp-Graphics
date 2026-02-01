#include "FileHandler.h"

#include <fmt/format.h>

bool FileHandler::setPath(const char *path) {
    if (path_file != nullptr) {
        fmt::println("Can only change path once.");
        return false;
    }
    path_file = path;
    return true;
}

bool FileHandler::read(std::string &data) {
    ix_file.open(path_file);
    if (path_file == nullptr) {
        fmt::print("Failed loading. No path has been set.");
        return false;
    }
    if (ix_file.fail()) {
        fmt::print("Failed reading file: {}\n", path_file);
        return false;
    }
    std::string ix_data;
    while (std::getline(ix_file, ix_data)) {
        data.append(ix_data);
    }
    ix_file.close();
    return true;
}

bool FileHandler::write(const char *data) {
    ox_file.open(path_file);
    if (!ox_file.fail()) {
        fmt::print("Failed writing file: {}\n", path_file);
        return false;
    }
    ox_file << data << std::endl;
    ox_file.close();
    return true;
}
