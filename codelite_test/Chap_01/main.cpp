#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

struct signed_num
{
    vector<int> num_part;
    bool sign_part = true; // true -> positive number
};

// void openFile(ifstream&, string);
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Program format is: basic file_name" << endl;
        return 1;
    }

    ifstream inFile;
    inFile.open(argv[1]);
    if(!inFile.is_open())
    {
        cout << "File open error" << endl;
        return 1;
    }
    // openFile(inFile, argv[1]);

    string line;
    vector<string> full_line;
    int count = 0;
    while (getline(inFile, line))
    {
        if (count > 1)
        {
            break;
        }
        full_line.push_back(line);
        ++count;
    }

    signed_num add_1;
    signed_num add_2;

    bool found_first_valid_element = false;
    
    for (int i = 0; i < (full_line[0].size() -1); i++)
    {
        // if ( i == 0)
        // {
        //     if (full_line[0][0] == '-')
        //     {
        //         add_1.push_back(1);
        //     }

        //     else
        //     {
        //         add_1.push_back(0);
        //     }
        // }
        if (full_line[0][0] == '-')
        {
            add_1.sign_part = false;
        }

        if (!found_first_valid_element)
        {
            if (full_line[0][i] == '-' || full_line[0][i] == '+' || full_line[0][i] == '0')
            {
                continue;
            }
            else
            {
                found_first_valid_element = true;
                cout << "The first valid element is " << full_line[0][i] << endl;
            }
        }

        int char_int = full_line[0][i] - '0';
        add_1.num_part.push_back(char_int);


        // while (!found_first_valid_element){
        //     if (full_line[0][i] == '-' || full_line[0][i] == '+' || full_line[0][i] == '0')
        //     {
        //         continue;
        //     }
        //     else
        //     {
        //         found_first_valid_element = true;
        //     }
            
        // }

    }

    for (auto i : add_1.num_part)
    {
        cout << i;
    }

    // for (auto i:full_line)
    // {
    //     for(char&c :i)
    //     {
    //         int ic = c - '0';

    //     }
    // }

    // char ch;
    // std::fstream fin("test.txt", std::fstream::in);

    // while (fin >> std::noskipws >> ch)
    // { 
    //    std::cout << ch;
    // }

    return 0; 
}

// void openFile(ifstream& inFile, string fname)
// {
//     inFile.open(fname);
//     if (inFile.is_open())
//     {
//         cout << "File open successed!" << endl; 
//     }
//     else
//     {
//         cout << "File open failed" << endl;
//         exit(-1);
//     }
// }