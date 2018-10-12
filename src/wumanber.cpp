#include "/Users/juniorlima/stdc++.h"


using namespace std;

unordered_map< char, bitset > char_mask(string pattern, vector<char> alphabeth) {
    int m = pattern.size();
    unordered_map<char, bitset > c;
    
    for (int i=0; i < alphabeth.size(); i++){
        c[alphabeth[i]] = bitset<m>{}.set();
    }
    
    bitset<m> pos_mask;
    pos_mask.set();
    pos_mask[0] = 0;
    
    bitset<m> one;
    one[0] = 1;
    
    for (int i=0; i<m; i++) {
        c[pattern[i]] = c[pattern[i]] &= pos_mask;
        pos_mask = pos_mask <<= 1;
        pos_mask = pos_mask |= one;
    }
    
    return c;
}


vector<int> wu_manber(string text, string pattern, vector<char> alphabeth, int distance) {
    int n = text.size();
    int m = pattern.size();
    unordered_map<char, bitset> c = char_mask(pattern, alphabeth);
    vector < bitset<m> > S;
    
    for(int i=0; i < distance+1; i++) {
        S[i] = bitset<m>{}.set();
    }
    
    vector<int> occ;
    bitset<m> sprev;
    bitset<m> sprev2;
    
    for(int i=0; i<n; i++) {
        S[0] = (S[0] <<= 1) |= C[text[j]];
        sprev = S[0];
        for (int j =0; j < distance+1; j++) {
            sprev2 = S[j];
            S[j] = ( (S[j] <<= 1) |= c[text[j]] ) &= (S[j-1] <<= 1) &= (sprev <<= 1) &= sprev;
            sprev = sprev2;
        }
        
        if (S[distance][0] == 0)
            occ.push_back(j);
    }
    
    return occ;
}

int main() {
    
    string txt = "abadac";
    string pattern = "cada"
    string alphabeth = "abcd";
    int distance = 2;
    std::vector<char> alph(alphabeth.begin(), alphabeth.end());
    
    std::vector<int> occ = wu_manber(text, pattern, alph, distance);
    
    for(int i=0; i < occ.size(); i++) {
        cout << "found in position: " << occ[i] << endl;
    }
    
    return 0;
}







