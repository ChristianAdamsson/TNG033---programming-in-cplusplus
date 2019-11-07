/*****************************************
* Lab 4: uppgift 3                       *
* PrettyPrinter for containers           *
* Author: Martin Falk                    *
******************************************/

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <utility>

/*******************************
* 1. Declarations              *
*******************************/

using PAIR = std::pair<std::string, std::set<std::string>>;
using Map_type = std::map<std::string, std::set<std::string>>;


/*********************************
* 2. Add class PrettyPrinter here*
*********************************/
class PrettyPrinter
{
public:
    PrettyPrinter(std::ostream& o, int i, char c);

    template<class Iterator>
    void print(std::string s, Iterator start_it, Iterator end_it);

    template<class T>
    void print(std::string s, T t);


    private:
    std::ostream& os;
    int indentation;
    char separator;
};

template <class Iterator>
void PrettyPrinter::print(std::string s, Iterator start_it, Iterator end_it)
 {
    os << s << "={\n";
    int counter = 0;
    for(;start_it != end_it; start_it++)
    {
        if(counter != 0)
        os << separator << std::endl;
            os << std::setw(indentation) << std::setfill(' ') << *start_it;
        counter++;
    }
    os << std::endl;
    os << "}";
 }
template<class T>
void PrettyPrinter::print(std::string s, T t)
{
    print(s, t.begin(), t.end());
}

template<class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2> p)
{
    os << "{" << p.first << "{" << p.second << " }}";
    return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::set<T> s)
{
    copy(s.begin(), s.end(), std::ostream_iterator<T>(os, ","));
    return os;
}
/*****************************************
* 3. Add stream insertion operators here *
******************************************/

PrettyPrinter::PrettyPrinter(std::ostream& o, int i, char c)
    : os(o), indentation(i), separator(c) {}

/*******************************
* 4. Main function             *
*******************************/

int main()
{
    /*** Part 1 ***************
     * Create a pretty printer *
     **************************/
    PrettyPrinter pp(std::cout, 2, ',');


    /*** Part 2 **************
     * Pretty print a vector *
     *************************/
    std::vector<int> v = {1, 2, 3, 4, 5};

    pp.print("vector v", v.begin(), v.end());


    /*** Part 3 **********************************
     * Pretty print using the container function *
     *********************************************/
    pp.print("\nvector v", v);

    /*** Part 4 ************
     * Pretty print a map  *
     ***********************/
    std::map<int, std::string> m = {{1, "first"}, {2, "second"}, {3, "third"}};

    pp.print("\nmap m", m);

    /*** Part 5 **************************
     * Pretty print an anagram container *
     *************************************/

    //replace this with the anagram container created from the input file
  Map_type s = {{"first", {"f", "i", "r", "s", "t"}},
                 {"second", {"s", "e", "c", "o", "n", "d"}}};

    pp.print("\nAnagram map", s);

    // this is the anagram map created from uppgift2_kort.txt
    s = {{"adegimnr", {"dreaming", "margined", "midrange"}},
         {"aekl", {"kale", "lake", "leak"}},
         {"aelrs", {"earls", "lares", "laser", "rales", "reals", "seral"}},
         {"cehiknt", {"kitchen", "thicken"}},
         {"ceilmopr", {"compiler", "complier"}},
         {"hist", {"hist", "hits", "shit", "this"}}};

    pp.print("\nAnagram map", s);

    return 0;
}
