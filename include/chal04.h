#ifndef AOC25_CHAL04_H
#define AOC25_CHAL04_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <iomanip>

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

    int sweeper(const vector<string>& data, int iter_lim);

}

#endif //AOC25_CHAL04_H