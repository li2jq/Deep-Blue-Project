#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct signed_num
{
    vector<int> num_part;
    bool sign_part = true; // true -> negative number
};

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cout << "Program format is: basic file_name" << endl;
        return 1;
    }

    ifstream inFile;
    inFile.open(argv[1]);
    // inFile.open("test_case5.txt");

    if(!inFile.is_open())
    {
        cout << "File open error" << endl;
        return 1;
    }

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

        if (full_line[0][0] != '-')
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
    }

    // cout << "The first line number is: " << endl;
    // for (auto i : add_1.num_part)
    // {
    //     cout << i;
    // }
    // cout << endl;
    // cout << "Its sign is " << add_1.sign_part << endl;
    
    found_first_valid_element = false;

    for (int i = 0; i < (full_line[1].size() -1); i++)
    {

        if (full_line[1][0] != '-')
        {
            add_2.sign_part = false;
        }

        if (!found_first_valid_element)
        {
            if (full_line[1][i] == '-' || full_line[1][i] == '+' || full_line[1][i] == '0')
            {
                continue;
            }
            else
            {
                found_first_valid_element = true;
                cout << "The first valid element is " << full_line[1][i] << endl;
            }
        }

        int char_int = full_line[1][i] - '0';
        add_2.num_part.push_back(char_int);
    }

    signed_num res;
    res.num_part;
    int carry = 0;

    if (add_1.sign_part == add_2.sign_part)
    {
        int cycle_num = add_1.num_part.size() > add_2.num_part.size()? add_1.num_part.size() : add_2.num_part.size();
        
        if (cycle_num != add_1.num_part.size())
        {
            // for( int i = 0; i < (cycle_num - add_1.num_part.size()); i++)
            // {
                
            //     add_1.num_part.insert(add_1.num_part.begin(), 0);
            // }
                   add_1.num_part.insert(add_1.num_part.begin(), cycle_num - add_1.num_part.size(), 0);

        }

        if (cycle_num != add_2.num_part.size())
        {
            // for( int i = 0; i < (cycle_num - add_2.num_part.size() + 1); i++)
            // {
                // cout << "Add zero" << endl;
                add_2.num_part.insert(add_2.num_part.begin(), cycle_num - add_2.num_part.size(), 0);
            // }
        }

        reverse(add_1.num_part.begin(), add_1.num_part.end());
        reverse(add_2.num_part.begin(), add_2.num_part.end());

        res.sign_part = add_1.sign_part;
        for (int i = 0  ; i <= cycle_num; i++)
        {
            int remain_num = ( add_1.num_part[i] + add_2.num_part[i] + carry ) % 10;
            if (i == cycle_num)
            {
                if (remain_num == 0 )
                {
                    continue;
                }
            }
            res.num_part.push_back(remain_num);
            carry = ( add_1.num_part[i] + add_2.num_part[i] + carry ) / 10;
            cout << "add_1 num is " << add_1.num_part[i] << " add_2 num is " << add_2.num_part[i] << " res.num_part is " << remain_num << endl;
        }
    }

    else // add_1.sign_part != add_2.sign_part
    {
        signed_num larger_one;
        signed_num small_one;

        if (add_1.num_part.size() != add_2.num_part.size())
        {
            larger_one = add_1.num_part.size() > add_2.num_part.size() ? add_1 : add_2;
            small_one = add_1.num_part.size() < add_2.num_part.size() ? add_1 : add_2;
        }
        else
        {
        int flag = 0; // 1 ---> abs(add_1.num) > abs(add_2.num) ||| 0 ---> abs(add_1.num) == abs(add_2.num) ||| -1  ---> abs(add_1.num) < abs(add_2.num)
            for (int i = 0; i < add_1.num_part.size(); i++)
            {
                if (add_1.num_part[i] > add_2.num_part[i])
                {
                    flag = 1;
                    break;
                }
                else if (add_1.num_part[i] < add_2.num_part[i])
                {
                    flag = -1;
                    break;
                }
                else
                {
                    continue;
                }        
            }

            // if (flag == 0)
            // {
            //     res.num_part.push_back(0);
            //     res.sign_part = false;
            // }
            // else
            {
                if (flag == 1)
                {
                    larger_one = add_1;
                    small_one = add_2;
                }
                else  
                {
                    larger_one = add_2;
                    small_one = add_1;      
                }            
                
            }
        }
        int cycle_num = larger_one.num_part.size();
        small_one.num_part.insert(small_one.num_part.begin(), cycle_num - small_one.num_part.size(), 0);

        reverse(small_one.num_part.begin(), small_one.num_part.end());
        reverse(larger_one.num_part.begin(), larger_one.num_part.end());

        cout << "larger.num_part: " << endl;
        for (auto i : larger_one.num_part)
        {
            cout << i;
        }
        cout << endl << "larger_one.sign_part: " << larger_one.sign_part << endl;                

        for (auto i : small_one.num_part)
        {
            cout << i;
        }
        cout << endl << "small_one.sign_part: " << small_one.sign_part << endl;    
        int borrow_bit = 0;
        for (int i = 0; i < cycle_num; i++)
        {
            if ((larger_one.num_part[i] - borrow_bit) >= small_one.num_part[i])
            {
                int sub_res = (larger_one.num_part[i] - borrow_bit) - small_one.num_part[i];
                res.num_part.push_back(sub_res);
                borrow_bit = 0;
            }
            else
            {
                int sub_res = (larger_one.num_part[i] - borrow_bit) + 10 - small_one.num_part[i];
                res.num_part.push_back(sub_res);
                borrow_bit = 1;
            } 
        }

    }
    reverse(res.num_part.begin(), res.num_part.end());

    cout << "res.num_part: " << endl;
    for (auto i : res.num_part)
    {
        cout << i;
    }
    cout << "res.sign_part: " << res.sign_part << endl;
    

    return 0; 
}
