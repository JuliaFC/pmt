#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


class Sellers
{
private:
    std::string _pattern;
    int _distance;
    std::vector< std::vector<int> > _dp;
    int _last, _prev;
    int _count;
    int _readedCount;

    int phi(char a, char b) {
        return (a != b) ? 1 : 0;
    }

    int min (int a, int b, int c) {
        return std::min(a,std::min(b,c));
    }

  public:
    Sellers(std::string pattern, int distance){
        _pattern = pattern;
        _distance = distance;
        _count = 0;
        _readedCount = 0;
    };

    ~Sellers(){};

    bool search(std::string text, bool isCompleteLine) {
        int n = text.length(), m = _pattern.length();
        
        if (n == 0) {
            this->reset(m);
            return false;
        } 

        bool ans = false;

        if(_dp.empty()) this->reset(m);
        
        for (int i = 0; i < n; i++) {
            _dp[_last][0] = 0;

            for (int j = 1; j <= m; j++) {
                _dp[_last][j] = min(_dp[_prev][j-1] + phi(_pattern[j-1], text[i]),
                                    _dp[_prev][j] + 1,
                                    _dp[_last][j-1] + 1);
            }
            
            if (_dp[_last][m] <= _distance) {
               _count++;
               ans = true;
            }
            
            _last = (_last + 1) % 2;
            _prev = (_prev + 1) % 2;
        }

        if(isCompleteLine) this->reset(m);   
        else _readedCount += n;
        

        return ans;
    };

    void reset(int m){
         _dp = std::vector< std::vector<int> >(2, std::vector<int>(m + 1, 0));

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j <= m; j++) {
                _dp[i][j] = j;
            }
        }

        _last = 1;
        _prev = 0;
        _readedCount = 0;
    }

    int count(){
        return _count;
    }
};

