#include <Utils/print_utils.h>
#include <iomanip>
#include<iostream>

//Print equal files contained in ans
void print_answer(const Answer& ans, const std::string& path1, const std::string& path2)
{
    std::cout << "/nPath 1" << std::setw(path1.length()+5) << "Path 2" << std::endl;
    std::cout << std::setw(path1.length()+5)<< std::left << path1  << path2 << "\n";
    if(ans.size()==0)
    {
        std::cout << "Above directories do not have the same files or have no access to files\n";
        return;
    }

    for(auto& set_files: ans)
    {
        auto end1 = set_files.first.end();
        auto end2 = set_files.second.end();
        std::cout << "Following files are the same" << "\n";
        uint64_t file_size = fs::file_size(path1 / set_files.first.front());
        std::string file_size_str = "Files size = ";
        if (file_size < 1000u) file_size_str += std::to_string(file_size) + " bytes\n";
        else if (file_size < 1'000'000u) file_size_str += std::to_string(file_size / 1000) + " kB\n";
        else if (file_size < 1'000'000'000u) file_size_str += std::to_string(file_size / 1000'000) + " MB\n";
        else file_size_str += std::to_string(file_size / 1000'000'000) + "," + std::to_string((file_size / 100'000'000)%10) + " GB\n";
        std::cout << file_size_str;
        for(auto files1 = set_files.first.begin(), files2 = set_files.second.begin();
                 files1!= end1 || files2!= end2;)
        {
            if (files1 != end1 && files2 !=end2)
            {
                std::cout << std::left << std::setw(path1.length()+5)  << files1->string() <<  std::left << std::setw(path1.length()+5) <<
                        files2->string() << "\n";
                files1++;
                files2++;
            }
            else if(files1 != end1)
            {
                std::cout << files1->string() << "\n";
                files1++;
            }
            else if(files2 != end2)
            {
                std::cout  << std::setfill(' ') << std::setw(path1.length()+5) << ' ';
                std::cout<< std::left << std::setw(path1.length()+5) << files2->string()  << "\n";
                files2++;
            }
        }
        std::cout << std::string(path1.length(), '/') << "\n";
    }
}
