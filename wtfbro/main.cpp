//
//  main.cpp
//  wtfbro
//
//  Created by Jeremy Stover on 4/26/19.
//  Copyright © 2019 Jeremy Stover. All rights reserved.
//

#include "md5.h"
#include <thread>
#include <future>
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
using std::endl;
using std::cout;

std::string poop(std::string *line){
    std::string asdf = "asdhejryutsklseusti";
    return asdf;
}


bool testString(std::string solution, std::string line, int solutionLength) {
    std::string sub;
    std::string subHash;
    for(int i = 0; i < line.length(); i++){
        sub = line.substr(i, solutionLength);
        if(sub.length() < solutionLength) {
            return false;
        }
        subHash = md5(sub);
        if(subHash == solution) {
            return true;
        }
    }
    return false;
}



int getBookList (std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


int stuff() {
    
    std::clock_t begin = clock();
    std::vector<std::future<int>> futures;
    
    std::vector<std::string> unfilteredFiles = std::vector<std::string>();
    std::vector<std::string> textFiles = std::vector<std::string>();
    
    getBookList("./books", unfilteredFiles);
    
    for (unsigned int i = 0;i < unfilteredFiles.size();i++) {
        if(unfilteredFiles[i].find(".txt")) {
            textFiles.push_back(unfilteredFiles[i]);
        }
        
    }
    
   
    
    
    
    for (int i = 0; i < 4; ++i) {
        futures.emplace_back(std::async(std::launch::async, [](int param, std::vector<std::string> files, std::clock_t begin){
            bool success = false;
            std::string string;
            
            std::string content;
            std::ifstream file;
//            std::string file_contents;
//            std::vector<std::string> file_contents;
            
            std::size_t const quarterSize = files.size() / 4;
            std::vector<std::string> split(files.begin() + (quarterSize * (param)), files.begin() + (quarterSize * (param + 1)));
            
            std::string testHash = md5(" traders everywhere");
            for(int i = 0; i < split.size(); i ++) {
                if(true) {
                    file.open("./books/" + split[i]);
                    
                    while (std::getline(file, string))
                    {
                        success = testString(testHash,string, 19);
                        if(success) {
                            clock_t end = clock();
                            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
                            
                            cout << "\n Found solution in: " << elapsed_secs << " seconds." << "\n";
                        }
                    }
                    file.close();
                }
                
            }
            return 1;
        }, i, textFiles, begin));
    }
    
    for (auto &future : futures) {
        future.get();
    }
    
    clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    
    cout << "\n Parsed entire database in: " << elapsed_secs << " seconds." << "\n\n";
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "__Starting application__" << "\n\n";
    stuff();
    return 1;
}

