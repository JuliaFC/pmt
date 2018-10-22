/**
 * @file aho_corasick.hpp
 * @author Júlia Feitosa (mjfc@cin.ufpe.br)
 * @brief Implements the Aho Corasick for multiple string matching
 * @version 0.1
 * @date 2018-10-18
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <algorithm>
#include "searcher.hpp"


class AhoCorasick : public Searcher
{

private:
  /**
   * @brief Stores the patterns to be seached
   *
   */
  std::vector<std::string> _patterns;

  /**
   * @brief Stores the "go to" lookup table
   *
   */
  std::vector<std::vector<int>> _go2;

  /**
   * @brief Set of valid characters in the text
   *
   */
	std::vector<char> _alphabet;

  /**
   * @brief Stores the occurences for each final state of the automata
   *
   */
  std::vector<int> _occ;

  /**
   * @brief The count of occurences for each pattern
   *
   */
  std::vector<int> _count;

  /**
   * @brief Stores the "fail" lookup table
   *
   */
  std::vector<int> _fail;

  /**
   * @brief Max number of states, in the worst case, one for each character in the patterns
   *
   */
  int _maxlength;

  /**
   * @brief Stores how many caracters was readed in the line.
   *        Its useful to get the position of a match where a line
   *        is feeded into the alrogithm partially.
   *
   */
  int _readedCount;

int GetMaxLength(std::vector<std::string> patterns){

  int res = 0;
  for(auto p : patterns){
    res +=p.length();
  }
  return res+1;
}

public:

  AhoCorasick(std::vector<std::string> &patterns, std::vector<char> alphabet){
    _patterns = patterns;
		_alphabet = alphabet;
    _maxlength = this->GetMaxLength(patterns);
    _go2 = this->BuildFSM(_patterns);


    _fail = this->BuildFail();
		_count.assign(_patterns.size(), 0);
    _readedCount = 0;
  }
   ~AhoCorasick(){};

std::vector<int> BuildFail(){

	std::queue<int> q;
	int state;
	std::vector<int> fail;
	fail.assign(_maxlength, -1);

	for(int i=0; i<_alphabet.size(); i++){
		if(_go2[0][i] != 0){

		  fail[_go2[0][i]] = 0;
		  q.push(_go2[0][i]);
		}
	}
	while(!q.empty()){
		    state = q.front();
		    q.pop();

		    for(int ch=0; ch<_alphabet.size(); ch++){

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
  go2.push_back(std::vector<int>(_alphabet.size(), -1));
}

  for(int i=0; i<patterns.size(); i++){
    int cur = 0, idx;
    for(int j=0; j<patterns[i].length(); j++){
        idx = (int) patterns[i][j];

        if(go2[cur][idx] == -1){
          go2[cur][idx] = state++;
        }
        cur = go2[cur][idx];
    }
    _occ[cur] = _occ[cur] |(1 << i);

  }

  for(int i=0; i<_alphabet.size(); i++){
    if(go2[0][i] == -1){
      go2[0][i] = 0;
    }
  }
  return go2;
}

int Go2Next(const char &ch, int state){

  int idx = (int)ch, st = state;

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
				_readedCount = 0;
    }

std::vector<int> wordCount(){
  return _count;
}

void resetPattern(std::string pattern){
 				_occ.clear();
        _fail.clear();
        _go2.clear();


				_readedCount = 0;
    }

int count(){
	int res = 0;
	for(auto c : _count){
		std::cout << "Total occurences: " << c << std::endl;

		res += c;
	}
  return res;
}


bool search(std::string text, bool isCompleteLine){

int state = 0, n = text.length();
bool ans = false;

for(int i=0; i<text.size(); i++){

if(text[i] >= 0 && text[i] < _alphabet.size()){
  state = Go2Next(text[i], state);
  if(_occ[state] == 0)
    continue;

  for (int j = 0; j < _patterns.size(); j++){
    if (_occ[state] & (1 << j)){
      _count[j]++;
			ans = true;
    }
  }

	if (!isCompleteLine) {
    _readedCount += n;
  } else {
    _readedCount = 0;
  }
}

}

return ans;
}

};
#endif
