#include <bits/stdc++.h>
#include "../csv/csv.h"
#define show(x) cout << #x << " = " << x << endl

using namespace std;

pair<double, double> priorProbabilites(const vector<vector<string>> &dataSet);
int findVocabulary(const vector<vector<string>> &dataSet);
pair<unordered_map<string, double>, unordered_map<string, double>> conditionalProbabilites(const vector<vector<string>> &dataSet, const vector<string> &sample);
unordered_map<string, int> frequencyInSample(const vector<string> &sample);
char classOfSample(pair<double, double> priors, unordered_map<string, double> cProbs, unordered_map<string, double> jProbs, unordered_map<string, int> frequency);

main()
{
    CSVReader readFile("chija.csv");

    vector<vector<string>> dataSet = readFile.getAllRows();
    pair<double, double> priors = priorProbabilites(dataSet);
    vector<string> sample = {"chinese", "chinese", "chinese", "tokyo", "japan"};
    pair<unordered_map<string, double>, unordered_map<string, double>> condProbs = conditionalProbabilites(dataSet, sample);
    unordered_map<string, int> frequency = frequencyInSample(sample);
    char Result = classOfSample(priors, condProbs.first, condProbs.second, frequency);

    show(priors.first);
    show(priors.second);
    show(condProbs.first["chinese"]);
    show(condProbs.first["tokyo"]);
    show(condProbs.first["japan"]);
    show(condProbs.second["chinese"]);
    show(condProbs.second["tokyo"]);
    show(condProbs.second["japan"]);
    show(frequency["chinese"]);
    show(frequency["tokyo"]);
    show(frequency["japan"]);
    show(Result);
}

pair<double, double> priorProbabilites(const vector<vector<string>> &dataSet)
{
    int countC = 0, countJ = 0;

    for(int i = 0; i < dataSet.size(); i++)
    {
        if(dataSet[i][dataSet[i].size() - 1] == "c") countC++;
        else countJ++;
    }

    double pC = (double) countC / (double) dataSet.size();
    double pJ = (double) countJ / (double) dataSet.size();

    pair<double, double> priors = make_pair(pC, pJ);

    return priors;
}

int findVocabulary(const vector<vector<string>> &dataSet)
{
    set<string> words;
    for(int i = 0; i < dataSet.size(); i++)
    {
        for(int j = 0; j < dataSet[i].size() - 1; j++)
        {
            words.insert(dataSet[i][j]);
        }
    }

    return words.size();
}

pair<unordered_map<string, double>, unordered_map<string, double>> conditionalProbabilites(const vector<vector<string>> &dataSet, const vector<string> &sample)
{
    unordered_map<string, double> c, j;
    set<string> words;

    for(int i = 0; i < sample.size(); i++)
    {
        words.insert(sample[i]);
    }

    set<string>::iterator it;

    for(it = words.begin(); it != words.end(); it++)
    {
        int countForC = 1, countForJ = 1;
        for(int i = 0; i < dataSet.size(); i++)
        {
            for(int j = 0; j < dataSet[i].size() - 1; j++)
            {
                if(dataSet[i][j] == *it)
                {
                    if(dataSet[i][dataSet[i].size() - 1] == "c") countForC++;
                    else countForJ++;
                } 
            }
        }
        c[*it] = countForC;
        j[*it] = countForJ;
    }

    int vocabulary = findVocabulary(dataSet);
    int denominatorC = vocabulary, denominatorJ = vocabulary;

    for(int i = 0; i < dataSet.size(); i++)
    {
        for(int j = 0; j < dataSet[i].size() - 1; j++)
        {
            if(dataSet[i][dataSet[i].size() - 1] == "c") denominatorC++;
            else denominatorJ++;
        }
    }


    for(it = words.begin(); it != words.end(); it++)
    {
        c[*it] /= ((double) denominatorC);
        j[*it] /= ((double) denominatorJ);
    }

    pair<unordered_map<string, double>, unordered_map<string, double>> probs = make_pair(c, j);

    return probs;
}

unordered_map<string, int> frequencyInSample(const vector<string> &sample)
{
    unordered_map<string, int> frequency;

    for(int i = 0; i < sample.size(); i++)
    {
        frequency[sample[i]] = 0;
    }

    for(int i = 0; i < sample.size(); i++)
    {
        frequency[sample[i]]++;
    }

    return frequency;
}

char classOfSample(pair<double, double> priors, unordered_map<string, double> cProbs, unordered_map<string, double> jProbs, unordered_map<string, int> frequency)
{
    char res;

    double pC = priors.first, pJ = priors.second;

    unordered_map<string, double>::iterator it;

    for(it = cProbs.begin(); it != cProbs.end(); it++)
    {
        pC *= pow(cProbs[it->first], frequency[it->first]);
        pJ *= pow(jProbs[it->first], frequency[it->first]);
    }

    show(pC);
    show(pJ);

    if(pC > pJ) res = 'c';
    else res = 'j';

    return res;
}