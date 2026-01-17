#include "FileManager.h"

#include <filesystem>

#include "fmt/format.h"


FileManager::FileManager() {
}

FileManager::~FileManager() {
}

void FileManager::reload() {
    m_folder_structure.clear();
    m_file_structure.clear();
}

FileManager::ListFileNames &FileManager::request(const std::string &file_name, const std::string &source_path) {
    const std::string full_file_path = source_path + file_name;
    const auto &it = m_file_structure.find(full_file_path);
    if (it == m_file_structure.end()) {
        const ListFiles &list_files = indexFolder(source_path);
        if (list_files.empty()) {
            fmt::println("Source path '{}' does noet exist.", source_path);
            throw std::invalid_argument("Source path '" + source_path + "' does not exist.");
        }
        indexFilesAt(source_path, list_files);
        const auto &sit = m_file_structure.find(full_file_path);
        if (sit == m_file_structure.end()) {
            fmt::println("File path '{}' does not exist", full_file_path);
            throw std::invalid_argument("File path '" + full_file_path + "' does not exist.");
        }
        return sit->second;
    }
    return it->second;
}

FileManager::ListFiles &FileManager::indexFolder(const std::string &source_path) {
    const auto iterator = m_folder_structure.find(source_path);
    if (iterator != m_folder_structure.end()) {
        return iterator->second;
    }
    ListFiles &map = m_folder_structure.emplace(source_path, ListFiles()).first->second;
    for (const std::filesystem::directory_entry &entry: std::filesystem::directory_iterator(source_path)) {
        if (entry.is_directory()) {
            continue;
        }
        const std::string src_file_string = entry.path().filename().string();
        const std::size_t index_extension = src_file_string.find_last_of('.');
        const std::string src_extension = src_file_string.substr(index_extension);
        const std::string src_filename = src_file_string.substr(0, index_extension);
        map.emplace_back(src_filename, src_extension);
    }
    return map;
}

void FileManager::indexFilesAt(const std::string &source_path, const ListFiles &files) {
    for (const auto &[file_name, extension]: files) {
        int digits = 0;
        int index = file_name.length() - 1;
        for (; index >= 0; --index) {
            const char &c = file_name[index];
            if (std::isdigit(c)) {
                digits += 1;
                continue;
            }
            if (c == '_') {
                --index;
            }
            break;
        }
        const std::string &name = file_name.substr(0, index + 1);
        const std::string &source = source_path + name;
        const std::string &full_file_name = source_path + file_name + extension;
        const auto &it = m_file_structure.find(source);
        if (it == m_file_structure.end()) {
            ListFileNames file_names = {full_file_name};
            m_file_structure.emplace(source, file_names);
        } else {
            it->second.emplace_back(full_file_name);
        }
    }
}
