#include <main.h>

#include "template.h"

int main()
{
    // Create parameters
    std::vector<std::string> file_data;
    auto out_buffer = make_shared<string>("");

    // Open file (AOC_DATA_FILE defined in src/CMakeLists.txt)
    std::ifstream input_file(AOC_DATA_FILE);
    if (!input_file.is_open())
    {
        std::cerr << "Could not open file: " << AOC_DATA_FILE << std::endl;
        return 1; // Fail
    }
    // Loop through each individual line and append to vector
    string line;
    while (getline(input_file, line))
    {
        file_data.push_back(line);
    }
    // Close the file
    input_file.close();


    // Run the challenge
    auto challenge_result = advent::challenge_entry(file_data, out_buffer, "");
    if (challenge_result)
    {
        cerr << "Advent challenge has failed!" << endl;
        cerr << "Exit code: " << challenge_result << endl;
    }

    return 0;
}
