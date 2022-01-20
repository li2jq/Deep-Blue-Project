#include <iostream>
#include <cstdlib>
#include <map>
#include <iterator>
#include <chrono>
#include <typeinfo>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std::chrono;

double double_with_two_decimal_places(double& ans)
{
    double res = (int) (ans * 100 + 0.5);
    return res/100;
}
int main()
{
    srand(time(0));

    std::map<int, double> wpn_ica; // Wrong Problem Number and its correct answer 
    std::map<int, double> pn_ut; // Problem number and the used time to answer it

    int total_wrong_number(0), total_correct_number(0), total_numbers;
    int difficult_level=-1;
    double total_time(0);
    auto min_time = std::numeric_limits<double>::max();

    std::cout << "How many problems do you want play ?" << "\n";
    std::cin >> total_numbers;

    std::cout << "What's the difficulty level do you want to try ?" << '\n';
    std::cout << '\t' << "1 (Range within 100 and only addtion/substraction included)" << '\n';
    std::cout << '\t' << "2 (Range within 1000 and only addtion/substraction included)" << '\n';
    std::cout << '\t' << "3 (Range within 1000 and addtion/substraction/multiplication/division(keep answer with two decimal places) included)" << '\n';
    std::cout << "Please input the corresponding difficulty level number: ";
    std::cin  >> difficult_level;  

    while (difficult_level != 1 && difficult_level != 2 && difficult_level != 3)
    {
        std::cout << "Invalid difficulty level number! Please input again: ";
        std::cin >> difficult_level;
    }

    for(int i=0; i<total_numbers; i++)
    {   int a,b;
        double ans;
        int arithmetic_choice;
        switch (difficult_level)
        {
        case 1:
            // Addition or substraction within range 100
            a = rand()%100; 
            b = rand()%100;
            arithmetic_choice = rand()%2;
            if (arithmetic_choice == 0)
            {
                ans = a + b;
                std::cout << "Problem " << i << "\n";
                std::cout << a << " + " << b << " = ?" << '\n';
            }
            else
            {
                ans = a - b;
                std::cout << "Problem " << i << "\n";
                std::cout << a << " - " << b << " = ?" << '\n';                
            }
            break;
        case 2:
            // Addition or substraction within range 1000
            a = rand()%1000; 
            b = rand()%1000;
            arithmetic_choice = rand()%2;
            if (arithmetic_choice == 0)
            {
                ans = a + b;
                std::cout << "Problem " << i << "\n";
                std::cout << a << " + " << b << " = ?" << '\n';
            }
            else
            {
                ans = a - b;
                std::cout << "Problem " << i << "\n";
                std::cout << a << " - " << b << " = ?" << '\n';                
            }
            break;
        case 3:
            // Addition, substraction, multiplication or division within range 1000
            a = rand()%1000; 
            b = rand()%1000;
            arithmetic_choice = rand()%4;
            if (arithmetic_choice == 0)
            {
                ans = a + b;
                std::cout << "Problem " << i << "\n";
                std::cout << a << " + " << b << " = ?" << '\n';
            }
            else if (arithmetic_choice == 1)
            {
                ans = a - b;
                std::cout << "Problem " << i << "\n";
                std::cout << a << " - " << b << " = ?" << '\n'; 
            }
            else if (arithmetic_choice == 2)
            
            {
                ans = a * b;
                std::cout << "Problem " << i << "\n";
                std::cout << a << " * " << b << " = ?" << '\n';                
            }
            else
            {   
                while (b == 0)
                {
                    b = rand()%1000;
                }

                ans = double(a) / b;
                std::cout << "Problem " << i << "\n";
                std::cout << a << " / " << b << " = ?" << '\n';  
                ans = double_with_two_decimal_places(ans);
            }
            break;

        }

        double usrans;
      
        auto start = high_resolution_clock::now();
        std::cin >> usrans;
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        
        total_time += duration.count();

        // Not Concise

        min_time = std::min(min_time, double(duration.count()));
        // if(i==0)
        // {
        //     min_time = duration.count();
        // }
        // else
        // {
        //     if(duration.count() < min_time)
        //     {
        //         min_time = duration.count();
        //     }
        // }

        pn_ut.insert(std::pair<int, double> (i, duration.count()));

        if (fabs(usrans - ans) > 0.01)
        {
            wpn_ica.insert(std::pair<int, double> (i, ans));
            ++total_wrong_number; 
        }    
    }

    total_correct_number = total_numbers - total_wrong_number;
    std::cout << "Total correct number is " << total_correct_number << '\n';
    std::cout << "Total wrong number is " << total_wrong_number << '\n';

    for(auto itr = wpn_ica.begin(); itr != wpn_ica.end(); ++itr)
    {
        std::cout << "The correct answer for Problem " << itr->first << " is " << itr->second << "\n";
    }

    std::cout << "The average time used for " << total_numbers << " Problems is " << total_time/total_numbers << " milliseconds" << '\n';
    std::cout << "The minimum time is " << min_time << " milliseconds."<<'\n';
    return 0;
}
