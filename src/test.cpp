#include <bits/stdc++.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace std;

bool exists_test3(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char **argv) {
    for(int i=1; i<argc; i++) {
        printf("%s\n", argv[i]);
        cout << exists_test3(string(argv[i])) << endl;
    }
    return 0;
}