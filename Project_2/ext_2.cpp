#include <fstream>
#include <iostream>
#include <sstream>
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
    if(argc != 3)
    {
        std::cout << "Program format is: ext_1 file_name.txt input_base_num(int) output_base_num(int)" << endl;
        return 1;
    }

    int input_base_num = std::stoi(argv[2]);

    if (input_base_num < 1 || input_base_num > 36)
    {
        std::cout << "Invalid input base number!" << endl;
        return 1;
    }

    int output_base_num = std::stoi(argv[3]);

    if (output_base_num < 1 || output_base_num > 36)
    {
        std::cout << "Invalid output base number!" << endl;
        return 1;
    }

    ifstream inFile;
    inFile.open(argv[1]);

    if(!inFile.is_open())
    {
        std::cout << "File open error" << endl;
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
        std::stringstream ss(line);
        std::string trimmed_string;
        ss >> trimmed_string;
        full_line.push_back(trimmed_string);
        ++count;
    }

    signed_num add_1;
    signed_num add_2;

    bool found_first_valid_element = false;

    for (int i = 0; i < full_line[0].size(); i++)
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
            }
        }
        int char_int;
        if (full_line[0][i] >= '0' && full_line[0][i] <= '9')
        {
            char_int = full_line[0][i] - '0';
        }
        else if (full_line[0][i] >= 'A' && full_line[0][i] <= 'Z')
        {
            char_int = full_line[0][i] - 'A'+ 10;
        }
        else if (full_line[0][i] >= 'a' && full_line[0][i] <= 'z')
        {
            char_int = full_line[0][i] - 'a'+ 10;
        }
        else
        {
            std::cout << "Invalid num!" << endl;
            return 1;
        }
        
        add_1.num_part.push_back(char_int);
    
    }

    int max_add_1 = *max_element(add_1.num_part.begin(), add_1.num_part.end());

    if (max_add_1 > input_base_num)
    {
        std::cout << "Invalid input: Num element > num base" << endl;
        return 1;
    }
    
    found_first_valid_element = false;

    for (int i = 0; i < full_line[1].size(); i++)
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
            }
        }

        int char_int;
        if (full_line[1][i] >= '0' && full_line[1][i] <= '9')
        {
            char_int = full_line[1][i] - '0';
        }
        else if (full_line[1][i] >= 'A' && full_line[1][i] <= 'Z')
        {
            char_int = full_line[1][i] - 'A'+ 10;
        }
        else if (full_line[1][i] >= 'a' && full_line[1][i] <= 'z')
        {
            char_int = full_line[1][i] - 'a'+ 10;
        }
        else
        {
            std::cout << "Invalid num!" << endl;
            return 1;
        }
        add_2.num_part.push_back(char_int);
    }

    int max_add_2 = *max_element(add_2.num_part.begin(), add_2.num_part.end());

    if (max_add_2 > input_base_num)
    {
        std::cout << "Invalid input: Num element > num base" << endl;
        return 1;
    }

    signed_num res;
    res.num_part;
    int carry = 0;

    if (add_1.sign_part == add_2.sign_part)
    {
        int cycle_num = add_1.num_part.size() > add_2.num_part.size()? add_1.num_part.size() : add_2.num_part.size();
        
        if (cycle_num != add_1.num_part.size())
        {
            add_1.num_part.insert(add_1.num_part.begin(), cycle_num - add_1.num_part.size(), 0);

        }

        if (cycle_num != add_2.num_part.size())
        {
            add_2.num_part.insert(add_2.num_part.begin(), cycle_num - add_2.num_part.size(), 0);
            
        }

        std::reverse(add_1.num_part.begin(), add_1.num_part.end());
        std::reverse(add_2.num_part.begin(), add_2.num_part.end());

        res.sign_part = add_1.sign_part;
        for (int i = 0  ; i <= cycle_num; i++)
        {
            int remain_num = ( add_1.num_part[i] + add_2.num_part[i] + carry ) % input_base_num;
            if (i == cycle_num)
            {
                if (remain_num == 0 )
                {
                    continue;
                }
            }
            res.num_part.push_back(remain_num);
            carry = ( add_1.num_part[i] + add_2.num_part[i] + carry ) / input_base_num;
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
        int cycle_num = larger_one.num_part.size();
        small_one.num_part.insert(small_one.num_part.begin(), cycle_num - small_one.num_part.size(), 0);

        std::reverse(small_one.num_part.begin(), small_one.num_part.end());
        std::reverse(larger_one.num_part.begin(), larger_one.num_part.end());
  
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
                int sub_res = (larger_one.num_part[i] - borrow_bit) + input_base_num - small_one.num_part[i];
                res.num_part.push_back(sub_res);
                borrow_bit = 1;
            } 
        }
        res.sign_part = larger_one.sign_part;

    }

    for (int i = (res.num_part.size()-1); i >= 0; --i)
    {
        if (res.num_part[i] != 0)
        {
            break;
        }
        else {
            res.num_part.pop_back();
        }
        
    }

    std::reverse(res.num_part.begin(), res.num_part.end());

    if (res.num_part.size() == 0)
    {
        res.num_part.push_back(0);
        res.sign_part = false;
    }
    
    string res_str = "";

    if (res.sign_part == true)
    {
        res_str += '-';
    }

    char ele;
    for (auto i : res.num_part)
    {
        if (i >= 0 && i <=9)
        {
            ele = i + '0';
        }
        else
        {
            ele = i - 10 + 'A'; 
        }
        
        res_str += ele;
    }

    std::cout << res_str << endl;

    return 0; 
}
