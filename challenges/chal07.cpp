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

    vector<uint64_t> p2_tracker(data_width, 0); // Keep track of part 2 "timelines"

    for (int i = 1; i < data.size(); i++)
    {
        for (int j = 0; j < data_width; j++)
        {
            // i = row #
            // j = col #

            // if above character is not 'S' or '|' then move along
            if (!(mut_data[i-1].at(j) == '|'|| mut_data[i-1].at(j) == 'S'))
            {
                continue;
            }

            // Save index of S in p2_tracker as 1
            if (mut_data[i-1].at(j) == 'S')
                p2_tracker[j] = 1;

            // if current cell is not '^' then mark current position with | and move along
            if (mut_data[i].at(j) != '^')
            {
                mut_data[i].at(j) = '|';
                continue;
            }

            // A split needs to happen
            if (j != 0)
            {
                mut_data[i].at(j-1) = '|';
                p2_tracker[j-1] += p2_tracker[j];
            }
            if (j != data_width - 1)
            {
                mut_data[i].at(j+1) = '|';
                p2_tracker[j+1] += p2_tracker[j];
            }
            p2_tracker[j] = 0;
            part1++;
        }
    }

    for (auto p : p2_tracker) part2 += p;

    // Update output buffer
    buffer.get()[0] = to_string(part1);
    buffer.get()[1] = to_string(part2);


    return 0;
}