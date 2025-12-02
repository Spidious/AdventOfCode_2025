#include <chal02.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{
    // Setting up regex
    regex re(R"(((\d+)-(\d+)))");
    smatch match;

    // Move puzzle input into a non-const string (this puzzle is a one-liner)
    string puzzle_input = data[0];
    // Create puzzle outputs
    uint_fast64_t part1 = 0;
    uint_fast64_t part2 = 0;

    // Loop over puzzle input using regex match.
    while (regex_search(puzzle_input, match, re))
    {
        // Grab the min and max of range for readability
        uint_fast64_t min = stoull(match[2]);
        uint_fast64_t max = stoull(match[3]);

        for (uint_fast64_t i = min; i <= max; i++)
        {
            // Check part 1
            if (check_invalid_1(to_string(i)))
            {
                // ID is invalid
                part1 += i;
            }

            // Check part 2
            if (check_invalid_2(to_string(i)))
            {
                // ID is invalid
                part2 += i;
            }

        }

        // Advance the puzzle input
        puzzle_input = match.suffix();
    }

    buffer.get()[0] = to_string(part1);
    buffer.get()[1] = to_string(part2);

    return 0;
}

bool advent::check_invalid_1(const string id)
{
    // Skip Anything non-even in length
    if (id.length() % 2 != 0) return false;

    // Grab first half of string and right half
    string lh = id.substr(0, id.length()/2);
    string rh = id.substr(id.length()/2);

    // Return if both halves are equal
    return lh == rh;
}

bool advent::check_invalid_2(const string id)
{
    for (int i = 1; i <= id.length()/2; i++)
    {
        // declair a test ID
        string tst_id;

        // Skip non-divisible i's
        if (id.length() % i != 0) continue;

        // Grab pattern
        string pat = id.substr(0, i);

        // Create full repeating pat that is equivalent to length of id
        for (int j = 0; j < id.length() / i; j++)
        {
            tst_id = tst_id + pat;
        }

        if (tst_id == id) return true;
    }
    return false;
}