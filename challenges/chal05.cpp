#include <chal05.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{
    vector<Range> fresh_foods;
    vector<unsigned long long> available_food;
    bool sw_case = false; // Have I found the empty line in the data input

    for (string d : data)
    {
        // Check and handle blank line
        if (d == "")
        {
            sw_case = true;
            continue;
        }

        // Effectively a switch case
        // If in second half of input
        if (sw_case)
        {
            available_food.push_back(stoull(d));
            continue;
        }

        // Parse the first half of input
        regex re(R"(^(\d+)-(\d+)$)");
        smatch match;
        if (!regex_match(d, match, re))
        {
            cerr << "Could not match regex on: " << d << endl;
            return 1;
        }

        // Fill the set with every value in range
        unsigned long long min = stoull(match[1]);
        unsigned long long max = stoull(match[2]);
        int last_index = -1;
        Range* new_range = new Range(min, max);
        if (!fresh_foods.empty())
        {
            bool added_to_list = false;
            for (int i = 0; i < fresh_foods.size(); i++)
            {

                switch (new_range->overlaps(fresh_foods[i]))
                {
                case 4:
                    break;
                case 3:
                    fresh_foods[i].min = new_range->min;
                    fresh_foods[i].max = new_range->max;
                    break;
                case 2:
                    fresh_foods[i].min = new_range->min;
                    break;
                case 1:
                    fresh_foods[i].max = new_range->max;
                    break;
                case 0:
                    continue;
                    break;
                }

                if (last_index >= 0)
                {
                    fresh_foods.erase(fresh_foods.begin() + (new_range - &fresh_foods[0]));
                    i--;
                } else delete new_range;
                last_index = i;
                added_to_list = true;
                new_range = (&fresh_foods[0] + i);
            }
            if (!added_to_list)
            {
                fresh_foods.push_back(*new_range);
            }
        }
        else
        {
            fresh_foods.push_back(*new_range);
        }
        new_range = nullptr;
    }


    // Count the number of foods in the set
    int part1 = 0;
    for (unsigned long long food_item : available_food)
    {
        for (auto food_range : fresh_foods)
        {
            if (food_range.contains(food_item))
            {
                // Count the match
                part1++;
            }
        }
    }

    // Count the number of acceptable foods possible
    unsigned long long part2 = 0;
    for (auto r : fresh_foods)
    {
        part2 += r.size();
    }

    buffer.get()[0] = to_string(part1);
    buffer.get()[1] = to_string(part2);

    return 0;
}