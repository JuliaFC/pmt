#include <bits/stdc++.h>
#include <string.h>

using namespace std;
#define MAXCHAR 256

void Enter(const std::string &pat, std::vector<vector<int>> &go2, std::vector<int> &occ, int &newstate){


  int state = 0, i = 1, idx = pat[i] - 'a';

  while(go2[state][idx] != -1){
    idx = pat[i] - 'a';
    state = go2[state][idx];
    i++;
  }

  for(int j=i; j<pat.length(); j++){

    newstate++;
    idx = pat[j] - 'a';
    go2[state][idx] = newstate;
    state = newstate;
  }
  go2.push_back(vector<int>(MAXCHAR, -1));


}

void BuildFSM(const std::vector<string> &patterns, std::vector<vector<int>> go2, std::vector<int> &occ){

cout << "in BuildFSM\n";
int newstate = 0, k = patterns.size();

for(int i=0; i<k; i++){
  Enter(patterns[i], go2, occ, newstate);
  occ[newstate] |= (1 << i);
}
for(int i=0; i<MAXCHAR; i++){
  if(go2[0][i] == -1){
    go2[0][i] = 0;
  }
}


}

void BuildFail(std::vector<vector<int>> go2, std::vector<int> &occ, std::vector<int> &fail){

cout << "in Fail\n";
std::queue<int> q;
int r, state;

for(int i=0; i<MAXCHAR; i++){
  if(go2[0][i] != 0){
    q.push(go2[0][i]);
    fail[go2[0][i]] = 0;
  }
}

while(!q.empty()){
  state = q.front();
  q.pop();

  for(int i=0; i<MAXCHAR; i++){
    if(go2[state][i] != -1){

      q.push(go2[0][i]);
      state = fail[state];

      while(go2[state][i] == -1){
        fail[state] = go2[state][i];
        occ.push_back(occ[fail[go2[0][i]]]);
      }
    }
  }
}

}

std::vector<int> AhoCorasick(const std::string &text, const std::vector<string> &patterns){

std::vector<vector<int>> go2;
std::vector<int> occ;
int state = 0, cur = 0, qtd;

go2.push_back(vector<int>(MAXCHAR, -1));
occ.push_back(0);

BuildFSM(patterns, go2, occ);

std::vector<int> fail(go2.size(), 0);
BuildFail(go2, occ, fail);

for(int i=0; i<text.size(); i++){
  cur = text[i] - 'a';
  state = go2[state][cur];
  qtd += occ[state];

  if(occ[state] != 0){
    for (int j = 0; j < patterns.size(); ++j)
        {
            if (occ[state] & (1 << j))
            {
                cout << "Word " << patterns[j] << " appears from "
                     << i - patterns[j].size() + 1 << " to " << i << endl;
            }
        }
  }
}
return occ;
}


int main(){
  std::string text = "she sells sea shells on the sea shore";
  std::vector<string> patterns  = {"he", "she", "hers", "his"};

  AhoCorasick(text, patterns);

    return 0;
}
