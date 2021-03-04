#include"read.hpp"


Read::Read(const char* rFileName)
{
    aFileName = rFileName;
    file.open(aFileName);
    if (!file)
    {
        cout << "Can not open " << aFileName << endl;
        return;
    }
}

void Read::read(void) /* main function for reading mps file */
{
    auto begin = chrono::steady_clock::now();
    getInstanceName();
    getRows();
    cout << "instance name: " << aInstanceName << endl;
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - begin;
    cout << "reading " << aInstanceName << " takes " << elapsed.count() << " seconds" << endl;
    cout << NUM_LINE << endl;
}

void Read::getInstanceName(void)
{
    vector<string> parsedLine;
    while (getline(file, line))
    {
        parsedLine = string2vec(line);
        if (parsedLine[0].compare("NAME") == 0)
        {
            aInstanceName = parsedLine[1];
            break;
        }
    }
}

void Read::getRows()
{
    while (getline(file, line))
    {

    }
}

vector<string> Read::string2vec(string line)
{
    int i = 0;
    int j = 0;
    vector<string> res;
    string word;
    while (isspace(line[i])) // remove leading spaces 
        i++;
    while (line[i])
    {
        if (isspace(line[i]))
        {
            while (isspace(line[i]))
                i++;
            res.push_back(word);
            word.clear();
            j = 0;
        }
        else
        {
            word.push_back(line[i]);
            i++;
        }
    }
    res.push_back(word);
    return res;
}