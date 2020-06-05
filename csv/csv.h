#ifndef CSV_H
#define CSV_H

#include<string>
#include<vector>

using namespace std;

class CSVReader
{
    private :
        string filename;

    public :
        CSVReader(string f);
        vector<vector<string>> getAllRows();
};

#endif
