/**
 * @file boyer_moore.hpp
 * @author Júlia Feitosa (mjfc@cin.ufpe.br)
 * @brief Implements the Aho Corasick algorithm for multiple pattern string matching
 * @version 0.3
 * @date 2018-10-20
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <algorithm>


#define MAXCHAR 256

class AhoCorasick{

private:
  std::vector<std::string> _patterns;
  std::vector<std::vector<int>> _go2;
  std::vector<int> _occ;
  std::vector<int> _count;
  std::vector<int> _fail;
  int _maxlength;

int GetMaxLength(std::vector<std::string> patterns){

  int res = 0;
  for(auto p : patterns){
    res +=p.length();
  }
  return res;
}

public:

void TestPatterns(){

	for(auto p : _patterns){
		std::cout << "[" << p << "]\n";
	}
	return;

}

void TestMaxLength(){

	std::cout<<"(" << _maxlength << ")\n";

}

void TestGo2(){

	for(int i=0; i<_maxlength; i++){
		for(int j=0; j<MAXCHAR; j++){
  			printf("%d", _go2[i][j]);
		}
		printf("\n");
	}

}

void TestFail(){

	for(int i=0; i<_maxlength; i++){
		printf("[%d] ", _fail[i]);
	}

}




  AhoCorasick(std::vector<std::string> patterns){
    _patterns = patterns;
    _maxlength = this->GetMaxLength(patterns);
    _go2 = this->BuildFSM(_patterns);
    _fail = this->BuildFail();
  }
   ~AhoCorasick(){};

std::vector<int> BuildFail(){

	std::queue<int> q;
	int state;
	std::vector<int> fail;
	fail.assign(_maxlength, -1);

	for(int i=0; i<MAXCHAR; i++){
		if(_go2[0][i] != 0){

		  fail[_go2[0][i]] = 0;
		  q.push(_go2[0][i]);
		}
	}
	while(!q.empty()){
		    state = q.front();
		    q.pop();

		    for(int ch=0; ch<MAXCHAR; ch++){

		       if(_go2[state][ch] != -1){
		          int f = fail[state];

		          while(_go2[f][ch] == -1){
		             f = fail[f];
		           }

		          f = _go2[f][ch];
		          fail[_go2[state][ch]] = f;

		          _occ[_go2[state][ch]] |= _occ[f];
		          q.push(_go2[state][ch]);
		       }
		    }
	}

	return fail;
}


std::vector<std::vector<int>> BuildFSM(const std::vector<std::string> &patterns){

int state = 1;
std::vector<std::vector<int>> go2;

_occ.assign(_maxlength, 0);

for(int i=0; i<_maxlength; i++){
  go2.push_back(std::vector<int>(MAXCHAR, -1));
}

  for(int i=0; i<patterns.size(); i++){
    int cur = 0, idx;
    for(int j=0; j<patterns[i].length(); j++){
        idx = patterns[i][j] - '0' + 26;

        if(go2[cur][idx] == -1){
          go2[cur][idx] = state++;
        }
        cur = go2[cur][idx];
    }
    _occ[cur] = _occ[cur] |(1 << i);

  }

  for(int i=0; i<MAXCHAR; i++){
    if(go2[0][i] == -1){
      go2[0][i] = 0;
    }
  }
  return go2;	
}

int Go2Next(const char &ch, int state){

  int idx = ch - '0' + 26, st = state;
  while(_go2[st][idx] == -1){
    st = _fail[st];
  }
  return _go2[st][idx];

}

void reset() {
        _occ.clear();
        _fail.clear();
        _go2.clear();
        _patterns.clear();
        _maxlength = 0;
    }

std::vector<int> count(){
  return _count;
}

void search(const std::string &text){

int state = 0;
_count.assign(_patterns.size(), 0);
for(int i=0; i<text.size(); i++){

  state = Go2Next(text[i], state);
  if(_occ[state] == 0)
    continue;

  for (int j = 0; j < _patterns.size(); j++){
    if (_occ[state] & (1 << j)){
      _count[j]++;
    }
  }
}
return;
}


 
};
