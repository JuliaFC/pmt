#include <bits/stdc++.h>
#include <string.h>

using namespace std;

int Phi(char a, char b){
  return int(a != b);
}

std::vector<int> Sellers(std::string text, std::string pattern, int err){
  int n = text.length(), m = pattern.length();
  int last = 1, prev = 0;

  std::vector<vector<int>> DP(2, std::vector<int>(m+1, 0));
  std::vector<int> ans;

  for(int i=0; i<2; i++){
    for(int j=0; j<=m; j++){
      DP[i][j] = j;
    }
  }

  for(int i=0; i<n; i++){
    DP[last][0] = 0;
    for(int j=1; j<=m; j++){
      DP[last][j] = min(DP[prev][j-1] + Phi(pattern[j-1], text[i]), DP[prev][j]+1);
      DP[last][j] = min(DP[last][j-1]+1, DP[last][j]);
    }

    if(DP[last][m] <= err){
      ans.push_back(i);
    }
    last = (last+1) % 2;
    prev = (prev+1) % 2;
  }
  
  return ans;

}

int main(){
  std::string text = "abracadabra";
  std::string pat = "abra";
  int err = 1;

  std::vector<int> occ = Sellers(text, pat, err);

  for (auto p : occ){
      std::cout << "found in position: " << p << endl;
  }

    return 0;
}
