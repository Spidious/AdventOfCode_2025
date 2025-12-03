#include <chal03.h>

size_t advent::challenge_entry(
        const vector<string>& data,
        shared_ptr<string[]> buffer,
        const string& input
    )
{
    int counter = 0;
    for (string bank : data)
    {
        size_t pos;
        int n = 9;
        string tmp_bank = bank.substr(0, bank.length() - 1);
        while ((pos = tmp_bank.find_first_of(to_string(n))) == string::npos)
        {
            n -= 1;
            if (n < 1)
            {
                // Failure
                cerr << "Something must be wrong, could not find number in string: " << bank << endl;
                return 1;
            }
        }

        cout << "\r" << n << " @ " << pos;
        string fin = to_string(n);
        tmp_bank = bank.substr(pos + 1);

        n = 9;
        while ((pos = tmp_bank.find_first_of(to_string(n))) == string::npos)
        {
            n -= 1;
            if (n < 1)
            {
                // Failure
                cerr << "Something must be wrong, could not find number in string: " << bank << endl;
                return 1;
            }
        }

        cout << "\r" << n << " @ " << pos;
        fin += to_string(n);

        counter += stoi(fin);
    }

    cout << "\r";

    buffer.get()[0] = to_string(counter);

    return 0;
}