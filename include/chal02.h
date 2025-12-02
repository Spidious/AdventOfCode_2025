#ifndef AOC25_CHAL02_H
#define AOC25_CHAL02_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <regex>
#include <format>
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

    // Handlers for part 1 and 2
    bool check_invalid_1(string id);
    bool check_invalid_2(string id);

}

#endif //AOC25_CHAL02_H