#include <iostream>
#include <cstdlib>
#include <map>
#include <iterator>
#include <chrono>
#include <typeinfo>

using namespace std::chrono;
int main()
{
    srand(time(0));

    std::map<int, int> wpn_ica; // Wrong Problem Number and its correct answer 
    std::map<int, double> pn_ut; // Problem number and the used time to answer it

    int total_wrong_number(0), total_correct_number(0), total_numbers;

    double total_time(0), min_time(0);

    std::cout << "How many problems do you want play ?" << "\n";
    std::cin >> total_numbers;

    for(int i=0; i<total_numbers; i++)
    {   
        int a = rand()%100; 
        int b = rand()%100;
        int ans = a + b;
        int usrans;

        std::cout << "Problem " << i << "\n";
        std::cout << a << " + " << b << " = ?" << '\n';
        
        auto start = high_resolution_clock::now();
        std::cin >> usrans;
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        
        // Not Concise
        if(i==0)
        {
            min_time = duration.count();
        }
        else
        {
            if(duration.count() < min_time)
            {
                min_time = duration.count();
            }
        }


        pn_ut.insert(std::pair<int, double> (i, duration.count()));
        if (usrans != ans)
        {
            wpn_ica.insert(std::pair<int, int> (i, ans));
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

    for(auto itr = pn_ut.begin(); itr != pn_ut.end(); ++itr)
    {
        total_time += itr->second;
    }

    std::cout << "The average time used for " << total_numbers << " Problems is " << total_time/total_numbers << " milliseconds" << '\n';
    std::cout << "The minimum time is " << min_time << '\n';
    return 0;
}
