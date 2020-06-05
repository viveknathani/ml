#include <bits/stdc++.h>
#include "../csv/csv.cpp"
using namespace std;

// function to calculate mean of vector of any data type
template<typename T>
double meanOfVector(const vector<T> &vec)
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

// function that uses the ols method
// and returns the values of m and b in y = mx + b
template<typename T>
pair<double, double> ordinaryLeastSquares(const vector<T> &xAxis, const vector<T> &yAxis)
{
    double m = 0, b = 0;
    double xMean = meanOfVector(xAxis);
    double yMean = meanOfVector(yAxis);

    double numerator = 0;
    double denominator = 0;

    // since xAxis.size() == yAxis.size(), we will use a common notation
    int dataSize = xAxis.size(); 

    for(int i = 0; i < dataSize; i++)
    {
        double term = (xAxis[i]-xMean)*(yAxis[i]-yMean);
        numerator += term;

        double dTerm = pow((xAxis[i]-xMean), 2);
        denominator += dTerm;
    }

    m = numerator / denominator;
    b = yMean - (m*xMean);

    pair<double, double> weights;
    weights.first = m;
    weights.second = b;

    return weights;
}

int main()
{
    CSVReader dataSet("salary_data.csv");
    vector<vector<string>> rows = dataSet.getAllRows();

    string columnOneName = rows[0][0];
    string columnTwoName = rows[0][1];

    vector<double> xAxis;
    vector<double> yAxis;

    for(int i = 1; i < rows.size(); i++)
    {
        xAxis.push_back(stod(rows[i][0]));  // convert to double and push, stod()
        yAxis.push_back(stoi(rows[i][1]));  // convert to int and push, stoi()
    }

    pair<double, double> weights = ordinaryLeastSquares(xAxis, yAxis);

    double testX;
    cout << "Enter the experience years of the candidate : ";
    cin >> testX;

    double result = (weights.first*testX) + weights.second;

    cout << "The salary of the employee is : "<<result<<endl; 
    return 0;
}