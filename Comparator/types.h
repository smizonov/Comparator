#ifndef TYPES_H
#define TYPES_H

#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;
using Candidates = std::map<uint64_t, std::pair<std::vector<fs::path>, std::vector<fs::path>>>;
using Sorted_files = std::map<uint64_t, std::vector<fs::path>>;
using Common_files = std::pair<std::vector<fs::path>, std::vector<fs::path>>;
using Answer = std::vector<Common_files>;

#endif // TYPES_H
