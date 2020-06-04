/*
    Program to demonstrate kNN regression algorithm.
    Author : Vivek Nathani
    The identifier names are self explanatory. 
    The definition of the function to fill the array dataSet is at the end of this program.
*/
#include<bits/stdc++.h>

using namespace std;

class Person
{
    private:
        double height, weight;
        double distance;

    public:
        void setValues(double h, double w)
        {
            this->height = h;
            this->weight = w;
        }     

        void setDistance(double D)
        {
            this->distance = D;
        }

        double getHeight()
        {
            return this->height;
        }

        double getWeight()
        {
            return this->weight;
        }
};

Person dataSet[14];

void fillDataSet();

bool comparison(Person a, Person b)
{
    return (a.getHeight() < b.getHeight());
}

// we utilise the binary search algorithm to find a crossover point.
// The crossover point is the point before which elements are smaller 
// than or equal to x and after which elements are greater

int findCrossOverPoint(int low, int high, double x)
{
    if(dataSet[high].getHeight() <= x) return high;

    if(dataSet[low].getHeight() >= x)  return low;

    int mid =(low + high) / 2;

    if(dataSet[mid].getHeight() <= x && dataSet[mid+1].getHeight() > x) return mid;

    if(dataSet[mid].getHeight() < x) return findCrossOverPoint(mid + 1, high, x);
    
    if(dataSet[mid].getHeight() > x) return findCrossOverPoint(low, mid - 1, x);
}

double knnRegression(Person predictPerson, int k)
{
    sort(dataSet, dataSet + 13, comparison);

    double x = predictPerson.getHeight();

    int cp = findCrossOverPoint(0, 12, x);

    int rightIndex = cp + 1;

    int count = 0;

    if(dataSet[cp].getHeight() == x) cp--;

    double mean = 0;

    while(cp >= 0 && rightIndex < 14 && count < k)
    {
        if(x - dataSet[cp].getHeight() < dataSet[rightIndex].getHeight() - x)
        {
            mean += dataSet[cp].getWeight();
            cp--;
        }
        else
        {
            mean += dataSet[rightIndex].getWeight();
            cp--;
        }
        
        count++;
    }

    while(count < k && cp >= 0) 
    {
        mean += dataSet[cp].getWeight();
        cp--;
        count++;
    }

    while(count < k && rightIndex < 14)
    {
        mean += dataSet[rightIndex].getWeight();
        rightIndex++;
        count++;
    }

    mean = mean / k;

    return mean;
}


int main()
{
    int k = 3;
    fillDataSet();
    Person test;
    test.setValues(70, -1);
    cout<<knnRegression(test, k);
    return 0;
}

void fillDataSet()
{
    dataSet[0].setValues(68.78190405, 162.3104725);
    dataSet[1].setValues(74.11010539, 212.7408556);
    dataSet[2].setValues(71.7309784, 220.0424703);
    dataSet[3].setValues(69.88179586, 206.3498006);
    dataSet[4].setValues(67.25301569, 152.2121558);
    dataSet[5].setValues(68.78508125, 183.9278886);
    dataSet[6].setValues(68.34851551, 167.9711105);
    dataSet[7].setValues(67.01894966, 175.9294404);
    dataSet[8].setValues(63.45649398, 156.3996764);
    dataSet[9].setValues(71.19538228, 186.6049256);
    dataSet[10].setValues(71.64080512, 213.7411695);
    dataSet[11].setValues(64.76632913, 167.1274611);
    dataSet[12].setValues(69.2830701, 189.4461814);
    dataSet[13].setValues(73.84701702, 241.8935632);
}
