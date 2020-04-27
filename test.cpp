#include <iostream>
#include <map>
#include <string>

using namespace std;
int main()
{
    // map declaration
    map<string, int> mymap;

    // mapping strings to integers
    mymap["hi"] = 1;
    mymap["welcome"] = 2;
    mymap["thanks"] = 3;
    mymap["bye"] = 4;

    // printing the integer mapped
    // by string "thanks"
    cout << mymap.at("thanks");
    return 0;
}
