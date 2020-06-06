#include <bits/stdc++.h>
#include "../csv/csv.cpp"

using namespace std; 

// validate this from the user
bool ridge = false;
bool lasso = false;

template<typename T>
void gradientDescent(const vector<T> &xAxis, const vector<T> &yAxis, double &m, double &b, double &learningRate)
{
    double gradientM = 0;
    double gradientB = 0;

    double x = 0;
    double y = 0;
    double guess = 0;

    int len = xAxis.size();

    for(int i = 0; i < len; i++)
    {
        x = xAxis[i];
        y = yAxis[i];

        gradientM += (x * (y - ((m * x) + b)));
        gradientB += ((y - (m * x) + b));
    }

    gradientM *= 2;
    gradientB *= 2;

    gradientM /= (double)len;
    gradientB /= (double)len;

    m += (gradientM * learningRate);
    b += (gradientB * learningRate);

    if(ridge)
    {
        m += (alpha * 2 * m * learningRate);
        b += (alpha * 2 * b * learningRate);
    }

    if(lasso)
    {
        m += (alpha * 2 * learningRate);
        b += (alpha * 2 * learningRate);
    }
}

template<typename T>
void trainModel(const vector<T> &xAxis, const vector<T> &yAxis, double &m, double &b, double &learningRate)
{
    // run through the same dataset to make it perfect

    double runM = 0;
    double runB = 0; 
    for(int i = 0; i < 10001; i++)
    {
        gradientDescent(xAxis, yAxis, runM, runB, learningRate);
    }

    m = runM;
    b = runB;
}

int main()
{
    CSVReader dataSet("data.csv");
    vector<vector<string>> rows = dataSet.getAllRows();

    vector<double> yAxis;
    vector<double> xAxis;

    for(int i = 0; i < rows.size(); i++)
    {
        xAxis.push_back(stod(rows[i][0]));
        yAxis.push_back(stod(rows[i][1]));
    }

    double m = 0;
    double b = 0;
    double learningRate = 0.0001;

    trainModel(xAxis, yAxis, m, b, learningRate);

    cout << "m : " << m << endl;
    cout << "b : " << b << endl;

    double input;
    cout << "Input for prediction : " << endl;
    cin >> input;

    int choice;
    cout << "Press 0 for ridge, 1 for lasso, 2 for none" << endl;
    cin >> choice;
    if(choice == 0) ridge = true;
    if(choice == 1) lasso = true;

    double result = (m*input) + b;

    cout << "Prediction : " << result << endl;

    return 0;
}
