#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <ostream>


using namespace std;
#define MAXCHAR 256

int GetMaxLength(std::vector<string> patterns){

  int res = 0;
  for(auto p : patterns){
    res +=p.length();
  }
  return res;
}

void BuildFail(std::vector<vector<int>> &go2, std::vector<int> &occ, std::vector<int> &fail){

std::queue<int> q;
int state;

for(int i=0; i<MAXCHAR; i++){
  if(go2[0][i] != 0){

    fail[go2[0][i]] = 0;
    q.push(go2[0][i]);
  }
}
while(!q.empty()){
      state = q.front();
      q.pop();

      for(int ch=0; ch<MAXCHAR; ch++){

         if(go2[state][ch] != -1){
            int f = fail[state];

            while(go2[f][ch] == -1){
               f = fail[f];
             }

            f = go2[f][ch];
            fail[go2[state][ch]] = f;

            occ[go2[state][ch]] |= occ[f];
            q.push(go2[state][ch]);
         }
      }
}

}


void BuildFSM(const std::vector<string> &patterns, std::vector<vector<int>> &go2, std::vector<int> &occ){

int state = 1, max_length = GetMaxLength(patterns);

  for(int i=0; i<patterns.size(); i++){
    int cur = 0, idx;
    for(int j=0; j<patterns[i].length(); j++){
        idx = patterns[i][j] - '0' + 26;

        if(go2[cur][idx] == -1){
          go2[cur][idx] = state++;
        }
        cur = go2[cur][idx];
    }
    occ[cur] = occ[cur] |(1 << i);

  }

  for(int i=0; i<MAXCHAR; i++){
    if(go2[0][i] == -1){
      go2[0][i] = 0;
    }
  }
}

int Go2Next(const std::vector<vector<int>> &go2, const std::vector<int> &fail, const char &ch, int state){

int idx = ch - '0' + 26, st = state;
  while(go2[st][idx] == -1){
    st = fail[st];
  }
  return go2[st][idx];

}

void PrintGo2(vector<vector<int>> &go2){
  for(int i=0; i<MAXCHAR; i++){
    for(int j=0; j<MAXCHAR; j++){
      printf("%d", go2[i][j]);
  }
  printf("\n" );
}
}

void PrintFail(vector<int> &fail){
  for(int i=0; i<fail.size(); i++){

      printf("%d\n", fail[i]);}
}


void AhoCorasick(const std::string &text, const std::vector<string> &patterns, std::vector<int> &res){

std::vector<vector<int>> go2;
std::vector<int> occ;
std::vector<int> fail;

int state = 0, max_length = GetMaxLength(patterns);

for(int i=0; i<max_length; i++){
  go2.push_back(vector<int>(MAXCHAR, -1));
}
occ.assign(max_length, 0);
fail.assign(max_length, -1);

BuildFSM(patterns, go2, occ);
//PrintGo2(go2);
BuildFail(go2, occ, fail);
//PrintFail(fail);

for(int i=0; i<text.size(); i++){

  state = Go2Next(go2, fail, text[i], state);
  if(occ[state] == 0)
    continue;

  for (int j = 0; j < patterns.size(); j++){
    if (occ[state] & (1 << j)){
      //cout << "found: " << patterns[j] << " at " << i-patterns[j].size()+1 << endl;
              res[j]++;
    }
  }
}
return;
}


int main(){
  std::string text = "She sells seashells by the seashore.The shells she sells are surely seashells.So if she sells shells on the seashore,I'm sure she sells seashore shells.";
  std::vector<string> patterns  = {"he", "she", "hers", "his"};
  std::vector<int> res(patterns.size(), 0);

  AhoCorasick(text, patterns, res);

  cout << "case sensitive algorithm" << endl;
  for(int i=0; i<patterns.size(); i++){
    cout << res[i] << " occurences of " << patterns[i] << endl;
  }

    return 0;
}
