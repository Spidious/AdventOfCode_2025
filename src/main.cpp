#include <main.h>

#include "template.h"

int main()
{
    // Create parameters
    std::vector<std::string> file_data;
    auto out_buffer = make_shared<string[]>(2);

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
    auto begin_time = chrono::high_resolution_clock::now();
    auto challenge_result = advent::challenge_entry(file_data, out_buffer, "");
    auto end_time = chrono::high_resolution_clock::now();

    if (challenge_result)
    {
        cerr << "Advent challenge has failed!" << endl;
        cerr << "Exit code: " << challenge_result << endl;
    }

    // Calculate duration
    auto duration = end_time - begin_time;
    auto u_seconds = chrono::duration_cast<std::chrono::microseconds>(duration);
    auto m_seconds = chrono::duration_cast<std::chrono::milliseconds>(duration);
    auto seconds = chrono::duration_cast<std::chrono::seconds>(duration);

    // Output the buffer
    cout << "############ \"" << AOC_CHAL << "\" OUTPUT ############" << endl;
    cout << "Part 1: " << out_buffer[0] << endl;
    cout << "Part 2: " << out_buffer[1] << endl;
    cout << "#########################################" << endl;
    cout << "Completed in: " << seconds.count() << "."
                            << setfill('0') << setw(3) << m_seconds.count() % 1000
                            << setfill('0')  << setw(3) << u_seconds.count() % 1000
                            << " Seconds" << endl;
    cout << "#########################################" << endl;
    return 0;
}