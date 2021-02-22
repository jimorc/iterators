#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "values.h"

using namespace std;

class Simple : public Value<std::string> 
{
    public:
        Simple(const std::string& str) : Value(str) {}
        Simple(const Simple&) = default;
        Simple(Simple&&) = default;
        Simple& operator=(const Simple&) = default;
        Simple& operator=(Simple&&) = default;
};


class Container : public Values<Simple>
{
    public:
    using value_type = Simple;
        Container() {}
        virtual ~Container() {}
};

int main()
{
    Container cont;
    cont.push_back(Simple("String 1"));
    Simple simp2("String 2");
    cont.push_back(simp2);
    cont.push_back(Simple("String 3"));

    cout << "Values using a range-based for\n";
    // prints:
    // String 1
    // String 2
    // String 3
    for (auto& simple : cont)
    {
        cout << simple.getValue() << '\n';
    }
    cout << "Values using a reverse iterator\n";
    // prints:
    // String 3
    // String 2
    // String 1
    for (auto iter = cont.rbegin(); iter != cont.rend(); ++iter)
    {
        cout << iter->getValue() << '\n';
    }

    const Container cSimp = cont;
    cout << "Values from a const container\n";
    // prints:
    // String 1
    // String 2
    // String 3
    for (auto iter = cSimp.cbegin(); iter != cSimp.cend(); ++iter)
    {
        cout << (*iter).getValue() << '\n';
    }
    cout << "Values using a constant reverse iterator\n";
    // prints:
    // String 3
    // String 2
    // String 1
    for (auto iter = cSimp.crbegin(); iter != cSimp.crend(); ++iter)
    {
        cout << iter->getValue() << '\n';
    }

    Container cont2 = cont;
    cout << "Contents of cont2:\n";
    // prints:
    // String 1
    // String 2
    // String 3
    for (auto iter = cont2.begin(); iter != cont2.end(); ++iter)
    {
        cout << iter->getValue() << '\n';
    }
    reverse_copy(cont.begin(), cont.end(), cont2.begin());
    cout << "Contents of cont2 after reverse_copy:\n";
    // prints:
    // String 3
    // String 2
    // String 1
    for (auto iter = cont2.begin(); iter != cont2.end(); ++iter)
    {
        cout << iter->getValue() << '\n';
    }

    fill(begin(cont2), end(cont2), Simple("String 4"));
    cout << "Contents of cont2 after fill:\n";
    // prints:
    // String 4
    // String 4
    // String 4
    for (auto& val: cont2)
    {
        cout << val.getValue() << '\n';
    }

    cout << "Contents of cont2 after copy with inserter\n";
    copy(cont.begin(), cont.end(), inserter(cont2, ++cont2.begin()));
    // prints:
    // String 4
    // String 1
    // String 2
    // String 3
    // String 4
    // String 4
    for (auto& val: cont2)
    {
        cout << val.getValue() << '\n';
    }
}