/*
 * author Richard
 * date 2019-11-02
 * compile clang++ --std=c++17
 */

#include <iostream>
#include <string>

using namespace std;

class ReportParser
{
public:
    int numStudents;
    int numInfos;
    string **matrix = NULL;
    ReportParser(int numStudents, int numInfos);
    ~ReportParser();
    void readReport();
    void writeStructuredReport(int sortOption);

    void print()
    {
        cout<<"matrix is : "<<endl;
        for (size_t i = 0; i < this->numStudents; i++)
        {
            for (size_t j = 0; j < this->numInfos; j++)
            {
                cout<<"martix["<<i<<"]["<<j<<"] : "<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    // Add your own functions and variables here
private:
    /*
     *get each colum max word length
     */
    int* getMaxWordLength()
    {
        int* maxLength = new int[this->numInfos];
        
        for (size_t i = 0; i < this->numInfos; i++)
        {
            int max = 0;
            for (size_t j = 0; j < this->numStudents; j++)
            {
                if (this->matrix[j][i].length() > max)
                {
                    max = this->matrix[j][i].length();
                    maxLength[i] = max;
                }
            }
        }

        return maxLength;
    }

    string* getColumn(int sortOption)
    {
        string* column = new string[this->numStudents];
        for (size_t i = 0; i < this->numStudents; i++)
        {
            column[i] = this->matrix[i][sortOption];
        }
        
        return column;
    }

    /*
     *give a array then sorted, get orginal index of a sorted array
     *eg:[c,b,a] sort to [a,b,c] return OrigIndex [2,1,0]
     */
    int* getOrigIndex(string* orig)
    {
        string sorted[this->numStudents];
        copy(orig, orig + this->numStudents, sorted);
        sort(sorted, sorted + this->numStudents);

        int* index = new int[this->numStudents];
        for (size_t i = 0; i < this->numStudents; i++)
        {
            index[i] = -1;
        }

        for (size_t i = 0; i < this->numStudents; i++)
        {
            for (size_t j = 0; j < this->numStudents; j++)
            {
                if (sorted[i] == orig[j])
                {
                    if (!isExist(index, this->numStudents, j))
                    {
                        index[i] = j;
                        break;
                    } 
                }
            }
        }
        
        return index;
    }

    bool isExist(int* array, int length, int value)
    {
        for (size_t i = 0; i < length; i++)
        {
            if (array[i] == value)
            {
                return true;
            }
        }
        
        return false;
    }

    int calcHeadAndTailLength(int* maxWordLength)
    {
        int total = 2 * this->numInfos + this->numInfos - 1;
        for (size_t i = 0; i < this->numInfos; i++)
        {
            total += maxWordLength[i];
        }

        return total;
    }

    void printFirstLine(int* maxWordLength)
    {
        int total = calcHeadAndTailLength(maxWordLength);
        
        cout<<"/";
        for (size_t i = 0; i < total; i++)
        {
           cout<<"-";
        }
        cout<<"\\"<<endl;
    }

    void printLastLine(int* maxWordLength)
    {
        int total = calcHeadAndTailLength(maxWordLength);
        cout<<"\\";
        for (size_t i = 0; i < total; i++)
        {
           cout<<"-";
        }
        cout<<"/"<<endl;
    }

    string formatWord(string word, int* maxWordLength, int index)
    {
        string whiteSpace = " ";

        if (word.length() == maxWordLength[index])
        {
            return whiteSpace + word + whiteSpace;
        } else
        {
            int padding = maxWordLength[index] - word.length();
            for (size_t i = 0; i < padding; i++)
            {
                word += whiteSpace;
            }
            return whiteSpace + word + whiteSpace;
        }
    }

    void printBody(int* orgiIndex, int* maxWordLength)
    {
        for (size_t i = 0; i < this->numStudents; i++)
        {
            int index = orgiIndex[i];
            cout<<"|";
            for (size_t j = 0; j < this->numInfos; j++)
            {
                cout<<formatWord(this->matrix[index][j], maxWordLength, j)<<"|";
            }
            cout<<endl;
        }
    }
};

ReportParser::ReportParser(int numStudents, int numInfos) 
{
    this->numStudents = numStudents;
    this->numInfos = numInfos;
    this->matrix = new string *[this->numStudents];
    for (size_t i = 0; i < this->numStudents; i++)
    {
        this->matrix[i] = new string[this->numInfos];
    }
} 

ReportParser::~ReportParser() 
{
    
}


void ReportParser::readReport()
{
    string line;
    const char* delim = " ";
    
    for (size_t i = 0; i < this->numStudents; i++)
    {
        cout<<"please input "<<i+1<<" line"<<endl;
        getline(cin, line);
        
        //split sring in c++
        //reference https://www.zhihu.com/question/36642771
        //reference https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        size_t index = 0;
        char* token = strtok(line.data(), delim);
        while (token != NULL)
        {
            this->matrix[i][index++] = token;
            token = strtok(NULL, delim);
        }
    }
}

void ReportParser::writeStructuredReport(int sortOption)
{   
    string* column = getColumn(sortOption);
    
    int* orgiIndex = getOrigIndex(column);
    int* maxWordLength = getMaxWordLength();

    cout<<"write structured report :"<<endl;

    printFirstLine(maxWordLength);
    
    printBody(orgiIndex, maxWordLength);
    
    printLastLine(maxWordLength);
}

//////////////////////////////////////////////////////////////////////
///////////////// DO NOT SUBMIT THE FOLLOWING LINES //////////////////
//////////////////////////////////////////////////////////////////////
int main()
{
    int m, n, sortOption;
    std::cin >> m >> n >> sortOption;
    getchar();
    ReportParser p(m, n);
    p.readReport();
    p.writeStructuredReport(sortOption);
    return 0;
}
