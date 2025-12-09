#include <chal09.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{
    // Move all string coords into node objects
    vector<node> all_nodes;
    for (auto d : data)
    {
        string mut = d;
        // Grab X
        uint64_t x = stoul(mut.substr(0, mut.find(",")));
        mut = mut.substr(mut.find(",")+1);
        // Grab Y
        uint64_t y = stoul(mut.substr(0));

        all_nodes.push_back(node(x, y));
    }

    set_obj<link> pairs;
    for (auto main_node : all_nodes)
    {
        for (auto other_node : all_nodes)
        {
            if (main_node == other_node) continue;
            pairs.insert(link(main_node, other_node));
        }
    }

    auto part1 = pairs.back();

    buffer.get()[0] = to_string(part1.area);

    /**
     * Begin Part 2
     */

    return 0;
}