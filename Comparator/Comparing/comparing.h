#ifndef COMPARING_DIR_H
#define COMPARING_DIR_H

#include <Utils/sys_call.h>
#include <Render/rendering.h>
#include <types.h>

Answer compare_manager(const std::string& path1, const std::string& path2);
Answer compare_files(Candidates&& candidat, const std::string& path1, const std::string& path2);
std::string calculate_checksum(fs::path path);

#endif // COMPARING_DIR_H
