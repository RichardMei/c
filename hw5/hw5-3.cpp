/*
 * author Richard
 * date 2019-11-01
 * compile clang++ --std=c++17
 */

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

class LookupTable
{
public:
    double start;
    double end;
    double increment;
    int size;
    float *input;
    // constructor, start: start position; end: end position; increment: the increment "dx"
    // You should calculate the value in range [start, end], with increment "increment"
    LookupTable(double start, double end, double increment)
    {
        this->start = start;
        this->end = end;
        this->increment = increment;
        init();
    };
    // virtual destructor
    virtual ~LookupTable() {};
    // get the value f(x) of the given x
    virtual double getValue(double x) = 0;

    void print()
    {
        std::cout<<"start:"<<this->start<<std::endl;
        std::cout<<"end:"<<this->end<<std::endl;
        std::cout<<"increment:"<<this->increment<<std::endl;
        std::cout<<"size:"<<this->size<<std::endl;
        std::cout<<"input:";
        
        for (size_t i = 0; i < this->size; i++)
        {
            std::cout<<this->input[i]<<",";
        }

        std::cout<<std::endl;
    }

    bool isOutOfRange(double x)
    {
        return x < this->start || x > this->end;
    }

    bool isInInput(double x) 
    {
        for (size_t i = 0; i < this->size; i++)
        {
            if (this->input[i] == x)
            {
                return true;
            } 
        }

        return false;
    }

    int findRightIndex(double x)
    {
        int index;

        for (size_t i = 0; i < this->size; i++)
        {
            if (this->input[i] > x)
            {
                index = i;
                break;
            }
        }

        return index;
    }

private:
    void init()
    {
        this->size = (int)((end - start) / increment) + 1;
        input = new float[size];
        input[0] = this->start;
        input[this->size - 1] = this->end;
        for (size_t i = 1; i < this->size -1; i++)
        {
            input[i] = start + i * this->increment;
        }
    }
};

class SquareLookupTable : public LookupTable
{
public:
    SquareLookupTable(double start, double end, double increment)
        :LookupTable(start, end, increment) {};

    ~SquareLookupTable() {};

    double getValue(double x)
    {
        if (isOutOfRange(x))
        {
            return 0;
        }

        bool mark = this->isInInput(x);
        if (mark)
        {
            return pow(x, 2);
        } else
        {
            int i = this->findRightIndex(x);
            //(x[user]-x[k])*f(x[k+1])
            float a = (x - this->input[i-1]) * pow(this->input[i], 2);
            //(x[k+1]-x[user])*f(x[k])
            float b = (this->input[i] - x) * pow(this->input[i-1], 2);
            return (a + b) / this->increment;
        }
    }
};

class SinLookupTable : public LookupTable
{
    public:
    SinLookupTable(double start, double end, double increment)
        :LookupTable(start, end, increment) {};

    ~SinLookupTable() {};

    double getValue(double x)
    {
        if (isOutOfRange(x))
        {
            return 0;
        }

        bool mark = this->isInInput(x);
        if (mark)
        {
            return sin(x);
        } else
        {
            int i = this->findRightIndex(x);
            //(x[user]-x[k])*f(x[k+1])
            float a = (x - this->input[i-1]) * sin(this->input[i]);
            //(x[k+1]-x[user])*f(x[k])
            float b = (this->input[i] - x) * sin(this->input[i-1]);
            return (a + b) / this->increment;
        }
    }
};

class LogLookupTable : public LookupTable
{
    public:
    LogLookupTable(double start, double end, double increment)
        :LookupTable(start, end, increment) {};

    ~LogLookupTable() {};

    double getValue(double x)
    {
        if (isOutOfRange(x))
        {
            return 0;
        }

        bool mark = this->isInInput(x);
        if (mark)
        {
            return log(x);
        } else
        {
            int i = this->findRightIndex(x);
            //(x[user]-x[k])*f(x[k+1])
            float a = (x - this->input[i-1]) * log(this->input[i]);
            //(x[k+1]-x[user])*f(x[k])
            float b = (this->input[i] - x) * log(this->input[i-1]);
            return (a + b) / this->increment;
        }
    }
};

//////////////////////////////////////////////////////////////////////
///////////////// DO NOT SUBMIT THE FOLLOWING LINES //////////////////
//////////////////////////////////////////////////////////////////////
int main()
{
    LookupTable* squareLookupTable = new SquareLookupTable(1, 2, 0.01); 
    //squareLookupTable->print();
    std::cout<<"squareLookupTable 2 is:"<<squareLookupTable->getValue(2)<<std::endl;
    std::cout<<"squareLookupTable 1.3 is:"<<squareLookupTable->getValue(1.3)<<std::endl;
    delete squareLookupTable;

    LookupTable* sinLookupTable = new SinLookupTable(1, 2, 0.01);
    std::cout<<"sinLookupTable 2 is:"<<sinLookupTable->getValue(2)<<std::endl;
    std::cout<<"sinLookupTable 1.3 is:"<<sinLookupTable->getValue(1.3)<<std::endl;
    delete sinLookupTable;

    LookupTable* logLookupTable = new LogLookupTable(1, 2, 0.01);
    std::cout<<"logLookupTable 2 is:"<<logLookupTable->getValue(2)<<std::endl;
    std::cout<<"logLookupTable 1.3 is:"<<logLookupTable->getValue(1.3)<<std::endl;
    delete logLookupTable;
    return 0;
}
