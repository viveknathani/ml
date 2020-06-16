/*
    Bernoulli Naive Bayes Classification.
    Author : Vivek Nathani
*/

#include <bits/stdc++.h>
#include "../csv/csv.h"
#define show(x) cout << #x << " = " << x << endl

using namespace std;

pair<double, double> findPriors(const vector<vector<string>> &dataSet);
pair<vector<double>, vector<double>> conditionalProbabilities(const vector<vector<string>> &dataSet, const vector<string> &sample);
string finalStep(pair<double, double> priors, pair<vector<double>, vector<double>> conditionals);

main()
{
    CSVReader readFile("bdata.csv");

    vector<vector<string>> dataSet = readFile.getAllRows();
    pair<double, double> priors = findPriors(dataSet);
    vector<string> sample = {"1", "1", "0"};
    pair<vector<double>, vector<double>> condProbs = conditionalProbabilities(dataSet, sample);
    string Result = finalStep(priors, condProbs);

    show(priors.first);
    show(priors.second);
    show(condProbs.first[0]);
    show(condProbs.first[1]);
    show(condProbs.first[2]);
    show(condProbs.second[0]);
    show(condProbs.second[1]);
    show(condProbs.second[2]);
    show(Result);
}

pair<double, double> findPriors(const vector<vector<string>> &dataSet)
{
    double passP = 0, failP = 0;

    int countP = 0, countF = 0;

    for(int i = 0; i < dataSet.size(); i++)
    {
        if(dataSet[i][dataSet[i].size() - 1] == "1") countP++;
        else countF++;
    }

    passP = (double) countP / (double) dataSet.size();
    failP = (double) countF / (double) dataSet.size();

    return make_pair(passP, failP);
}

// find the conditional or posterior probabilites
pair<vector<double>, vector<double>> conditionalProbabilities(const vector<vector<string>> &dataSet, const vector<string> &sample)
{
    vector<double> passProbs, failProbs;

    // since we know the value of denominator already (by looking at the dataset)
    double passD = 3, failD = 2;


    for(int i = 0; i < sample.size(); i++)
    {
        int countPass = 0, countFail = 0;

        for(int j = 0; j < dataSet.size(); j++)
        {
            if(dataSet[j][i] == sample[i])
            {
                if(dataSet[j][dataSet[j].size() - 1] == "1") countPass++;
                else countFail++;
            }
        }

        passProbs.push_back((double)countPass / passD);
        failProbs.push_back((double)countFail / failD);
    }

    return make_pair(passProbs, failProbs);
}

string finalStep(pair<double, double> priors, pair<vector<double>, vector<double>> conditionals)
{
    string res = "fail";

    double passP = priors.first, failP = priors.second;

    for(int i = 0; i < conditionals.first.size(); i++)
    {
        passP *= conditionals.first[i];
        failP *= conditionals.first[i];
    }

    show(passP);
    show(failP);

    if(passP > failP) res = "pass";

    return res;
}