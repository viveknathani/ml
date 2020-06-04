/*
    Program to demonstrate kNN classification algorithm.
    Author : Vivek Nathani
    The identifier names are self explanatory. 
    The definition of the function to fill the array dataSet is at the end of this program.
*/

#include<bits/stdc++.h>

using namespace std;

class Point
{
    private:
        double x, y, distance;
        int val;

    public:
        void setValues(double X, double Y, int color)
        {
            this->x = X;
            this->y = Y;
            this->val = color;
        }    

        void setDistance(double D)
        {
            this->distance = D;
        }

        double getDistance() 
        {
            return this->distance;
        }       

        double getX()
        {
            return this->x;
        }

        double getY()
        {
            return this->y;
        }

        int getVal()
        {
            return this->val;
        }
};

Point dataSet[16];

void fillDataSet();

bool comparison(Point a, Point b)
{
    return (a.getDistance() < b.getDistance());
}

double euclideanDistance(Point predictPoint, Point existingPoint)
{
    return sqrt(pow(predictPoint.getX() - existingPoint.getX(), 2)
              + pow(predictPoint.getY() - existingPoint.getY(), 2));
}

int knnClassify(int k, Point predictPoint)
{
    for(int i = 0; i < 16; i++)
    {
        dataSet[i].setDistance(euclideanDistance(predictPoint, dataSet[i]));
    }

    sort(dataSet, dataSet + 16, comparison);

    int greenZeroFrequency = 0;
    int redOneFrequency = 0;

    for(int i = 0; i < k; i++)
    {
        if(dataSet[i].getVal() == 0) greenZeroFrequency++;
        else redOneFrequency++;
    }

    int prediction;
    if(greenZeroFrequency > redOneFrequency) prediction = 0;
    else prediction = 1;

    return prediction;
}

int main()
{
    int k = 3; 
    Point test;
    test.setValues(2.5, 7, 0); //passing the distance value as 0. It plays no role in the algorithm.
    fillDataSet();
    int result = knnClassify(k, test);
    cout<<result<<endl;
    return 0;
}

void fillDataSet()
{
    dataSet[0].setValues(1, 12, 0);
    dataSet[1].setValues(2, 5, 0);
    dataSet[2].setValues(5, 3, 1);
    dataSet[3].setValues(3, 2, 1);
    dataSet[4].setValues(3, 6, 0);
    dataSet[5].setValues(1.5, 9, 1);
    dataSet[6].setValues(7, 2, 1);
    dataSet[7].setValues(6, 1, 1);
    dataSet[8].setValues(3.8, 3, 1);
    dataSet[9].setValues(3, 10, 0);
    dataSet[10].setValues(5.6, 4, 1);
    dataSet[11].setValues(4, 2, 1);
    dataSet[12].setValues(3.5, 8, 0);
    dataSet[13].setValues(2, 11, 0);
    dataSet[14].setValues(2, 9, 0);
    dataSet[15].setValues(1, 7, 0);
}
