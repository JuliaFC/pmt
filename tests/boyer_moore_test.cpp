#include "../src/boyer_moore.hpp"
#include "../src/file_reader.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
    
    // string text = "abracadabra";
    // string txt1 = "abracada";
    // string txt2 = "bra";
    // string pat = "abra";
    //string alphabeth = "abcdefghijklmnopqrstuvwxyz -?ABCDEFGHIJKLMNOPQRSTUVXYZ1234567890:<<*[]";

    string textfile = "files/sheakespeare.txt";
    string pat = "love";
    std::vector<char> alph;

    for(int i=0; i < 256; i++) {
        alph.push_back(char(i));
    }

    FileReader fr(textfile);
    std::string line;

    BoyerMoore b(pat, alph);
    int ret = fr.getLine(line);
    do {
        b.search(line, (ret != 1));
        ret = fr.getLine(line);
    } while (ret != -1);

    cout << b.count() << endl;


    return 0;
}
