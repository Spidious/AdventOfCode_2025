#ifndef AOC25_CHAL05_H
#define AOC25_CHAL05_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>
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

    struct Range
    {
        uint64_t min = 0;
        uint64_t max = 0;

        Range(uint64_t min, uint64_t max) : min(min), max(max) {}

        bool contains(uint64_t num) const
        {
            return min <= num && num <= max;
        }

        uint64_t size() const
        {
            return max - min + 1; // Add 1 as the range is inclusive
        }

        /**
         * Check if range 'r' overlaps this range
         * @param r another range
         * @return 0: no overlap, 1: r overlaps this low bound, 2: r overlaps this upper bound, 3: r is fully inside this range, 4: this range is fully inside r
         */
        int overlaps(const Range r) const
        {
            // Check r.min is inside this range
            const bool rmin_inside = this->contains(r.min);
            // Check r.max is inside this range
            const bool rmax_inside = this->contains(r.max);

            // If-Else return cases
            if ((!rmin_inside && !rmax_inside) && r.min < min && r.max > max) // This is contained inside r
                return 4;
            else if ((rmin_inside && rmax_inside)) // r is contained in this
                return 3;
            else if (rmin_inside && !rmax_inside) // r overlaps max bound
                return 2;
            else if (!rmin_inside && rmax_inside) // r overlaps min bound
                return 1;
            else
                return 0;
        }
    };

}

#endif //AOC25_CHAL05_H