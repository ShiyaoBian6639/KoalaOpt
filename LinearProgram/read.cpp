#include"read.hpp"


Read::Read(const char* rFileName)
{
    aFileName = rFileName;
    file.open(aFileName);
    if (!file){
        cout << "Can not open " << aFileName << endl;
        return;
    }
}

void Read::read(void) /* main function for reading mps file */
{
    auto begin = chrono::steady_clock::now();
    getInstanceName();
    getRows();
    getCols();
    cout << "instance name: " << aInstanceName << endl;
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - begin;
    cout << "reading " << aInstanceName << " takes " << elapsed.count() << " seconds" << endl;
    cout << "number of lines: " <<NUM_LINE << endl;
    cout << "num rows: " << NUM_CONSTRAINTS << endl;
}

void Read::getInstanceName(void)
{
    while (getline(file, line)){
        parsedLine = string2vec(line);
        NUM_LINE++;
        if (parsedLine[0].compare("NAME") == 0){
            aInstanceName = parsedLine[1];
        }
        else if (parsedLine[0].compare("ROWS") == 0){
            break;
        }
    }
}

void Read::getRows()
{
    string row_sign;
    while (getline(file, line)){
        parsedLine = string2vec(line);
        if (parsedLine.size() == 1 && parsedLine[0].compare("COLUMNS") == 0){
            break;
        }else{
            row_sign = parsedLine[0];
            ROW_SIGN.push_back(row_sign);
            ROW_NAME2IDX[parsedLine[1]] = NUM_CONSTRAINTS++;
            if (row_sign.compare("N") == 0){

                // differentiate E,L,G and N 
            }
        }
    }
}

void Read::getCols()
{
    while (getline(file, line)){
        parsedLine = string2vec(line);
        if (parsedLine.size() == 1 && parsedLine[0].compare("RHS") == 0){
            break;
        }
        else if (parsedLine.size()== 3 && parsedLine[2].compare("'INTORG'") == 0){
            INT_MARKER = 1;
        }
        else if (parsedLine.size() == 3 && parsedLine[2].compare("'INTEND'") == 0) {
            INT_MARKER = 0;
        }
        else {
            readCols();
        }
    }
}

void Read::readCols()
{
    int i;
    string col_name;
    string row_name;
    int row_index;
    double value;
    col_name = parsedLine[0];
    NUM_VARS++;
    for (i = 1; i < parsedLine.size(); i++) {
        if (i % 2) { // row name
            row_name = parsedLine[i];
            row_index = ROW_NAME2IDX[row_name];
        }
        else { // value 
            value = stod(parsedLine[i]);
            A.push_back(Trip(row_index, NUM_VARS, value));
        }
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
    while (line[i]){
        if (isspace(line[i])){
            while (isspace(line[i]))
                i++;
            res.push_back(word);
            word.clear();
            j = 0;
        }else{
            word.push_back(line[i]);
            i++;
        }
    }
    res.push_back(word);
    return res;
}