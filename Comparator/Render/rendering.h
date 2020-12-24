#ifndef RENDERING_DIRECTORY_H
#define RENDERING_DIRECTORY_H

#include<types.h>

std::vector<fs::path> get_file_list(const std::string& path);
std::map<uint64_t, std::vector<fs::path>> render_directory(const std::string& path);

Candidates processing_file(const std::string& path1, const std::string& path2);
Sorted_files render_directory(const std::string& path);
std::vector<fs::path> get_file_list(const std::string& path);

#endif // RENDERING_DIRECTORY_H
