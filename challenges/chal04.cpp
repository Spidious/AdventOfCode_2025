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
    // Create "removed" counter and a mutable data copy of the input data
    int removed = 0;
    vector<string> new_data = data;

    // Loop through each row
    for (int j = 0; j < data.size(); j++)
    {
        // Loop through each cell
        for (int i = 0; i < data[j].size(); i++)
        {
            // If the cell is not an @ then skip it
            if (data[j].at(i) != '@')
            {
                continue;
            }

            // Create count for this cells neighbors
            int count = 0;

            // Loop through 9 cells and check for neighboring @'s (skip 1,1)
            for (int column = 0; column < 3; column++)
            {
                for (int row = 0; row < 3; row++)
                {
                    // Create x and y offsets for readability
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

    // Decrement the iter limit
    iter_lim--;
    if (iter_lim == 0 || removed == 0)
    {
        // Base case
        return removed;
    }

    // Recursively add removed to next iteration
    return removed + sweeper(new_data, iter_lim);
}