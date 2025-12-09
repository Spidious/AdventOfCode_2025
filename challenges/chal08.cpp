#include <chal08.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{

    // Parse all 3D coordinates into node objects
    vector<node> all_nodes;
    for (auto d : data)
    {
        string mut = d;
        // Grab X
        uint64_t x = stoul(mut.substr(0, mut.find(",")));
        mut = mut.substr(mut.find(",")+1);
        // Grab Y
        uint64_t y = stoul(mut.substr(0, mut.find(",")));
        mut = mut.substr(mut.find(",")+1);
        // Grab Z
        uint64_t z = stoul(mut);

        all_nodes.push_back(node(x, y, z));
    }

    // Create large pairs list
    long count = 0;
    // vector<link> pairs;
    circuit pairs;

    // Loop over all nodes and find every single pair
    for (auto main_node : all_nodes)
    {
        for (auto other_node : all_nodes)
        {
            count++;
            if (main_node == other_node) continue;
            pairs.add_pair(link(main_node, other_node));
        }
    }

    // Add first 10 pairs to circuits
    vector<circuit> circuits;
    for (int i = 0; i < 10; i++)
    {
        // Check condition
        circuit * matched = nullptr;
        link current = pairs.pop_first();
        // Loop over each existing circuit
        for (int j = 0; j < circuits.size(); j++)
        {
            // check if pair should be added
            if (circuits[j].has_match(current))
            {

                // Move pair to circuit
                circuits[j].add_pair(current);
                matched = &circuits[j];
            }
        }
        // If unmached, create new circuit and move pair
        if (!matched)
        {
            circuits.push_back(circuit());
            circuits.back().add_pair(current);
        }
        matched = nullptr;
    }

    // Merge necessary circuits
    for (int i = 0; i < circuits.size(); i++)
    {
        for (int j = 0; j < circuits.size(); j++)
        {
            if (i == j) continue;
            if (circuits[i].contains(circuits[j]))
            {
                circuits[i] += circuits[j];
                circuits.erase(circuits.begin() + j);
            }
        }
    }

    // Sort the circuits
    sort(circuits.begin(), circuits.end(), greater<>());

    // Take product of top 3
    uint64_t part1 = 1;
    for (int i = 0; i < circuits.size(); i++)
    {
        cout << circuits[i].count() << endl;
        part1 *= circuits[i].count();
    }

    // Output to buffer
    buffer.get()[0] = to_string(part1);

    return 0;
}