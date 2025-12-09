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
        uint64_t x, y, z;
    public:
        node_obj(const uint64_t x, const uint64_t y, const uint64_t z) : x(x), y(y), z(z) {}
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
    class rectangl_obj
    {
    protected:
        node a, b;
        float distance;
        friend circuit_obj;

    public:
        rectangl_obj(const node& a, const node& b) : a(a), b(b), distance(a.distance(b)) {}

        const node& get_a() const
        {
            return a;
        }
        const node& get_b() const
        {
            return b;
        }

        bool operator== (const rectangl_obj& rh) const
        {
            if (rh.a == a && rh.b == b)
                return true;
            if (rh.a == b && rh.b == a)
                return true;
            return false;
        }
        bool operator< (const rectangl_obj& rh) const
        {
            return distance < rh.distance;
        }
        bool operator> (const rectangl_obj& rh) const
        {
            return distance > rh.distance;
        }
        rectangl_obj& operator= (const rectangl_obj& rh)
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
        // vector<link> pairs;
        set<link> pairs;
        set<node> nodes;
    public:
        circuit_obj() = default;
        void add_pair(link p)
        {
            // pairs.push_back(p);
            pairs.insert(p);
            nodes.insert(p.get_a());
            nodes.insert(p.get_b());
        }
        bool contains(const link& p) const
        {
            // for (auto pair : pairs)
            //     if (p == pair)
            //         return true;
            return pairs.contains(p);
        }
        bool contains(const node& n) const
        {
            return nodes.contains(n);
        }
        bool contains(const circuit_obj& c) const
        {
            for (auto n : c.nodes)
                if (contains(n)) return true;
            return false;
        }
        bool has_match(const link& p) const
        {
            if (contains(p.get_a())) return true;
            if (contains(p.get_b())) return true;
            return false;
        }
        uint64_t count() const
        {
            return nodes.size();
        }
        void join(circuit_obj& c)
        {
            for (auto i : c.pairs)
                pairs.insert(i);
            for (auto i : c.nodes)
                nodes.insert(i);
        }
        uint64_t size() const
        {
            return pairs.size();
        }

        circuit_obj& operator+= (circuit_obj& rh)
        {
            this->join(rh);
            return *this;
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
        const rectangl_obj& first() const { return *pairs.begin(); }
        const rectangl_obj& last() const { return *pairs.rbegin(); }
        rectangl_obj pop_first()
        {
            auto hold = first();
            pairs.erase(pairs.begin());
            return hold;
        }
        auto begin() const { return pairs.begin(); }
        auto end()   const { return pairs.end(); }

    } typedef circuit;

}

#endif //AOC25_CHAL08_H