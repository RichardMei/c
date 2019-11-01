#include <iostream>
#include <math.h>

const int ERRORCODE = -1;

class DataAnalyser
{
public:
    DataAnalyser() {};
    virtual ~DataAnalyser() {};
    /** 
     * virtual function "calculate"
     * @param data: the data array need to be calculated
     * @param size: the length of the data
     * @return: the calculated result
     */
    virtual float calculate(float* data, size_t size)
    {
        std::cout << "ERROR: Try to access virtual function which is in base class" << std::endl;
        return ERRORCODE;
    };
};


// MaximumAnalyser
class MaximumAnalyser : public DataAnalyser
{
    float calculate(float* data, size_t size) {
        float max = data[0];
        for (size_t i = 1; i < size; i++)
        {
            if (data[i] > max)
            {
                max = data[i];
            }
        }
        return max;
    }
};

// MinimumAnalyser
class MinimumAnalyser : public DataAnalyser
{
    float calculate(float* data, size_t size) {
        float min = data[8];
        for (size_t i = 1; i < size; i++)
        {
            if (data[i] < min)
            {
                min = data[i];
            }
        }
        return min;
    }
};

// AverageAnalyser
class AverageAnalyser : public DataAnalyser
{
    float calculate(float* data, size_t size) {
        float sum = 0;
        for (size_t i = 1; i < size; i++)
        {
            sum += data[i];
        }
        return sum / size;
    }
};

// MedianAnalyser
class MedianAnalyser : public DataAnalyser
{
    /**
     *if a sorted arr[n] length is even, median = (arr[n/2] + arr[n/2 + 1]) / 2;
     *if a sorted arr[n] length is odd, median = arr[(n+1)/2]
     *notice that, in c++ arr index from 0 not 1
     */
    float calculate(float* data, size_t size) 
    {
        std::sort(data, data + size);

        bool isEven = (size % 2 == 0);
        if (isEven)
        {
            return (data[(size-1) / 2] + data[(size-1) / 2 + 1]) / 2;
        } else
        {
            return data[size / 2];
        }
    }
};

// StdDevAnalyser
class StdDevAnalyser : public DataAnalyser
{
    float calculate(float* data, size_t size) 
    {
        DataAnalyser* averageAnalyser = new AverageAnalyser();
        float avg = averageAnalyser->calculate(data, size);
        delete averageAnalyser;

        float sum = 0;
        for (size_t i = 0; i < size; i++)
        {
            sum += pow(data[i] - avg, 2);
        }

        return sqrt(sum / size);
    }
};

//////////////////////////////////////////////////////////////////////
///////////////// DO NOT SUBMIT THE FOLLOWING LINES //////////////////
//////////////////////////////////////////////////////////////////////
int main()
{
    /* Your can write your own main for testing */
    float arr[] = {0.3, -100, 1, 2, 5, 6, 9, 12, 2};
    DataAnalyser* max = new MaximumAnalyser();
    std::cout<< max->calculate(arr, 9) <<std::endl;
    delete max;

    DataAnalyser* min = new MinimumAnalyser();
    std::cout<< min->calculate(arr, 9) <<std::endl;
    delete min;

    DataAnalyser* avg = new AverageAnalyser();
    std::cout<< avg->calculate(arr, 9) <<std::endl;
    delete avg;

    DataAnalyser* median = new MedianAnalyser();
    std::cout<< median->calculate(arr, 9) <<std::endl;
    delete median;

    DataAnalyser* stdDev = new StdDevAnalyser();
    std::cout<< stdDev->calculate(arr, 9) <<std::endl;
    delete stdDev;

    return 0;
}