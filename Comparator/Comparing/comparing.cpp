#include <future>
#include <fstream>
#include <Comparing/comparing.h>

//Recieve paths of directories and return vectors of pairs with the same files
Answer compare_manager(const std::string& path1, const std::string& path2)
{
    Candidates candidates = processing_file(path1, path2);//get candidates - map size(key)
                                                          // pair of vectors - files from path1 and path2 (value)
    return compare_files(move(candidates), path1, path2); //comparing files with checksum
}

//Recive candidates and check it using checksum
Answer compare_files(Candidates&& candidat, const std::string& path1, const std::string& path2)
{
    Answer ans;
    std::vector<std::vector<std::string>> group_dir1, group_dir2;
    std::vector<std::future<Answer>> common_files;
    for(auto& i:candidat)
    {
        common_files.push_back(//single thread for each size
                    std::async([&i, &path1, &path2] {
            Answer temp_ans;
            auto &list = i.second; // next step create vector with same file in each dir

            std::map<std::string, std::vector<fs::path>> dir1_tree, dir2_tree;
            for(auto& p1:list.first)
                dir1_tree[calculate_checksum(path1/ p1)].push_back(p1);
            for(auto& p2:list.second)
                dir2_tree[calculate_checksum(path2/ p2)].push_back(p2);
            dir1_tree.erase("NULL");// Erase files
            dir2_tree.erase("NULL");// with permission denied
            for(auto it_dir1 = dir1_tree.begin(), it_dir2 = dir2_tree.begin();
                it_dir1 != dir1_tree.end() && it_dir2 != dir2_tree.end();)
            {
                if(it_dir1->first == it_dir2->first) // if checksum are equal, make pair with same files
                {
                    temp_ans.push_back(make_pair(move(it_dir1->second), move(it_dir2->second)));
                    it_dir1++;
                    it_dir2++;
                } else if(it_dir1->first < it_dir2->first)
                    it_dir1++;
                else if(it_dir1->first > it_dir2->first)
                    it_dir2++;
            }
            return temp_ans;

        })
       );
    }
    for(auto&& pairs:common_files)
    {
        auto temp(pairs.get()); // get return r-value
        ans.insert(ans.end(), make_move_iterator(temp.begin()), make_move_iterator(temp.end()));
    }
    return ans;
}
//Calculate and return checksum, or NULL if "Permission denied"
std::string calculate_checksum(fs::path path)
{
    std::string comand = "sha1sum '" + path.string() + "' 2>&1";
    std::string hash =  sys_call(comand.c_str());
    if(std::string(hash.end()-18, hash.end()) == "Permission denied\n") // Permission denied of file
        return "NULL";
    else
    {
        return std::string(make_move_iterator(hash.begin()),
                           make_move_iterator(hash.begin()+32));
    }
}


