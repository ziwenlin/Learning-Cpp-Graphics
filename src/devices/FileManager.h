#ifndef LEARNINGSFML_FILEMANAGER_H
#define LEARNINGSFML_FILEMANAGER_H
#include <vector>
#include <string>
#include <unordered_map>


inline class FileManager {
public:
    struct File {
        const std::string name;
        const std::string extension;
    };

    typedef std::vector<File> ListFiles;
    typedef std::vector<std::string> ListFileNames;

private:
    std::unordered_map<std::string, ListFiles> m_folder_structure;
    std::unordered_map<std::string, ListFileNames> m_file_structure;

public:
    FileManager();

    ~FileManager();

    void reload();

    ListFileNames &request(const std::string &file_name, const std::string &source_path, const std::string &file_extension);

private:
    ListFiles &indexFolder(const std::string &source_path);

    void indexFilesAt(const std::string &source_path, const ListFiles &files);
} file_manager;


#endif //LEARNINGSFML_FILEMANAGER_H
