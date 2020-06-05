#include<bits/stdc++.h>
#include "../csv/csv.cpp"
using namespace std;

vector<vector<string>> readFromCSV()
{
    fstream filePointer;
    filePointer.open("salary_data.csv", ios::in);

    vector<vector<string>> rows;
    vector<string> row;
    string line;
    while(!filePointer.eof())
    {
        filePointer >> line;
        stringstream ss(line);

        while(ss.good())
        {
            string word;
            getline(ss, word, ',');
            row.push_back(word);
        }

        rows.push_back(row);
        row.clear();
    }
    return rows;
}

int main()
{
    vector<vector<string>> rows = readFromCSV();

    for(int i = 0; i < rows.size(); i++)
    {
        for(int j = 0; j < rows[i].size(); j++)
        {
            cout<<rows[i][j]<<" ";
        }
        cout<<endl;
    }
    CSVReader test("file");
    return 0;
}