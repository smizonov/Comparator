#include<algorithm>
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<utility>
#include <Render/rendering.h>

//Build map where key - size of files, value - pair of vectors with the same files size
//first vector - files from path1, second - from path2
Candidates processing_file(const std::string& path1, const std::string& path2)
{
    Sorted_files dir1 = render_directory(path1),
                 dir2 = render_directory(path2);
    Candidates candidates; //next step join vectors with the same size
    for(auto it_dir1 = dir1.begin(), it_dir2 = dir2.begin();
             it_dir1!= dir1.end() && it_dir2!= dir2.end();)
    {
        if(it_dir1->first == it_dir2->first)
        {
            candidates[it_dir1->first] = make_pair(std::move(it_dir1->second), std::move(it_dir2->second));
            it_dir1++;
            it_dir2++;
        } else if(it_dir1->first < it_dir2->first)
            it_dir1++;
        else if(it_dir1->first > it_dir2->first)
            it_dir2++;
    }
    dir1.clear();
    dir2.clear();
    return candidates;
}

//Build map where key - size of files, value - vector of files with the same size
Sorted_files render_directory(const std::string& path)
{
    std::vector<fs::path> all_files;
    try {
        all_files = get_file_list(path);
    } catch (fs::filesystem_error)
    {
        std::cerr << path << ": No such directory!\n";
        exit(1);
    }

    Sorted_files size_to_files;
    for(auto& i:all_files)
    {
        size_to_files[fs::file_size(path / i)].push_back(i);
    }
    all_files.clear();
    return size_to_files;
}

//Get path and return vector of files names
std::vector<fs::path> get_file_list(const std::string& path)
{
    std::vector<fs::path> file_list;

            fs::path apk_path(path);
            for (fs::directory_iterator i(apk_path); i != fs::directory_iterator(); ++i)
            {
                if(!is_directory(i->path()))
                    file_list.push_back(i->path().filename());
                else
                    continue;
            }


    return file_list;
}


