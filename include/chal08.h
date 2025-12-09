#ifndef AOC25_CHAL08_H
#define AOC25_CHAL08_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
/*
 * Extra includes here
 */

using namespace std;

namespace advent
{
    class circuit_obj;
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

    /**
     * Node (Coordinate) object
     */
    class node_obj
    {
    protected:
        uint16_t x, y, z;
    public:
        node_obj(const uint16_t x, const uint16_t y, const uint16_t z) : x(x), y(y), z(z) {}
        float distance(const node_obj& n) const
        {
            float a = (n.x - x)*(n.x - x);
            float b = (n.y - y)*(n.y - y);
            float c = (n.z - z)*(n.z - z);
            float st = sqrt(a + b + c);
            return st;
        }
        bool operator== (const node_obj& rh) const
        {
            if (rh.x == x && rh.y == y && rh.z == z)
                return true;
            return false;
        }
        node_obj& operator= (const node_obj& rh)
        {
            if (this == &rh) return *this;
            x = rh.x; y = rh.y; z = rh.z;
            return *this;
        }
        bool operator<(const node_obj& rh) const
        {
            if (x != rh.x) return x < rh.x;
            if (y != rh.y) return y < rh.y;
            return z < rh.z;
        }

    } typedef node;

    /**
     * Link object
     */
    class link_obj
    {
    protected:
        node a, b;
        float distance;
        friend circuit_obj;

    public:
        link_obj(const node& a, const node& b) : a(a), b(b), distance(a.distance(b)) {}

        const node& get_a() const
        {
            return a;
        }
        const node& get_b() const
        {
            return b;
        }

        bool operator== (const link_obj& rh) const
        {
            if (rh.a == a && rh.b == b)
                return true;
            if (rh.a == b && rh.b == a)
                return true;
            return false;
        }
        bool operator< (const link_obj& rh) const
        {
            return distance < rh.distance;
        }
        bool operator> (const link_obj& rh) const
        {
            return distance > rh.distance;
        }
        link_obj& operator= (const link_obj& rh)
        {
            if (this == &rh) return *this;
            this->a = rh.a;
            this->b = rh.b;
            this->distance = rh.distance;
            return *this;
        }
    } typedef link;

    /**
     * Circuit object
     */
    class circuit_obj
    {
        vector<link> pairs;
    public:
        circuit_obj() = default;
        void add_pair(link p)
        {
            pairs.push_back(p);
        }
        bool contains(const link& p) const
        {
            for (auto pair : pairs)
                if (p == pair)
                    return true;
            return false;
        }
        bool contains(const node& n) const
        {
            for (auto pair : pairs)
                if (pair.a == n || pair.b == n)
                    return true;
            return false;
        }
        bool has_match(const link& p) const
        {
            if (contains(p.get_a())) return true;
            if (contains(p.get_b())) return true;
            return false;
        }
        uint16_t count() const
        {
            set<node> ns;
            for (auto pair : pairs)
            {
                ns.insert(pair.get_a());
                ns.insert(pair.get_b());
            }
            return ns.size();
        }
        void sort()
        {
            std::sort(pairs.begin(), pairs.end());
        }

        circuit_obj& operator= (const circuit_obj& rh)
        {
            if (this == &rh) return *this;
            pairs = rh.pairs;
            return *this;
        }
        bool operator< (const circuit_obj& rh) const
        {
            return count() < rh.count();
        }
        bool operator> (const circuit_obj& rh) const
        {
            return count() > rh.count();
        }
        const link_obj& first() const { return pairs[0]; }
        const link_obj& last() const { return pairs.back(); }
        link_obj pop_first()
        {
            auto hold = pairs[0];
            pairs.erase(pairs.begin());
            return hold;
        }
        auto begin() const { return pairs.begin(); }
        auto end()   const { return pairs.end(); }

    } typedef circuit;

}

#endif //AOC25_CHAL08_H