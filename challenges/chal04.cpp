#include <chal04.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{

    /*
     * Part 1
     */
    buffer.get()[0] = to_string(sweeper(data, 1));

    /*
     * Part 2
     */
    buffer.get()[1] = to_string(sweeper(data, -1));

    return 0;
}

int advent::sweeper(const vector<string>& data, int iter_lim)
{
    int removed = 0;
    vector<string> new_data = data;

    for (int j = 0; j < data.size(); j++)
    {
        // Loop through each column
        for (int i = 0; i < data[j].size(); i++)
        {
            if (data[j].at(i) != '@')
            {
                continue;
            }
            int count = 0;

            // Loop through 9 cells and check for neighboring @'s (skip 1,1)
            for (int column = 0; column < 3; column++)
            {
                for (int row = 0; row < 3; row++)
                {
                    int x = row-1, y = column-1;

                    // Skip center of 3x3 grid
                    if (x == y && x == 0) continue;

                    // Check out of min bounds
                    if (i + x < 0 || j + y < 0) continue;
                    // Check out of max bounds
                    if (i + x > data[j].size() - 1 || j + y > data.size() - 1) continue;

                    // check if data is an @
                    count += (data[j + y].at(i + x) == '@') ? 1 : 0;
                }
            }

            // Update [j, i] of map to count
            if (0 <= count && count < 4)
            {
                new_data[j].at(i) = '.';
                removed++;
            }
        }
    }

    iter_lim--;
    if (iter_lim == 0 || removed == 0)
    {
        return removed;
    }
    return removed + sweeper(new_data, iter_lim);
}