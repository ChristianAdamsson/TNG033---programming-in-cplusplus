#include <iostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
//void display(const std::pair<std::string, int>& p);

void display(const std::pair<std::string, int>& p)
{

    std::cout << std::setw(15) << std::left << p.first << std::setw(30) << std::left << p.second << std::endl;
}

struct less_second {
    bool operator ()(std::pair<std::string,int>  &v1 , std::pair<std::string,int>  &v2  ) const {
        return (v1.second > v2.second);
    }
};

//std::ifstream in_file;
std::string in_string;
std::string in_file_string;

int main()
{

std::cout << "please enter filename:";

std::cin >> in_file_string;
std:: ifstream in_file(in_file_string);

if (!in_file){
    std::cout << "file does not exist";
}
else{
std::map<std::string, int> myMap;
int counter_numbofwords = 0;




while(in_file >> in_string)
{

    std::transform(in_string.begin(), in_string.end(), in_string.begin(), ::tolower);
    in_string.erase(std::remove_if (in_string.begin(), in_string.end(), ispunct), in_string.end());

    myMap[in_string]++;
    ++counter_numbofwords;

}

//sort(myMap.begin(), myMap.end());

std::cout << "number of words:" << counter_numbofwords << std::endl;
std::cout << "number of unique words:" << myMap.size() << std::endl;

std::for_each(myMap.begin(), myMap.end(), display);


//std::vector<std::pair<std::string, int> > mapcopy(myMap.begin(), myMap.end());
//std::sort(mapcopy.begin(), mapcopy.end(), less_second());
//std::cout << std::endl << "descending order:" << std::endl;
//
//std::for_each(mapcopy.begin(), mapcopy.end(), display);
////std::for_each(myMap.begin(), myMap.end(), display);

return 0;
}
}
