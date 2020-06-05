#include <string>
#include <vector>
#include "csv.h"
#include <fstream>
#include <iostream>

using namespace std;

CSVReader::CSVReader(string f)
{
    this -> filename = f;
}


vector<vector<string>> CSVReader::getAllRows()
{
}