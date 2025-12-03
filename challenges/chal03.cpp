#include <algorithm>
#include <chal03.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{
    // Init the part1 and part2 variables
    int part1 = 0;
    unsigned long long part2 = 0;

    // Loop through input data
    for (string bank : data)
    {
        // Work on part1
        string num1 = search_in_substring(bank, 0, 2);
        if (num1.length() != 2) cerr << "part 1 is not 2 digits" << endl;
        part1 += stoi((num1 == "") ? "0" : num1);

        // Work on part2
        string num2 = search_in_substring(bank, 0, 12);
        if (num2.length() != 12) cerr << "part 2 is not 12 digits" << endl;
        part2 += stoull((num2 == "") ? "0" : num2);

    }

    // Update output buffer
    buffer.get()[0] = to_string(part1);
    buffer.get()[1] = to_string(part2);

    return 0;
}

// Recursively handle substring search
string advent::search_in_substring(const string& input, const int start, const int end_offset)
{
    // Base case. end_offset should not be <= 0
    if (end_offset <= 0)
    {
        return "";
    }

    // Grab the front and back indexes of input substring
    int front = start, back = (input.length() - end_offset) - start;

    // Grab thte substring [start, end_offset]
    string substring = input.substr(front, back+1);

    // Find the highest num of substring and it's index
    array<int, 2> highest_num = find_first_highest(substring);

    // Advance substring search + append next number to current highest number
    return to_string(highest_num[0]) + search_in_substring(input, start+highest_num[1]+1, end_offset - 1);
}

array<int, 2> advent::find_first_highest(const string& input)
{
    // Create a variable to hold the highest number yet found
    int highest = 0, pos = 0;

    // Loop through the input and update highest anytime a new one is found
    // Quit when 9 is found, nothing is higher than 9
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i]-48 > highest)
        {
            highest = input[i]-48;
            pos = i;
        }
        if (highest == 9) break;
    }

    // Return {value, position}
    // Runtime is O(n)
    return {highest, pos};
}