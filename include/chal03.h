#ifndef AOC25_CHAL03_H
#define AOC25_CHAL03_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <array>
/*
 * Extra includes here
 */

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

    string search_in_substring(const string& input, int start, int end_offset);
    array<int, 2> find_first_highest(const string& input);

}

#endif //AOC25_CHAL03_H