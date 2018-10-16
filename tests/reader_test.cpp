#include <iostream>
#include <string>
#include "../src/file_reader.hpp"

using namespace std;


int main(){
    string file = "files/sheakespeare.txt";
    FileReader fr;
    fr.load(file);
    string l;

    int ret = fr.getLine(l);

    do{
        if (ret == 1) cout << l;
        else cout << l << endl;

        ret = fr.getLine(l);
        
    } while (ret != -1);

    return 0;
}