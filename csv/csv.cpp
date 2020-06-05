#include <string>
#include <vector>
#include "csv.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

CSVReader::CSVReader(string f)
{
    this -> filename = f;
}

vector<vector<string>> CSVReader::getAllRows()
{
    fstream filePointer;
    filePointer.open(this -> filename, ios::in);
    
    vector<vector<string>> rows;
    vector<string> row;
    string line;

    while(!filePointer.eof())
    {
        filePointer >> line;

        stringstream ss(line);

        while(ss.good())
        {
            string columnData;
            getline(ss, columnData, ',');
            row.push_back(columnData);
        }
        rows.push_back(row);
        row.clear();
    }

    return rows;
}