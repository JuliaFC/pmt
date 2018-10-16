#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class BoyerMoore
{
private:
    std::unordered_map <char, int> _c;
    std::vector<int> _s;
    std::string _pattern;
    std::vector<char> _alphabeth;
    int _count;
    int _j;

    std::unordered_map<char, int> buildBadChar(const std::string& pattern, const std::vector<char> alphabeth) {
        int m = pattern.size();
        int l = alphabeth.size();
        std::unordered_map<char, int> map;

        for (int i = 0; i < l; i++) map[alphabeth[i]] = -1;

        for (int i = 0; i < m; i++) map[pattern[i]] = i;

        return map;
    };

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
    BoyerMoore(const std::string& pattern, std::vector<char> alphabeth){
        this->setPattern(pattern, alphabeth);
    };

    ~BoyerMoore();

    void setPattern(const std::string& pattern, std::vector<char> alphabeth){
        _pattern = pattern;
        _alphabeth = alphabeth;
        _c = buildBadChar(_pattern, _alphabeth);
        _s = buildGoodSuffix(_pattern);
        _j = -1;
    }

    void search(const std::string& text) {
        int n = text.size();
        int m = _pattern.size();
        int l = _alphabeth.size();

        int i = 0;
        int j = m - 1;

        while (i <= n - m)
        {
            j = m - 1;
            while (j >= 0 && text[i + j] == _pattern[j])
                j -= 1;

            if (j == -1)
            {
                _count++;
                i += _s[_s.size() - 1];
            }
            else
            {
                i += std::max(_s[j], j - _c[text[i + j]]);
            }
        }

    }
    void reset();
};


