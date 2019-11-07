#include <iostream>
#include <string>
#include <iomanip>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <fstream>






typedef std::pair<std::string, std::set<std::string>> Pair;

typedef std::map<std::string, std::set<std::string>> Map;

void display(const Pair& a)
{
        if (a.second.size() > 1)
        {
           std::ostream_iterator<std::string> out_it(std::cout, " ");
           copy(a.second.begin(), a.second.end(), out_it);

        std::cout << " --> "
                << a.second.size() << " words." << std::endl;
        }
}


bool less_than(const Pair& a, const Pair& b)
{
    return (a.second.size() < b.second.size());
}


std::ifstream infile("uppgift2.txt");

int main()
{

    Map anagrams;

    int counter = 0;


    if (!infile)
    {
        std::cout << "Could not be opened!!" << std::endl;
        return 0;
    }

    std::string instring;

    while (infile >> instring)
    {
        std::string sorted_s = instring;
        std::sort(sorted_s.begin(), sorted_s.end());


        anagrams[sorted_s].insert(instring);

        counter++;
    }


    std::cout << "\nNumber of words = " << counter << std::endl;

    std::cout <<"\n-- ANAGRAMS --" << std::endl;

    for_each(anagrams.begin(), anagrams.end(), display);


    Map::iterator it = max_element(anagrams.begin(), anagrams.end(), less_than);

    return 0;
}
