#include <bits/stdc++.h>
#include <string.h>

using namespace std;


void BuildFSM(const std::vector<string> &patterns, std::vector<int> go2, std::vector<int> &occ){

int newstate = 0, k = patterns.size();

for(int i=0; i<k; i++){
  Enter(patterns[i], go2, occ, newstate);
  occ[newstate] |= (1 << i);
}


}

void Enter(const std::string &pat, std::vector<int> &go2, std::vector<int> &occ, int &newstate){
  int state = 0, i = 0, idx = pat[i] - 'a';

  while(go2[state][i] != -1){
    idx = pat[i] - 'a'
    state = go2(state, idx);
    j++;
  }

  for(int j=i; j<pat.length(); j++){
    newstate++;
    idx = pat[j] - 'a';
    go2[state][idx] = newstate;
    state = newstate;
  }


}

std::vector<int> AhoCorasick(const std::string &text, const std::vector<string> &patterns){


}

int main(){
  std::string text = "she sells sea shells on the sea shore";
  std::string patterns[] = {"he", "she", "hers", "his"};

    return 0;
}
