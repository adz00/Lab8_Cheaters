#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "hash.h"

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main(int argc, char *argv[])
{

    int chunkSize = atoi(argv[2]);
    vector<string> chunk = vector<string>();
    string currentWord;
    string currentChunk;
    ifstream currentFile;

    string dir = string(argv[1]);
    vector<string> files = vector<string>();
    string path;

    getdir(dir,files);

    HashTable table;
    int comp[files.size()][files.size()];
    for (int i=0; i<files.size(); i++) {
        for (int j=0; j<files.size(); j++) {
            comp[i][j] = 0;
        }
    }

    for (unsigned int i=0; i<files.size(); i++) {
        path = dir + "/" + files[i];
        currentFile.open(path);
        if (currentFile.is_open()) {
            while (currentFile >> currentWord) {
                if (chunk.size() == chunkSize) {
                    chunk.erase(chunk.begin());
                }
                chunk.push_back(currentWord);
                if (chunk.size() == chunkSize) {
                    currentChunk = "";
                    for (int j = 0; j < chunk.size(); j++) {
                        currentChunk += chunk.at(j) + " ";
                    }
                }
                table.insertNode(currentChunk, i);
                vector<int> x = table.find(currentChunk);
                for (int it=0; it<x.size(); it++) {
                    if (x[it]!=i) {
                        comp[i][x[it]]++;
                    }
                }
            }
        }
        currentFile.close();
    }

    int chunkLimit = atoi(argv[3]);

    for (int i=0; i<files.size(); i++) {
        for (int j=0; j<files.size(); j++) {
            if (comp[i][j] >= chunkLimit) {
                cout << comp[i][j] << ", " << files[i] << ", " << files[j] << endl;
            }
        }
    }

    return 0;
}