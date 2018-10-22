/**
 * @file boyer_moore.hpp
 * @author Junior Lima (junior.lima.ivd.2@gmail.com)
 * @brief Implements the Boyer Moore Algorithm for exact string matching
 * @version 0.1
 * @date 2018-10-18
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include "searcher.hpp"


class BoyerMoore : public Searcher
{
private:

    /**
     * @brief Stores the information about the bad char rule of Boyer Moore Algorithm.
     *
     */
    std::unordered_map <char, int> _c;

    /**
     * @brief Stores the information about the bad suffix rule of Boyer Moore Algorithm.
     *
     */
    std::vector<int> _s;

    /**
     * @brief String to be seached
     *
     */
    std::string _pattern;

    /**
     * @brief Set of valid characters in the text
     *
     */
    std::vector<char> _alphabeth;

    /**
     * @brief Stores the end of last text processed to possibly partial processing with Boyer Moore
     *
     */
    std::string _lineprefix;

    /**
     * @brief Counts the number words of matches in the text.
     *
     */
    int _count;

    /**
     * @brief Stores how many caracters was readed in the line.
     *        Its useful to get the position of a match where a line
     *        is feeded into the alrogithm partially.
     *
     */
    int _readedCount;

    /**
     * @brief Builds a map<char, int> that works as a lookup table of the Bad Char rule.
     *        For each unique char c in the pattern, the map stores the position of the last
     *        Occourence of c in the pattern.
     *
     * @param pattern String to be searched
     * @param alphabeth Set of valid characters
     * @return std::unordered_map<char, int> The builded lookup table
     */
    std::unordered_map<char, int> buildBadChar(const std::string& pattern, const std::vector<char> &alphabeth) {
        int m = pattern.size();
        int l = alphabeth.size();
        std::unordered_map<char, int> map;

        for (int i = 0; i < l; i++) map[alphabeth[i]] = -1;

        for (int i = 0; i < m; i++) map[pattern[i]] = i;

        return map;
    };

    /**
     * @brief Calculates the longest prefix that is also a suffix in the pattern
     *
     * @param pattern String to be searched
     * @return std::vector<int> Builded borded array, where each position i stores the longest
     *                          prefix of the substring 0..i
     */
    std::vector<int> border(const std::string& pattern) {
        int m = pattern.size();
        std::vector<int> next(m + 1, 0);

        int i = 1, j = 0;

        while (i + j < m) {
            while (i + j < m && pattern[i + j] == pattern[j]) {
                j++;
                next[i + j] = j;
            }

            i += std::max(1, j - next[j]);
            j = next[j];
        }

        return next;
    };

    /**
     * @brief Builds the lookup vector of good suffix using the reverse border.
     *
     * @param pattern String to be searched
     * @return std::vector<int> Builded good suffix lookup vector
     */
    std::vector<int> buildGoodSuffix(const std::string& pattern) {
        int m = pattern.size();
        std::string rev = pattern;

        reverse(rev.begin(), rev.end());

        std::vector<int> reverse_border = border(rev);
        std::vector<int> good_suffix(m + 1, m - reverse_border[m]);

        int j = 0;

        for (int l = 1; l < m + 1; l++)
        {
            j = m - 1 - reverse_border[l];
            if (good_suffix[j] > l - reverse_border[l])
                good_suffix[j] = l - reverse_border[l];
        }

        return good_suffix;
    };

public:
    /**
     * @brief Construct a new Boyer Moore object
     *
     * @param pattern String to be searched
     * @param alphabeth Set of valid characters
     */
    BoyerMoore(const std::string& pattern, std::vector<char> alphabeth){
        this->setPattern(pattern, alphabeth);
    };

    /**
     * @brief Destroy the Boyer Moore object
     *
     */
    ~BoyerMoore(){};

    /**
     * @brief Set a new Pattern object, a new alphabeth and reset the object
     *
     * @param pattern String to be searched
     * @param alphabeth Set of valid characters
     */
    void setPattern(const std::string& pattern, std::vector<char> alphabeth){
        _pattern = pattern;
        _alphabeth = alphabeth;
        _c = buildBadChar(_pattern, _alphabeth);
        _s = buildGoodSuffix(_pattern);
        _count = 0;
        _readedCount = 0;
        _lineprefix.clear();
    }

    /**
     * @brief Searches the pattern in the text accordingly to the Boyer Moore Algorithm
     *
     * @param text String where the pattern will be searched
     * @param isCompleteLine Tells if the line is complete or the rest of the line will be feeded
     *                       in the next interations
     * @return true The pattern was found
     * @return false The pattern was not found
     */
    bool search(std::string text, bool isCompleteLine) {

        if (!_lineprefix.empty()) text = _lineprefix + text;

        int n = text.size();
        int m = _pattern.size();
        int l = _alphabeth.size();

        int i = 0;
        int j = m - 1;
        bool ans = false;

        while (i <= n - m) {
            j = m - 1;
            while (j >= 0 && text[i + j] == _pattern[j])
                j -= 1;

            if (j == -1) {
                ans = true;
                _count++;
                i += _s.back();
            } else {
                i += std::max(_s[j], j - _c[text[i + j]]);
            }
        }

        if (!isCompleteLine) {
            _lineprefix = text.substr(std::max(0, n - m + 1));
            _readedCount += n - m + 1;
        } else {
            _lineprefix.clear();
            _readedCount = 0;
        }
        return ans;
    }

    /**
     * @brief Reset all attributes of the object
     *
     */
    void reset() {
        _c.clear();
        _s.clear();
        _pattern = "";
        _alphabeth.clear();
        _count = 0;
    }

    /**
     * @brief Return the number of word matches in the past iterations
     *
     * @return int
     */
    int count(){
        return _count;
    }

    /**
     * @brief Reset the object and sets a new pattern
     *
     * @param pattern
     */
    void resetPattern(std::string pattern){
        _pattern = pattern;
        _c = buildBadChar(_pattern, _alphabeth);
        _s = buildGoodSuffix(_pattern);
        _count = 0;
        _readedCount = 0;
        _lineprefix.clear();
    }
};

#endif
