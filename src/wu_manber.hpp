/**
 * @file wu_manber.hpp
 * @author Junior Lima (junior.lima.ivd.2@gmail.com)
 * @brief This file implements approximate string matching using 
 *        Wu Manber Algorithm.
 * @version 0.1
 * @date 2018-10-18
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef WU_MANBER
#define WU_MANBER

#include <vector>
#include <unordered_map>
#include <iostream>
#include "searcher.hpp"

class WuManber : public Searcher
{
private:
    /**
     * @brief Pattern to be searched
     * 
     */
    std::string _pattern;

    /**
     * @brief Set of valid characters in text
     * 
     */
    std::vector<char> _alphabeth;

    /**
     * @brief Stores a mask for each possible char. A mask of char 's' have the i bit equal
     *        to zero if the char 's' occour in the i position on the pattern.  
     * 
     */
    std::unordered_map<char, uint_fast64_t > _charMask;

    /**
     * @brief Shift masks. After processed with Wu Manber, it says if the pattern occour 
     *        in the i position with distance of d if the i bit of _s[d] is set to zero
     */
    std::vector < uint_fast64_t > _s;

    /**
     * @brief Counts word matches occorence
     * 
     */
    int _count;

    /**
     * @brief Stores the max distance of matches. I.e. error.
     * 
     */
    int _distance;

    /**
     * @brief Stores how many caracters was readed in the line. 
     *        Its useful to get the position of a match where a line 
     *        is feeded into the alrogithm partially.
     * 
     */
    int _readedCount;

    /**
     * @brief Builds the mask for each char in the alphabeth. See _charMask doc. for more info.
     * 
     * @param pattern The pattern to be searched
     * @param alphabeth Set of valid characters
     * @return std::unordered_map<char, uint_fast64_t > The mounted char mask
     */
    std::unordered_map<char, uint_fast64_t > buildCharMask(std::string pattern, std::vector<char> alphabeth) {
        const int m = pattern.size();
        std::unordered_map< char, uint_fast64_t > c;

        for (int i = 0; i < alphabeth.size(); i++)
        {
            c[alphabeth[i]] = ~0ull >> (64 - m);
        }

        uint_fast64_t pos_mask =  ~1ull;

        uint_fast64_t one =  1ull;

        for (int i = 0; i < m; i++) {
            c[pattern[i]] = c[pattern[i]] & pos_mask;
            pos_mask = pos_mask << 1;
            pos_mask = pos_mask | one;
        }

        return c;
    }

public:
    /**
     * @brief Construct a new Wu Manber object
     * 
     * @param pattern String to be searched
     * @param alphabeth Set of valid characters
     * @param distance Max error valid for a match
     */
    WuManber(const std::string &pattern, std::vector<char> alphabeth, int distance){
        this->setPattern(pattern, alphabeth, distance);
    };

    /**
     * @brief Destroy the Wu Manber object
     * 
     */
    ~WuManber(){};

    /**
     * @brief Set the Pattern object
     * 
     * @param pattern String to be searched 
     * @param alphabeth Set of valid characters
     * @param distance Max error valid for a match
     */
    void setPattern(const std::string &pattern, std::vector<char> alphabeth, int distance){
        if (_pattern.size() > 64) {
            printf("Error: wu-manber can't run with pattern size bigger than 64.\n");
            exit(-1);
        }
        _pattern = pattern;
        _alphabeth = alphabeth;
        _count = 0;
        _charMask = this->buildCharMask(_pattern, _alphabeth);
        _distance = distance;
        _readedCount = 0;
    ;}

    /**
     * @brief Searches the pattern in the text accordingly to the Wu Manber algorithm
     * 
     * @param text String where the pattern will be searched
     * @param isCompleteLine Tells if the line is complete or will be feeded in the next calls
     * @return true The pattern was found in the line
     * @return false The pattern was not found in the line
     */
    bool search(std::string text, bool isCompleteLine){
        int n = text.size();
        int m = _pattern.size();

        if (m > 64) {
            printf("Error: wu-manber can't run with pattern size bigger than 64.\n");
            exit(-1);
        }

        bool ans = false;
        
        if (_s.empty()){
            _s = std::vector< uint_fast64_t >(_distance + 1, ~0ull >> (64 - m));

            for (int i = 0; i <= _distance; i++) {
                _s[i] = _s[i] << 1;
                //_s[i] = (_s[i - 1] << 1) & _s[0]; das anotações
            }
        }
        
        uint_fast64_t sprev;
        uint_fast64_t sprev2;

        uint_fast64_t msk = 1ULL << (m - 1);
        
        for (int i = 0; i < n; i++) {
            
            sprev = _s[0];

            _s[0] = ((_s[0] << 1) | _charMask[text[i]]) & (~uint_fast64_t(0) >> (64 - m));

            for (int j = 1; j < _distance + 1; j++) {
                sprev2 = _s[j];
                _s[j] = ((_s[j] << 1) | _charMask[text[i]]) & (_s[j - 1] << 1) & (sprev << 1) & sprev;
                sprev = sprev2;
            }

            if (_s[_distance] < msk) {
                _count++;
                ans = true;
            }               
        }

        if (isCompleteLine){
            _s = std::vector< uint_fast64_t >(_distance + 1, ~0ull >> (64 - m));
            for (int i = 1; i <= _distance; i++) {
                _s[i] = _s[i - 1] << 1 & _s[0];
            }
            _readedCount = 0;
        } else _readedCount += n;

        return ans;
    };

    /**
     * @brief Reset all attributes in the object
     * 
     */
    void reset(){
        _pattern.clear();
        _alphabeth.clear();
        _count =0;
        _distance = 0;
        _charMask.clear();
        _s.clear();
    }
    
    /**
     * @brief Return the total number of word matches
     * 
     * @return int 
     */
    int count(){
        return _count;
    };

    /**
     * @brief Reset the object and stores the new pattern
     * 
     * @param pattern String to be searched
     */
    void resetPattern(std::string pattern){
        this->reset();
        this->setPattern(pattern, _alphabeth, _distance);
    }
};

#endif
