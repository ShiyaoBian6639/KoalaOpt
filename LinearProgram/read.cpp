#include"read.hpp"

void Read::read(void) /* main function for reading mps file */
{
    auto begin = chrono::steady_clock::now();
    ifstream file(aFileName);
    string line;
    char word;
    int count = 0;
    typedef vector<string> list_type;
    list_type list;
    /* read instance name */

    while (file >> line >> word) //getline(file, line)
    {
        cout << line << endl;
        if (word == '\n')
            cout << "this is newline" << endl;

    }
    cout << "number of lines: " << count << endl;
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - begin;
    cout << "Reading instance " << aInstanceName << " takes " << elapsed.count() << " seconds" << endl;
}