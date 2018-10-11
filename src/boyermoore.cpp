#include <bits/stdc++.h>
#include <string.h>

using namespace std;

unordered_map<char, int> badChar(string pattern, vector<char> alphabeth) {
    int m = pattern.size();
    int l = alphabeth.size();
    unordered_map<char, int> map;
    
    for (int i=0; i < l; i++) {
        map[alphabeth[i]] = -1;
    }

    for(int i=0; i < m; i++) {
        map[pattern[i]] = i;        
    }

    return map;
}

vector<int> border(string pattern){
    int m = pattern.size();
    std::vector<int> next(m+1,0);

    int i=1,j=0;

    while(i+j < m) {
        while(i+j < m && pattern[i+j]==pattern[j]) {
            j++;
            next[i+j] = j;
        }
        i += max(1, j - next[j]);
        j = next[j];
    }

    return next;
}

vector<int> goodSuffix(string pattern) {
    int m = pattern.size();
    string rev = pattern;
    reverse(rev.begin(), rev.end());
    vector<int> reverse_border = border(rev);
    vector<int> good_suffix(m+1,m-reverse_border[m]);
    int j=0;
    for(int l=1; l < m+1; l++){
        j = m - 1 - reverse_border[l];
        if(good_suffix[j] > l - reverse_border[l])
            good_suffix[j] = l - reverse_border[l];
    }

    return good_suffix;
}

vector<int> boyerMoore(string text, string pattern, vector<char> alphabeth) {
    int n = text.size();
    int m = pattern.size();
    int l = alphabeth.size();

    unordered_map<char, int> c = badChar(pattern,alphabeth);
    
    vector<int> s = goodSuffix(pattern);

    vector<int> ans;
    int i=0;
    int j = m-1;
    
    while(i <= n-m) {
        j = m-1;
        while(j>=0 && text[i+j]==pattern[j])
            j -= 1;

        if (j == -1) {
            ans.push_back(i);
            i += s[s.size()-1];
        } else {
            i += max(s[j], j - c[text[i+j]]);
        }
    }

    return ans;
}

int main(){
    string text = "abracadabra";
    string pat = "abra";
    string alphabeth = "abcdefghijklmnopqrstuvwxyz -?ABCDEFGHIJKLMNOPQRSTUVXYZ";
    std::vector<char> alph(alphabeth.begin(), alphabeth.end());

    vector<int> occ = boyerMoore(text, pat, alph);
    
    for (auto p : occ){
        cout << "found in position: " << p << endl;
    }

    return 0;
}