/* 
    Program to display logistic regression
    Our model equation is y = b0 + b1x1 + b2x2
    Author : Vivek Nathani
*/

#include <bits/stdc++.h>
#include "../csv/csv.h"
#define show(x) cout << #x << " = " << x << endl  // this will print a variable with its name, done for ease of work 

void normalize(vector<double> &vec);
double sigmoid(const vector<double> &b, double x1, double x2);
double costFunction(vector<double> &x1, vector<double> &x2, const vector<double> &y, const vector<double> &b);
void gradientDescent(vector<double> &x1, vector<double> &x2, const vector<double> &y, double learningRate, vector<double> &b);
void trainModel(vector<double> &x1, vector<double> &x2, const vector<double> &y, vector<double> &b, double learningRate);
int checkAccuracy(const vector<double> &y, const vector<double> predictions);

main()
{
    CSVReader dataSet("dataset.csv");

    vector<vector<string>> rows = dataSet.getAllRows();

    vector<double> x1;
    vector<double> x2;
    vector<double> y;
    vector<double> b(3, 0);

    for(int i = 0; i < rows.size(); i++)
    {
        x1.push_back(stod(rows[i][0]));
        x2.push_back(stod(rows[i][1]));
        y.push_back(stod(rows[i][2]));
    }

    double learningRate = 0.01;
    double dataSize = x1.size();

    normalize(x1);
    normalize(x2);
    show(learningRate);
    trainModel(x1, x2, y, b, learningRate);
    vector<double> predictions;
    for(int i = 0; i < dataSize; i++)
    {
        double term = b[0] + ( b[1] * x1[i] ) + (b[2] * x2[i] );
        if(term > 0.5) term = 1.0;
        else term = 0.0;
        predictions.push_back(term);
    }

    show(b[0]);
    show(b[1]);
    show(b[2]);

    int Accuracy = checkAccuracy(y, predictions);
    show(Accuracy);
}


/*
    Performing min-max normalization on a given dataset A
    new_max(A) and new_min(A) are defined by us.
    Formula : Vi =   Vi - min(A) * (new_max(A) - new_min(A))  + new_min(A)  
                   ---------------
                   max(A) - min(A) 
*/
void normalize(vector<double> &vec)
{
    double max = *max_element(vec.begin(), vec.end());
    double min = *min_element(vec.begin(), vec.end());
    double range = max - min;

    double newMax = 1;
    double newMin = 0;

    for(int i = 0; i < vec.size(); i++)
    {
        vec[i] = ( (vec[i] - min) * (newMax - newMin) / range ) + newMin;
    }
}

/*
    Returning the value of sigmoid function g(z)
    g(z) =  1 / (1 + e^z)
*/
double sigmoid(const vector<double> &b, double x1, double x2)
{
    double y = b[0] + ( b[1] * x1 ) + ( b[2] * x2 );
    double e = M_E;
    double term = 1 + pow(e, y);
    return pow(term, -1);
}

/*
    Calculating the cost function using the found set of weights.
*/
double costFunction(vector<double> &x1, vector<double> &x2, const vector<double> &y, const vector<double> &b)
{
    double cF = 0;
    int dataSize = x1.size();

    for(int i = 0; i < dataSize; i++)
    {
        double logH = log(sigmoid(b, x1[i], x2[i]));
        double loss = ( -y[i] * logH ) - ( (1 - y[i]) * log(1 - logH) );
        cF += loss;
    }

    cF /= dataSize;

    return cF;
}

/*
    Calculating the gradients of our weights by 
    using the partial derivative of the cost function w.r.t to the feature in concern.
*/
void gradientDescent(vector<double> &x1, vector<double> &x2, const vector<double> &y, double learningRate, vector<double> &b)
{
    vector<double> deltaB(3, 0);
    int dataSize = x1.size();

    for(int i = 0; i < dataSize; i++)
    {
        double h = sigmoid(b, x1[i], x2[i]);
        double error = h - y[i];
        error *= learningRate;

        deltaB[0] += error;
        deltaB[1] += ( error * x1[i] );
        deltaB[2] += ( error * x2[i] );
    }

    b[0] += deltaB[0];
    b[1] += deltaB[1];
    b[2] += deltaB[2];
}

/*
    Training is the most important step for gradient descent.
    We need to run it on the same dataset multiple times with 
    modified values of weights each time.
    Here we perform our operation until the differences between 
    consequent cost functions minimize, meaning until our
    gradients converge.
*/
void trainModel(vector<double> &x1, vector<double> &x2, const vector<double> &y, vector<double> &b, double learningRate)
{
    double minimize_difference = 0.00005;
    double cost = costFunction(x1, x2, y, b);
    double changeCost = 1;
    int numberOfIterations = 0;

    while(changeCost > minimize_difference)
    {
        double oldCost = cost;
        gradientDescent(x1, x2, y, learningRate, b);
        cost = costFunction(x1, x2, y, b);
        changeCost = oldCost - cost;
        numberOfIterations++;
    }

    b[0] *= -1;
    b[1] *= -1;
    b[2] *= -1;

    show(numberOfIterations);
}

/*
    A simple function that compares the predictions against
    the original set of values of y.
*/
int checkAccuracy(const vector<double> &y, const vector<double> predictions)
{
    int count = 0;
    int dataSize = y.size();
    show(dataSize);

    for(int i = 0; i < dataSize; i++)
    {
        if(y[i] == predictions[i]) count++;
    }

    return count;
}