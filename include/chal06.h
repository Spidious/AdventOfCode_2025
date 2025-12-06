#ifndef AOC25_CHAL06_H
#define AOC25_CHAL06_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <regex>

using namespace std;

namespace advent
{
    /**
     * Standard challenge code entrypoint
     * @param data string file data to be read
     * @param buffer string pointer buffer for output
     * @param input optional string input
     * @return size_t status (zero on success, non-zero on fail)
     */
    size_t challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    );

    class MathProblem_1
    {
        uint64_t total;
        bool operand; // true: * || false: +

    public:
        MathProblem_1(const char c) : total(0), operand(c == '*') {}
        void apply(uint64_t n)
        {
            if (operand)
            {
                if (!total) total++;
                total *= n;
            }
            else
                total += n;
        };
        uint64_t get_total() const { return total; }

    };

    struct MathProblem_2
    {
        vector<string> data;
        int width;
        bool operand;

        MathProblem_2(const char c, const int w) : data(w, ""), width(w), operand(c == '*') {}

        int append(string s)
        {
            // s must be same width as data (Cannot assume left or right padding)
            if (s.size() != width) return 1;

            // append each character to its index in each string of data
            for (int i = 0; i < width; i++)
            {
                data[i] += s.at(i);
            }

            // success
            return 0;
        }

        uint64_t get_total() const
        {
            uint64_t total = 0;

            // Apply thet operation for each
            for (int i = width - 1; i >= 0; i--)
            {
                uint64_t val = stoull(data[i]);

                if (operand)
                {
                    if (!total) total++;
                    total *= val;
                } else
                {
                    total += val;
                }
            }

            return total;
        }
    };
}

#endif //AOC25_CHAL06_H