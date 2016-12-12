/*

* next_int_perm.cpp program identifies and provides the following integer

* of any given input using C++ next_permutation method.

*

* C++ has a built in function std::next_permutation as part of algorithms

* library. Next_permutation ouputs lexicographically ordered permutations

* for the input range.

*

*/

#include <algorithm>

#include <cstdio>

#include <cstdlib>

#include <fstream>

#include <string>

 

using namespace std;

 

/*

* parse is a helper function to parse a given string

* and append "0" if necessary based on leftover value.

*

* Input:  @line  - input read from the file.

*

* Output: @string  - sorted parsed string.

*/

 

string parse(string line)

{

    sort(line.begin(), line.end());

    int leftover = 6 - line.size();

    string pad;

    for (int i = 0; i < leftover; ++i)

        pad += "0";

    return (pad + line);

}

 

/*

* main function which accepts input file name as a command line arguments

* and reads input data from that file and finds the following integer of

* read input. It treats each line as one input from the file until it finds

* end of file. It uses C++ standard methods like sort, next_permutation

* atoi to find the next following integer.

*

* On success it outputs following integers for each line of input

* otherwise it retuens (0).

*

* Input: @argv - input file name and path.

*

* Output: Prints valid following integer for each input in the file.

*/

 

int main(int argc, char* argv[])

{

    ifstream myfile(argv[1]);

    string line;

 

    if(myfile)

    {

        while(getline(myfile, line))

        {

            int range = atoi(line.c_str());

            string digits = parse(line);

            sort(digits.begin(), digits.end());

            while (next_permutation(digits.begin(), digits.end()))

            {

                int val = atoi(digits.c_str());

                if (val > range)

                {

                    printf("%d\n", val);

                    break;

                }

            }

        }

        myfile.close();

    }

    return 0;

}