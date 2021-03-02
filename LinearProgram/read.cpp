#include"read.hpp"

Read::Read(string rFileName)
{
    aFileName = rFileName;
    file.open(aFileName, ios_base::in);
}

void Read::read(void) /* main function for reading mps file */
{
    auto begin = chrono::steady_clock::now();
    getInstanceName(); 
    while (getline(file, line))
    {
        cout << line << endl;
    }
    cout << "NUM_LINE: " << NUM_LINE << endl; 
    cout << "NUM_words: " << NUM_NNZ << endl;
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - begin;
    cout << "reading takes " << elapsed.count() << " seconds" << endl;
}

void Read::getInstanceName()
{
    while (getline(file, line)) //
    {

        if (line[0] != '*')
        {
            boost::split(result, line, boost::is_any_of("\t "), boost::token_compress_on);
            if (result[0].compare("NAME") == 0) 
            {
                aInstanceName = result[1];
                break;
            }
        }
        NUM_LINE++;
    }
}