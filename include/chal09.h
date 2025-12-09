#ifndef AOC25_CHAL09
#define AOC25_CHAL09

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <set>
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

    struct node_obj
    {
        const uint64_t x, y;
        node_obj(uint64_t x, uint64_t y) : x(x), y(y) {}
        const uint64_t area(const node_obj& n) const
        {
            auto a = static_cast<int64_t>(n.y-y+1);
            auto b = static_cast<int64_t>(n.x-x+1);
            return abs(a) * abs(b);
        }
        const bool operator== (const node_obj& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }
    } typedef node;

    struct link_obj
    {
        const node a, b;
        const uint64_t area;
        link_obj(uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2) : a(node(x1, y1)), b(x2, y2), area(a.area(b)) {}
        link_obj(node a, node b) : a(a), b(b), area(a.area(b)) {}
        const bool operator== (const link_obj& rhs) const
        {
            return a == rhs.a && b == rhs.b;
        }
        const bool operator< (const link_obj& rhs) const
        {
            return area < rhs.area;
        }
        const bool operator> (const link_obj& rhs) const
        {
            return area > rhs.area;
        }

    } typedef link;

    template <typename T>
    struct set_obj : public set<T>
    {
        set_obj<T>() : set<T>() {}
        const T& back() const
        {
            return *std::prev(this->end());
        }
        T pop_back()
        {
            auto hold = this->back();
            this->erase(this->end());
            return hold;
        }
    };

}

#endif //AOC25_CHALLENGE