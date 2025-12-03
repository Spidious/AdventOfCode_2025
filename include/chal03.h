#ifndef AOC25_CHALLENGE
#define AOC25_CHALLENGE

#include <string>
#include <iostream>
#include <memory>
#include <vector>
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

    /*
     * Extra functions/classes here
     */

}

#endif //AOC25_CHALLENGE