#include <bits/stdc++.h>
#include "../csv/csv.h"
#define show(x) cout << #x << " = " << x << endl
using namespace std;

pair<vector<vector<double>>, vector<vector<double>>> splitData(const vector<vector<string>>& dataSet, double ratio);
pair<double, double> priorProbabilities(const vector<int>& yVector);
template<typename T> double meanOfVector(const vector<T> &vec);
template<typename T> double standardDeviation(const vector<T> &vec, double mean);
vector<double> probabilityDensity(const vector<double> &sample, const vector<double> &mean, const vector<double> &sd);
int calcFinal(const vector<vector<double>> &dataSet, const vector<int> &yVector, const vector<double> &sample);
vector<int> makePredictions(const vector<vector<double>> &trainSet, const vector<vector<double>> &testSet, const vector<int> &yTrain);
double checkAccuracy(const vector<int> &yVector, const vector<int> &predictions);

main()
{
    CSVReader readFile("pima.csv");

    vector<vector<string>> dataSet = readFile.getAllRows();

    double splittingRatio = 80;
    pair<vector<vector<double>>, vector<vector<double>>> splitted = splitData(dataSet, splittingRatio);
    vector<vector<double>> train = splitted.first;
    vector<vector<double>> test = splitted.second;
    vector<int> trainRes;
    vector<int> testRes;

    for(int i = 0; i < train.size(); i++)
    {
        trainRes.push_back(train[i][train[i].size() - 1]);
        train[i].erase(train[i].begin() + train[i].size() - 1);
    }

    for(int i = 0; i < test.size(); i++)
    {
        testRes.push_back(test[i][test[i].size() - 1]);
        test[i].erase(test[i].begin() + test[i].size() - 1);
    }

    show(dataSet.size());
    show(train.size());
    show(test.size());
    show(trainRes.size());
    show(testRes.size());
    show(test[0].size());
    vector<int> predictions = makePredictions(train, test, trainRes);
    double Accuracy = checkAccuracy(testRes, predictions);
    show(Accuracy);
}

template<typename T> double meanOfVector(const vector<T> &vec)
{
    double mean = 0;
    double len = vec.size();

    for(int i = 0; i < len; i++)
    {
        mean += (double)vec[i];
    }

    mean /= len;
    return mean;
}

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

template<typename T> double standardDeviation(const vector<T> &vec, double mean)
{
    double sd = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        sd += pow(vec[i] - mean, 2);
    }

    sd = sqrt(sd);

    sd = sd / (double)(vec.size());

    return sd;
}

vector<double> probabilityDensity(const vector<double> &sample, const vector<double> &mean, const vector<double> &sd)
{
    vector<double> result;

    for(int i = 0; i < sample.size(); i++)
    {
        double factor = pow(sd[i] * sqrt(2 * M_PI), -1);
        double term = -0.5 * pow( (sample[i] - mean[i]) / sd[i], 2 );
        double res = factor * pow(M_E, term);
        result.push_back(res);
    }
    return result;
}

pair<double, double> priorProbabilities(const vector<int>& yVector)
{
    double class0Prop = 0;
    double class1Prop = 0;

    int count0 = 0, count1 = 0;

    for(int i = 0; i < yVector.size(); i++)
    {
        if(yVector[i] == 0) count0++;
        else count1++;
    }

    class0Prop = (double) (count0) / (double) (yVector.size());
    class1Prop = (double) (count1) / (double) (yVector.size());

    pair<double, double> priors = make_pair(class0Prop, class1Prop);

    return priors;
}

int calcFinal(const vector<vector<double>> &dataSet, const vector<int> &yVector, const vector<double> &sample)
{
    pair<double, double> priors = priorProbabilities(yVector);
    vector<double> mean0, sd0, mean1, sd1;

    for(int i = 0; i < dataSet[0].size(); i++)
    {
        vector<double> feature0;
        vector<double> feature1;
        for(int j = 0; j < dataSet.size(); j++)
        {
            if(yVector[j] == 0) feature0.push_back(dataSet[j][i]);
            else feature1.push_back(dataSet[j][i]);
        }

        double m0 = meanOfVector(feature0);
        double s0 = standardDeviation(feature0, m0);
        double m1 = meanOfVector(feature1);
        double s1 = standardDeviation(feature1, m1);

        mean0.push_back(m0);
        sd0.push_back(s0);
        mean1.push_back(m1);
        sd1.push_back(s1);
    }

    vector<double> densities0 = probabilityDensity(sample, mean0, sd0);
    vector<double> densities1 = probabilityDensity(sample, mean1, sd1);

    double pZeroSample = priors.first;
    double pOneSample = priors.second;

    for(int i = 0; i < densities0.size(); i++)
    {
        pZeroSample *= densities0[i];
        pOneSample *= densities1[i];
    }

    pZeroSample += 1;
    pOneSample += 1;

    int label;
    if(pZeroSample <= pOneSample) label = 0;
    else label = 1;
    return label; 
}


vector<int> makePredictions(const vector<vector<double>> &trainSet, const vector<vector<double>> &testSet, const vector<int> &yTrain)
{
    vector<int> predictions;

    for(int i = 0; i < testSet.size(); i++)
    {
        vector<double> sample;
        for(int j = 0; j < testSet[i].size(); j++)
        {
            sample.push_back(testSet[i][j]);
        }

        int res = calcFinal(trainSet, yTrain, sample);

        predictions.push_back(res);
    }

    return predictions;
}

double checkAccuracy(const vector<int> &yVector, const vector<int> &predictions)
{
    int count = 0;

    for(int i = 0; i < yVector.size(); i++)
    {
        if(yVector[i] == predictions[i]) count++;
    }

    double percent = (double) count / (double) yVector.size();
    percent *= (double)100;
    return percent;
}



