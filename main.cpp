#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

std::map<std::pair<char, char>, int> getFrequencies(const std::string& str) {
    std::map<std::pair<char, char>, int> frequencies;
    for (size_t i = 0; i < str.size() - 1; ++i) {
        frequencies[std::make_pair(str[i], str[i + 1])]++;
    }
    return frequencies;
}

std::pair<char, char> getMaxFrequencyPair(const std::map<std::pair<char, char>, int>& frequencies) {
    return std::max_element(frequencies.begin(), frequencies.end(),
        [](const auto& p1, const auto& p2) {
            return p1.second < p2.second;
        })->first;
}

std::string replaceMaxFrequencyPair(std::string str, const std::pair<char, char>& pair) {
    std::string newStr;
    // std::string newChar;
    // newChar += pair.first;
    // newChar += pair.second;
    char newChar = pair.first + pair.second;
    std::cout << "Replacing " << pair.first << pair.second << " with " << newChar << std::endl;
    for (size_t i = 0; i < str.size(); ++i) {
        if (i < str.size() - 1 && str[i] == pair.first && str[i + 1] == pair.second) {
            newStr += newChar;
            ++i;
        } else {
            newStr += str[i];
        }
    }
    return newStr;
}

std::string bytePairEncoding(std::string str) {
    while (true) {
        auto frequencies = getFrequencies(str);
        auto maxFrequencyPair = getMaxFrequencyPair(frequencies);
        if (frequencies[maxFrequencyPair] <= 1) {
            break;
        }
        str = replaceMaxFrequencyPair(str, maxFrequencyPair);
    }
    return str;
}

int min_edit_distance(const std::string& str1, const std::string& str2) {
    std::vector<std::vector<int>> dp(str1.size() + 1, std::vector<int>(str2.size() + 1, 0));
    // for each row, delete cost of D(i, 0) = i
    for (size_t i = 0; i <= str1.size(); ++i) {
        dp[i][0] = i;
    }
    // for each column, insert cost of D(0, j) = j
    for (size_t j = 0; j <= str2.size(); ++j) {
        dp[0][j] = j;
    }
    for (size_t i = 1; i <= str1.size(); ++i) {
        for (size_t j = 1; j <= str2.size(); ++j) {
            // insertion or deletion with respect to str1
            // if with respect to str2, the insertion and deletion will be exchanged
            // but the cost is the same, so either understanding is fine

            // from D(i, j - 1) to D(i, j), means consider an additional character in str2: str2[j]
            // insert str2[j] to str1
            int insertion = dp[i][j - 1] + 1;
            // from D(i - 1, j) to D(i, j), means consider an additional character in str1: str1[i]
            // delete str1[i] from str1
            int deletion = dp[i - 1][j] + 1;
            int match = dp[i - 1][j - 1];
            int mismatch = dp[i - 1][j - 1] + 1;
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = std::min({insertion, deletion, match});
            } else {
                dp[i][j] = std::min({insertion, deletion, mismatch});
            }
        }
    }
    return dp[str1.size()][str2.size()];
}

int main() {
    // std::string str = "aaa_ bdaa_ abac_";
    // std::string encodedStr = bytePairEncoding(str);
    // std::cout << "Encoded string: " << encodedStr << std::endl;

    std::string str1 = "intention";
    std::string str2 = "execution";
    std::cout << "Min edit distance: " << min_edit_distance(str1, str2) << std::endl;

    return 0;
}