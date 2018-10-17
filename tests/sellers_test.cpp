#include "../src/sellers.hpp"
#include "../src/file_reader.hpp"
#include <iostream>

using namespace std;

void sampleTesting(){
    std::string text = "abad";
    std::string text2 = "ac";
    std::string pat = "cada";
    int err = 2;

    Sellers s(pat, err);

    s.search(text, false);
    s.search(text2, true);

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
    do
    {
        s.search(line, (ret != 1));
        ret = fr.getLine(line);
    } while (ret != -1);

    cout << s.count() << endl;
}

int main(int argc, char const *argv[])
{
    textfileTest();
    return 0;
}

