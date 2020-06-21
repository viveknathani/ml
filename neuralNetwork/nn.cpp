#include<iostream>
#include<fstream>
#include<vector>
#define show(x) cout << #x << " = " << x << endl

using namespace std;

const int TOTAL_IMAGES = 60000;
const int PIXEL_HEIGHT = 28;
const int PIXEL_WEIGHT = 28;

class Image 
{
    public :
        int pixels[PIXEL_HEIGHT][PIXEL_WEIGHT];
        int label;

    Image()
    {
        this -> label = -1;
    }    

    void printImageAndLabel()
    {
        for(int i = 0; i < 28; i++)
        {
            for(int j = 0; j < 28; j++)
            {
                cout << this -> pixels[i][j];
            }
            cout << endl;
        }

        cout << "Label : " << this -> label << endl;
    }

    void modifyPixels(unsigned char t, int i, int j)
    {
        if(t == 0) this -> pixels[i][j] = 0;
        else this -> pixels[i][j] = 1;
    }
};

void readTrainingSet(Image images[]);
int reverseInt(int i);

main()
{
    Image images[TOTAL_IMAGES];
    readTrainingSet(images);
}

int reverseInt(int i) 
{
    unsigned char c1, c2, c3, c4;
    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void readTrainingSet(Image images[])
{
    string dataPath = "data/train-images-idx3-ubyte";
    string labelPath = "data/train-labels-idx1-ubyte";
    ifstream dataReader, labelReader;
    dataReader.open(dataPath, ios::binary);
    labelReader.open(labelPath, ios::binary);

    int32_t magicNumber = 0;
    int32_t numberOfImages = 0, rows = 0, cols = 0;
    int32_t numbeOfItems = 0;

    dataReader.read((char*)&magicNumber, sizeof(magicNumber));
    dataReader.read((char*)&numberOfImages, sizeof(numberOfImages));
    dataReader.read((char*)&rows, sizeof(rows));
    dataReader.read((char*)&cols, sizeof(cols));

    numberOfImages = reverseInt(numberOfImages);
    rows = reverseInt(rows);
    cols = reverseInt(cols);

    labelReader.read((char*)&magicNumber, sizeof(magicNumber));
    labelReader.read((char*)&numbeOfItems, sizeof(numbeOfItems));

    numbeOfItems = reverseInt(numbeOfItems);

    cout << "Training Data File" << endl;
    show(numberOfImages);
    show(rows);
    show(cols);

    cout << endl << "Training Label File" << endl;
    show(numbeOfItems);

    for(int p = 0; p < TOTAL_IMAGES; p++)
    {
        for(int i = 0; i < 28; i++)
        {
            for(int j = 0; j < 28; j++)
            {
                unsigned char t;
                dataReader.read((char*)&t, sizeof(t));
                images[p].modifyPixels(t, i, j);
            }
        }
    }

    for(int i = 0; i < TOTAL_IMAGES; i++)
    {
        unsigned char t;
        labelReader.read((char*)&t, sizeof(t));
        images[i].label = (int)t;
    }
}

