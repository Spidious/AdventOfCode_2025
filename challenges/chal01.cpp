#include <chal01.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{
    // Handle the challenge
    try
    {
        // Create dial object
        advent::Dial dial(STARTING_POS, DIAL_MIN, DIAL_MAX);
        // Create output count
        int zero_count = 0;

        // Create regex pattern
        regex re("^([LR])(\\d+)$");
        smatch match;

        // Loop through the rotation data
        for (auto rotation : data)
        {
            // Apply regex pattern and check for fail
            if (!regex_match(rotation, match, re))
            {
                cerr << "Part of input is invalid: " << rotation << endl;
                return 1;
            }

            // Apply appropriate rotation
            switch (match[1].str()[0])
            {
            case 'L':
                dial -= stoi(match[2].str()); // Left
                break;

            case 'R':
                dial += stoi(match[2].str()); // right
                break;

            default:
                cerr << "Part of input is invalid: " << rotation << endl;
                return 1;
            }
        }

        // Update the output buffer for both parts
        buffer[0] = to_string(dial.get_parts()[0]);
        buffer[1] = to_string(dial.get_parts()[1]);

    }
    catch (const invalid_argument& e)
    {
        // Catch the failed parameters for dial
        cerr << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown Exception" << endl;
        return -1;
    }

    return 0;
}

advent::Dial& advent::Dial::operator+= (const int& rotation)
{
    int pos_hold = pos;

    // Handle right hand rotation
    int movement = (pos - min) + rotation;   // shift to 0..offset
    movement = ((movement % offset) + offset) % offset; // Wrap back into bounds [min-max] adjusted to be [0-offset]
    pos = min + movement; // shift to min..max

    // Check if value is 0 (for part 1)
    if (pos == 0)
    {
        part1++;
    }

    // Check wraps for part 2
    if (pos_hold + rotation > max)
    {
        part2 += (((min-(pos-min))+max)+rotation)/offset;
    }


    return *this;
}

advent::Dial& advent::Dial::operator-= (const int& rotation)
{
    // Could NOT figure out how to do this algebraically so I brute forced it and no I'm not proud of it
    for (int i = 0; i < rotation; i++)
    {
        pos--;
        if (pos < min) pos = max;
        if (pos == min) part2++;
    }

    // Check case for part 1
    if (pos == 0)
    {
        part1++;
    }

    return *this;
}

int* advent::Dial::get_parts() const
{
    int arr[] = {part1, part2};
    return arr;
}

