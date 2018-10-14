#include <vector>
#include <bitset>
#include <unordered_map>
#include <iostream>
#include <boost/dynamic_bitset.hpp>


using namespace std;
using namespace boost;

unordered_map< char, dynamic_bitset<> > char_mask(string pattern, vector<char> alphabeth) {
    const int m = pattern.size();
    unordered_map<char, dynamic_bitset<> > c;
    
    for (int i=0; i < alphabeth.size(); i++){
        c[alphabeth[i]] = dynamic_bitset<>(m, ~0ul);
    }
    
    dynamic_bitset<> pos_mask(m, ~1ul);
    
    dynamic_bitset<> one(m, 1ul);
    
    for (int i=0; i<m; i++) {
        c[pattern[i]] = c[pattern[i]] & pos_mask;
        pos_mask = pos_mask << 1;
        pos_mask = pos_mask | one;
    }

    return c;
}


vector<int> wu_manber(string text, string pattern, vector<char> alphabeth, int distance) {
    const int n = text.size();
    const int m = pattern.size();
    unordered_map<char, dynamic_bitset<> > c = char_mask(pattern, alphabeth);
    vector < dynamic_bitset<> > s(distance+1, dynamic_bitset<>(m, ~0));
    
    vector<int> occ;
    dynamic_bitset<> sprev(m);
    dynamic_bitset<> sprev2(m);

    for(int i=0; i<n; i++) {
        
        s[0] = (s[0] << 1) | c[text[i]];
        
        sprev = s[0];
        
        for (int j = 1; j < distance+1; j++) {
            sprev2 = s[j];
            s[j] = ( (s[j] << 1) | c[text[i]] )
                    & (s[j-1] << 1)
                    & (sprev << 1)
                    & sprev;
            sprev = sprev2;
        }

        if (s[distance][m-1] == 0)
            occ.push_back(i);
    }
    
    return occ;
}

int main() {
    
    string txt = "abadac";
    string pattern = "cada";
    string alphabeth = "abcd";
    int distance = 2;
    std::vector<char> alph(alphabeth.begin(), alphabeth.end());
    
    std::vector<int> occ = wu_manber(txt, pattern, alph, distance);
    
    for(int i=0; i < occ.size(); i++) {
        std::cout << "found in position: " << occ[i] << endl;
    }
    
    return 0;
}







