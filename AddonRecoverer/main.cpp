#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <direct.h>
#include <stdio.h>
#include <windows.h>

int main()
{
    namespace fs = std::filesystem; //making stuff more compact

    char result[MAX_PATH]; //buffer to following method
    std::string pathStr = std::string(result, GetModuleFileName(NULL, result, MAX_PATH)); //get a string to the exe
    fs::path currPath = pathStr.substr(0, pathStr.find_last_of('\\') + 1); //remove the exe from the path, we want the dir

    int count = 0; //keeping track of the backup files 

    for (auto& dirEntry : fs::recursive_directory_iterator(currPath)) { //iterate through all of the files and files of subdirectories
        fs::path p = dirEntry.path(); //path to the file currently being iterated
        fs::path ext = p.extension(); //its extension

        if (ext == ".bak") { //if a backup file was found
            fs::path luaP = p.string().substr(0, p.string().find_last_of(".")); //getting the path to our non-backup .lua file

            if (fs::exists(luaP)) {
                fs::remove(luaP);
            }

            fs::rename(p, luaP);

            count++; //add to the counter 
        }
    }

    printf("Found %d backup files, your settings have been restored.\nPress any key to stop the program.", count); //to let the user know the program exectuted properly
    std::cin.get(); //pause

    return 0;
}