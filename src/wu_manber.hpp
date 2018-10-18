#ifndef WU_MANBER
#define WU_MANBER

#include <vector>
#include <unordered_map>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include "searcher.hpp"

class WuManber : public Searcher
{
private:
    std::string _pattern;
    std::vector<char> _alphabeth;
    std::unordered_map<char, boost::dynamic_bitset<> > _charMask;
    std::vector < boost::dynamic_bitset<> > _s;
    int _count;
    int _distance;
    int _readedCount;

    std::unordered_map<char, boost::dynamic_bitset<> > buildCharMask(std::string pattern, std::vector<char> alphabeth) {
        const int m = pattern.size();
        std::unordered_map< char, boost::dynamic_bitset<> > c;

        for (int i = 0; i < alphabeth.size(); i++)
        {
            c[alphabeth[i]] = boost::dynamic_bitset<>(m, ~0ul);
        }

        boost::dynamic_bitset<> pos_mask(m, ~1ul);

        boost::dynamic_bitset<> one(m, 1ul);

        for (int i = 0; i < m; i++) {
            c[pattern[i]] = c[pattern[i]] & pos_mask;
            pos_mask = pos_mask << 1;
            pos_mask = pos_mask | one;
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
            _s = std::vector< boost::dynamic_bitset<> >(_distance + 1, boost::dynamic_bitset<>(m, ~0));

            for (int i = 1; i <= _distance; i++) {
                _s[i] = _s[i - 1] << 1;
            }
        }
        
        boost::dynamic_bitset<> sprev(m);
        boost::dynamic_bitset<> sprev2(m);

        
        for (int i = 0; i < n; i++) {

            sprev = _s[0];

            _s[0] = (_s[0] << 1) | _charMask[text[i]];

            for (int j = 1; j < _distance + 1; j++) {
                sprev2 = _s[j];
                _s[j] = ((_s[j] << 1) | _charMask[text[i]]) & (_s[j - 1] << 1) & (sprev << 1) & sprev;
                sprev = sprev2;
            }

            if (_s[_distance][m - 1] == 0) {
                _count++;
                ans = true;
            }               
        }

        if (isCompleteLine){
            _s = std::vector< boost::dynamic_bitset<> >(_distance + 1, boost::dynamic_bitset<>(m, ~0));
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