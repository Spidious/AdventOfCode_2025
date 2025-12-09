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

    set_obj<rectangle> rectangles;
    for (auto main_node : all_nodes)
    {
        for (auto other_node : all_nodes)
        {
            if (main_node == other_node) continue;
            rectangles.insert(rectangle(main_node, other_node));
        }
    }

    auto part1 = rectangles.back();

    buffer.get()[0] = to_string(part1.area);

    /**
     * Begin Part 2
     */

    // Create vector of lines
    vector<link> main_line;
    for (int i = 1; i < all_nodes.size(); i++)
        main_line.push_back(link(all_nodes[i - 1], all_nodes[i]));

    rectangle current_rect = rectangles.pop_back();
    for (int i = 0; i < rectangles.size(); i++)
    {
        bool matched = true;
        for (auto line : main_line)
            if (current_rect.intersects(line))
            {
                matched = false;
            }
        if (matched)
        {
            buffer.get()[1] = to_string(current_rect.area);
            break;
        }
        current_rect = rectangles.pop_back();
    }


    return 0;
}