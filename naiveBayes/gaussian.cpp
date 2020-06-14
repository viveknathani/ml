#include <bits/stdc++.h>
#include "../csv/csv.h"
#define show(x) cout << #x << " = " << x << endl
using namespace std;

pair<vector<vector<double>>, vector<vector<double>>> splitData(const vector<vector<string>>& dataSet, double ratio)
{
    pair<vector<vector<double>>, vector<vector<double>>> splitted;
    vector<vector<double>> train(dataSet.size());
    vector<vector<double>> test;

    for(int i = 0; i < dataSet.size(); i++)
    {
        for(int j = 0; j < dataSet[i].size(); j++)
        {
            train[i].push_back(stod(dataSet[i][j]));
        }
    }

    int len = train.size() - (ratio * train.size() / 100);

    while(test.size() <= len)
    {
        srand(time(NULL));
        int index = rand() % train.size();
        test.push_back(train[index]);
        train.erase(train.begin() + index);
    }

    splitted = make_pair(train, test);

    return splitted;
}

main()
{
    CSVReader readFile("pima.csv");

    vector<vector<string>> dataSet = readFile.getAllRows();

    double splittingRatio = 80;
    pair<vector<vector<double>>, vector<vector<double>>> splitted = splitData(dataSet, splittingRatio);
    vector<vector<double>> train = splitted.first;
    vector<vector<double>> test = splitted.second;

    show(dataSet.size());
    show(train.size());
    show(test.size());
}