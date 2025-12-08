#include <chal06.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{
    // Create a vector of math problems
    vector<MathProblem_1> problems;

    // iterate over the bottom of the input to initialize 'problems'
    regex re("([+*]) ?");
    smatch match;
    auto operands = data.back(); // Mutable object
    while (regex_search(operands, match, re))
    {
        // append a new math problem object to the vector
        problems.push_back(MathProblem_1(match[0].str().at(0)));

        // Advance the regex search
        operands = match.suffix();
    }

    // Iterate over the input (-1 row) as normal
    for (int i = 0; i < data.size() -1; i++)
    {
        // Update regex and create a mutable regex object
        re.assign(R"((\d+) ?)");
        string problem_part = data[i];

        // loop over the line of input
        int j = 0;
        while (regex_search(problem_part, match, re))
        {
            // Grab the number as an unsigned long long
            uint64_t num = stoull(match[0].str());

            // Apply to the current problem i
            problems[j].apply(num);

            problem_part = match.suffix();
            j++;
        }
    }

    // Count the total result of each problem
    uint64_t part1 = 0;
    for (auto p : problems) part1 += p.get_total();

    // Update the output buffer
    buffer.get()[0] = to_string(part1);

    /*
     * Begin part 2
     */
    // Initialize problems_2
    re.assign(R"(([\+\*])(\s+)(\s|$))");
    vector<MathProblem_2> problems_2;
    operands = data.back();
    while (regex_search(operands, match, re))
    {
        // Initialize the problem object
        problems_2.push_back(MathProblem_2(
            match[1].str().at(0),
            match[2].str().size() + 1
        ));
        // Advance regex
        operands = match.suffix();
    }

    // Loop through each column
    uint16_t num_columns = problems_2.size();
    vector<string> mut_data = data;
    for (uint16_t i = 0; i < num_columns; i++)
    {
        // Loop through each row
        for (string& row : mut_data)
        {
            // Ensure row is not data.back()
            if (row == data.back()) break;

            // Grab a substring of the row
            string problem_part = row.substr(0, problems_2[i].width);
            if (i + 1 != num_columns) row = row.substr(problems_2[i].width+1);

            // Append substring to problem
            problems_2[i].append(problem_part);
        }
    }

    uint64_t part2 = 0;
    for (auto p : problems_2) part2 += p.get_total();

    buffer.get()[1] = to_string(part2);

    return 0;
}