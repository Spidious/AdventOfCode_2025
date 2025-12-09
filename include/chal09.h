#ifndef AOC25_CHAL09_H
#define AOC25_CHAL09_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <set>
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

    struct node_obj
    {
        uint64_t x, y;
        node_obj(uint64_t x, uint64_t y) : x(x), y(y) {}
        const uint64_t area(const node_obj& n) const
        {
            auto a = static_cast<int64_t>(n.y-y+1);
            auto b = static_cast<int64_t>(n.x-x+1);
            return abs(a) * abs(b);
        }
        const uint64_t distance(const node_obj& n) const
        {
            long double a = ((x-n.x)*(x-n.x));
            long double b = ((y-n.y)*(y-n.y));
            return sqrt(a+b);
        }
        const bool operator== (const node_obj& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }
        node_obj& operator= (const node_obj& rhs)
        {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }
    } typedef node;

    struct link_obj
    {
        node a, b;
        long double distance;
        link_obj(node a, node b) : a(a), b(b), distance(a.distance(b)) {}
        link_obj() : a(node(0,0)), b(node(0,0)), distance(0) {};

        const int intersects(const link_obj& other) const
        {
            // Lines are only ever horizontal or vertical, check if they are horizontal
            bool this_horizontal = a.y == b.y;
            bool other_horizontal = other.a.y == other.b.y;

            // if parallel or collinear, they do not intersect (collinear does not count as intersecting here)
            if (this_horizontal == other_horizontal) return 0;

            // if any of the endpoints match then drop
            if (a == other.a || a == other.b || b == other.a || b == other.b) return 0;

            // Determine which is horizontal and which is vertical
            const link_obj& H_Line = this_horizontal ? *this : other;
            const link_obj& V_Line = this_horizontal ? other : *this;

            // Determine intersect
            if (
                (H_Line.a.x < V_Line.a.x && V_Line.a.x < H_Line.b.x)
                &&
                (V_Line.a.y < H_Line.a.y && H_Line.a.y < V_Line.b.y)
                )
            {
                return 1;
            }
            if (
                (V_Line.a.x == H_Line.a.x || V_Line.a.x == H_Line.b.x)
                ||
                (H_Line.a.y == V_Line.a.y || H_Line.a.y == V_Line.b.y)
                )
            {
                return 2;
            }
            return 0;



        }

        const bool operator== (const link_obj& rhs) const
        {
            return a == rhs.a && b == rhs.b;
        }
        const bool operator< (const link_obj& rhs) const
        {
            return distance < rhs.distance;
        }
        const bool operator> (const link_obj& rhs) const
        {
            return distance > rhs.distance;
        }
        link_obj& operator= (const link_obj& rhs)
        {
            if (this == &rhs) return *this;
            this->a = rhs.a;
            this->b = rhs.b;
            this->distance = rhs.distance;
            return *this;
        }

    } typedef link;

    struct rectangl_obj
    {
        node a, b;
        uint64_t area;
        vector<link> perimeter;

        rectangl_obj(node a, node b) : a(a), b(b), area(a.area(b))
        {
            perimeter.push_back(link(a, node(b.x, a.y)));
            perimeter.push_back(link(node(b.x, a.y), b));
            perimeter.push_back(link(b, node(a.x, b.y)));
            perimeter.push_back(link(node(a.x, b.y), a));
        }

        const bool intersects(const link_obj& pair)
        {
            for (auto edge : perimeter)
            {
                int res = edge.intersects(pair);
                if (res == 0) return 0;
                if (res == 1) return 1;
                // todo :: Figure out how to determine if res 2 is inside or outside
                // Determine if edge is horizontal or vertical
                if (edge.a.x == edge.b.x) // Horizontal
                {
                    node pair_node = (pair.a.x == edge.a.x) ? pair.a : pair.b;
                    link parallel_edge;
                    for (auto e : perimeter)
                        if ((e.a.x == edge.a.x && e.b.x == edge.b.x)
                            ||
                            (e.a.x == edge.b.x && e.b.x == edge.a.x))
                        {
                            parallel_edge = e;
                            break;
                        }
                    if ((parallel_edge.a.y - edge.a.y > 0) && (pair_node.y - edge.a.y > 0)
                        ||
                        (parallel_edge.a.y - edge.a.y < 0) && (pair_node.y - edge.a.y < 0))
                    {
                        return true;
                    }

                } else // Vertical
                {
                    node pair_node = (pair.a.y == edge.a.y) ? pair.a : pair.b;
                    link parallel_edge;
                    for (auto e : perimeter)
                        if ((e.a.y == edge.a.y && e.b.y == edge.b.y)
                            ||
                            (e.a.y == edge.b.y && e.b.y == edge.a.y))
                        {
                            parallel_edge = e;
                            break;
                        }
                    // Actually solve it
                    if ((parallel_edge.a.x - edge.a.x > 0) && (pair_node.x - edge.a.x > 0)
                        ||
                        (parallel_edge.a.x - edge.a.x < 0) && (pair_node.x - edge.a.x < 0))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        const bool operator== (const rectangl_obj& rhs) const
        {
            return a == rhs.a && b == rhs.b;
        }
        const bool operator< (const rectangl_obj& rhs) const
        {
            return area < rhs.area;
        }
        const bool operator> (const rectangl_obj& rhs) const
        {
            return area > rhs.area;
        }
        rectangl_obj& operator= (const rectangl_obj& rhs)
        {
            if (this == &rhs) return *this;
            this->a = rhs.a;
            this->b = rhs.b;
            this->area = rhs.area;
            this->perimeter = rhs.perimeter;
            return *this;
        }

    } typedef rectangle;

    template <typename T>
    struct set_obj : set<T>
    {
        set_obj<T>() : set<T>() {}
        const T& back() const
        {
            return *std::prev(this->end());
        }
        T pop_back()
        {
            auto it = prev(this->end());
            auto hold = *it;
            this->erase(it);
            return hold;
        }
    };

}

#endif //AOC25_CHAL09_H