#include "../src/wu_manber.hpp"
#include "../src/file_reader.hpp"
#include <iostream>

using namespace std;

void testSimple(){
    string txt = "abadac";
    string pat = "cada";

    std::vector<char> alph;

    for (int i = 0; i < 256; i++)
    {
        alph.push_back(char(i));
    }

    WuManber w(pat, alph, 2);

    w.search(txt, true);

    cout << w.count() << endl;
}

int main() {
    string textfile = "files/sheakespeare.txt";
    string pat = "love";
    int distance = 2;
    std::vector<char> alph;

    for (int i = 0; i < 128; i++)
    {
        alph.push_back(char(i));
    }

    FileReader fr(textfile);
    std::string line;

    WuManber w(pat, alph, distance);
    int ret = fr.getLine(line);
    int count=0;
    bool countedLine = false;
    do
    {
        bool res = w.search(line, (ret != 1));
        if(res && !countedLine) {
            count++;
            countedLine = true;
        }
        ret = fr.getLine(line);
        if(ret == 0) {
            countedLine = false;
        }
        
    } while (ret != -1);

    cout << w.count() << endl;

    //testSimple();
    return 0;
}