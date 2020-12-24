#include <Utils/sys_call.h>
#include<iostream>

//Make system call to with command = cmd. And return answer as a string
std::string sys_call(const char* cmd) {
    try{
        char buffer[128];
        std::string result = "";
        FILE* pipe;
            pipe = popen(cmd, "r");
        try {
            if (!pipe) throw std::runtime_error("popen() failed!");
            if(fgets(buffer, sizeof buffer, pipe) != NULL) {
                result += buffer;
            }
        } catch (...) {
            pclose(pipe);
            throw;
        }
        pclose(pipe);
        return result;
    } catch (...)
    {
        std::cout <<"Error popen!";
    }
}
