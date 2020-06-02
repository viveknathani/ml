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

        double getDistance() 
        {
            return this->distance;
        }       
};

Point dataSet[16];

void fillDataSet();

int main()
{
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
