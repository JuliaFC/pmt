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
        return int(a != b);
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
        bool ans = false;

        if(_dp.empty()) {
            _dp = std::vector<std::vector<int>>(2, std::vector<int>(m + 1, 0));

            for (int i = 0; i < 2; i++) {
                for (int j = 0; j <= m; j++) {
                    _dp[i][j] = j;
                }
            }

            _last = 1;
            _prev = 0;
        }

        for (int i = 0; i < n; i++) {
            _dp[_last][0] = 0;

            for (int j = 1; j <= m; j++) {
                _dp[_last][j] = std::min(_dp[_prev][j - 1] + this->phi(_pattern[j - 1], text[i]), _dp[_prev][j] + 1);
                _dp[_last][j] = std::min(_dp[_last][j - 1] + 1, _dp[_last][j]);
            }
            
            if (_dp[_last][m] <= _distance) {
               _count++;
               ans = true;
            }
            
            _last = (_last + 1) % 2;
            _prev = (_prev + 1) % 2;
        }

        if(isCompleteLine) {
            _dp = std::vector<std::vector<int>>(2, std::vector<int>(m + 1, 0));

            for (int i = 0; i < 2; i++) {
                for (int j = 0; j <= m; j++) {
                    _dp[i][j] = j;
                }
            }

            _last = 1;
            _prev = 0;
            _readedCount = 0;
        } else {
            _readedCount += n;
        }

        return ans;
    };

    int count(){
        return _count;
    }
};

