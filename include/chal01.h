#ifndef AOC25_CHAL01_H
#define AOC25_CHAL01_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <regex>
#include <array>

#define STARTING_POS 50
#define DIAL_MIN 0
#define DIAL_MAX 99

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

    // Object to better handle the dial
    class Dial
    {
        // Values to try to do this algebraically (boy what a fail)
        int pos, min, max, offset;

        // For fun
        long iter_count = 0;

        // Variables specifically to hold Part 1 and Part 2 outputs
        int part1 = 0, part2 = 0;

    public:
        // Constructor
        Dial(int def_pos, int def_min, int def_max) :
            pos(def_pos),
            min(def_min),
            max(def_max),
            offset(def_max-def_min+1)
        {
            if (pos < min || max <= min || pos > max)
            {
                throw invalid_argument("Invalid Position or Bounds on dial");
            }
        }

        // Override for += and -= operators
        Dial& operator+= (const int& rotation);
        Dial& operator-= (const int& rotation);

        // Getters
        array<int, 2> get_parts() const;
        long get_iters() const;

    };

}

#endif //AOC25_CHAL01_H