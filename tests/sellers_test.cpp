#include "../src/sellers.hpp"
#include "../src/file_reader.hpp"
#include <iostream>

using namespace std;

void sampleTesting(){
    std::string text = "This is the 100th Etext file presented by Project Gutenberg, and";
    std::string pat = "love";
    int err = 2;

    Sellers s(pat, err);

    s.search(text, false);

    cout << s.count() << endl;
}

void textfileTest(){
    string textfile = "files/sheakespeare.txt";
    string pat = "love";
    int distance = 2;

    FileReader fr(textfile);
    std::string line;

    Sellers s(pat, distance);
    int ret = fr.getLine(line);
    int res;
    int count =0;
    bool lineCounted = false;
    string fullline = "";

    do
    {
        fullline += line;
        
        res = s.search(line, (ret == 0));
        
        if (res && !lineCounted) {
            count++;
            lineCounted = true;
        }

        if (ret == 0 && lineCounted) cout << fullline << endl;

        if (ret == 0) {
            fullline = "";
            lineCounted = false;
        }
        ret = fr.getLine(line);
        
    } while (ret != -1);

    cout << count << endl;
}

int main(int argc, char const *argv[])
{
    textfileTest();
    return 0;
}

