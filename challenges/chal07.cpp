#include <chal07.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{
    vector<string> mut_data = data;
    int data_width = data[0].size();

    uint64_t part1 = 0; // count this on O(mn)
    uint64_t part2 = 0;

    vector<uint64_t> p1_tracker(data_width, 0);
    vector<uint64_t> p2_tracker(data_width, 0); // Keep track of part 2 "timelines"

    // Save index of S in p2_tracker as 1
    int mid = data_width / 2;
    p1_tracker[mid] = 1;
    p2_tracker[mid] = 1;

    // Skip straight over S row and go to actual splits
    for (int i = 2; i < data.size(); i += 2)
    {
        // Loop in sort of a cone shape
        for (int j = (data_width - i) / 2; j < (data_width + i) / 2; j++)
        {
            // i = row #
            // j = col #

            // if current cell is not '^' then mark current position with | and move along
            if (!(mut_data[i].at(j) == '^' && p1_tracker[j]))
            {
                // mut_data[i].at(j) = '|';
                continue;
            }

            // A split needs to happen
            if (j != 0)
            {
                // mut_data[i].at(j-1) = '|';
                if (p1_tracker[j])
                {
                    p1_tracker[j-1] = 1;
                }
                p2_tracker[j-1] += p2_tracker[j];
            }
            if (j != data_width - 1)
            {
                // mut_data[i].at(j+1) = '|';
                if (p1_tracker[j])
                {
                    p1_tracker[j+1] = 1;
                }
                p2_tracker[j+1] += p2_tracker[j];
            }

            // Clear the center of the split
            p1_tracker[j] = 0;
            p2_tracker[j] = 0;
            part1++;

            // There are never 2 splits immediately next to each other (No ^^ always ^.^)
            j++;
        }
    }

    for (auto p : p2_tracker) part2 += p;

    // Update output buffer
    buffer.get()[0] = to_string(part1);
    buffer.get()[1] = to_string(part2);


    return 0;
}