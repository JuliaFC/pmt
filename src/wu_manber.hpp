#ifndef WU_MANBER
#define WU_MANBER

#include <vector>
#include <unordered_map>
#include <iostream>
#include "searcher.hpp"

class WuManber : public Searcher
{
private:
    std::string _pattern;
    std::vector<char> _alphabeth;
    std::unordered_map<char, uint_fast64_t > _charMask;
    std::vector < uint_fast64_t > _s;
    int _count;
    int _distance;
    int _readedCount;

    std::unordered_map<char, uint_fast64_t > buildCharMask(std::string pattern, std::vector<char> alphabeth) {
        const int m = pattern.size();
        std::unordered_map< char, uint_fast64_t > c;

        for (int i = 0; i < alphabeth.size(); i++)
        {
            c[alphabeth[i]] = ~0ull;
        }

        uint_fast64_t pos_mask =  ~1ull;

        uint_fast64_t one =  1ull;

        for (int i = 0; i < m; i++) {
            c[pattern[i]] = c[pattern[i]] & pos_mask;
            pos_mask = pos_mask << 1;
            pos_mask = pos_mask | one;
        }

        for(int i=0; i < m; i++){
            for(int j=0; j < 65; j++){
                std::cout << ((c[pattern[i]] & (1ull << j)) == (1ull << j));
            }

            std::cout << std::endl;
            
        }

        return c;
    }

public:
    
    WuManber(const std::string &pattern, std::vector<char> alphabeth, int distance){
        this->setPattern(pattern, alphabeth, distance);
    };

    WuManber(){};
    ~WuManber(){};

    void setPattern(const std::string &pattern, std::vector<char> alphabeth, int distance){
        _pattern = pattern;
        _alphabeth = alphabeth;
        _count = 0;
        _charMask = this->buildCharMask(_pattern, _alphabeth);
        _distance = distance;
        _readedCount = 0;
    ;}

    bool search(std::string text, bool isCompleteLine){
        int n = text.size();
        int m = _pattern.size();
        bool ans = false;
        
        if (_s.empty()){
            _s = std::vector< uint_fast64_t >(_distance + 1, ~0ull);

            for (int i = 1; i <= _distance; i++) {
                _s[i] = _s[i - 1] << 1;
            }
        }
        
        uint_fast64_t sprev;
        uint_fast64_t sprev2;

        uint_fast64_t msk = 1ULL << (m - 1);

        
        for (int i = 0; i < n; i++) {

            sprev = _s[0];

            _s[0] = (_s[0] << 1) | _charMask[text[i]];

            for (int j = 1; j < _distance + 1; j++) {
                sprev2 = _s[j];
                _s[j] = ((_s[j] << 1) | _charMask[text[i]]) & (_s[j - 1] << 1) & (sprev << 1) & sprev;
                sprev = sprev2;
            }

            if (!_s[_distance] & msk) {
                _count++;
                ans = true;
            }               
        }

        if (isCompleteLine){
            _s = std::vector< uint_fast64_t >(_distance + 1, ~0ull);
            for (int i = 1; i <= _distance; i++) {
                _s[i] = _s[i - 1] << 1;
            }
            _readedCount = 0;
        } else _readedCount += n;

        return ans;
    };

    void reset(){
        _pattern.clear();
        _alphabeth.clear();
        _count =0;
        _distance = 0;
        _charMask.clear();
        _s.clear();
    }
    
    int count(){
        return _count;
    };

    void resetPattern(std::string pattern){
        this->reset();
        this->setPattern(pattern, _alphabeth, _distance);
    }
};

#endif
