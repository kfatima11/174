/*

*

* next_int.c program identifies and provides the following integer of any given

* integer input.

*

* Suppose you have a fixed list of digits chosen from the range 1..9.

* What numbers can you make with them? You’re allowed as many zeros as you want.

*

* Example : if you are writing your number with two 1’s and one 5

* 1,1,5

*

* Possible list in ascending order :

* 115,151,511,1015,1051

* Constraint : The number of 1s,2s,…9s is fixed but number of 0s is arbitrary.

*

* next_int.c will accept as ts first argument a path to a filename.

* Each line in this file is one test case.

*

* Input : Each test case will contain an integer n < 10^6.

* Output: For each test case output which is the next integer in the list.

* 115  -> 151

* 842 -> 2048

* 8000  -> 80000

* 50110812884911623516 ? 50110812884911623561

* 82454322474161687049 ? 82454322474161687094

* 82040229261723155710 ? 82040229261723157015

* 43888989554234187388 ? 43888989554234187838

* 76080994872481480636 ? 76080994872481480663

* 31000989133449480678 ? 31000989133449480687

* 20347716554681051891 ? 20347716554681051918

*

*/

 

#include <stdio.h>

 

#include <string.h>

 

 

/*

* Invalid index in an array.

*/

#define INVALID_INDEX   (-1)

/*

* Maimum buffer size is used to read data from an input file.

*/

#define BUFF_SIZE       (1024)

 

 

 

/*

* byte_swap is a helper function to swap bytes pointed by p1 and p2 pointers.

*/

 

void byte_swap (char *p1, char *p2)

 

{

    char temp = 0;

 

    if (!p1 || !p2) return;

 

    temp = *p1;

    *p1 =  *p2;

    *p2 = temp;

 

}

 

/*

* string_reversal is a helper function which reverse data in character

* array pointed by str from start offset to end offset.

*

* Input: @str     - pointer to an array of charecters.

*        @start   - start offset in an array pointed by str parameter.

*        @end     - end offset in an array pointed by str parameter.

*

* Output: N/A

*/

 

void string_reversal (char *str, unsigned int start, unsigned int end)

 

{

    char temp = 0;

 

    /*

     * parameter validation

     */

    if (!str || (start == end)) return;

 

    /*

     * while loop to traverse the character array from start and end offsets

     * to swap the data between them; this loop will continue until

     * start offset less than end offset. By end of this loop data pointed

     * by str and start and end offset will be reversed.

     */

 

    while (start < end) {

 

        temp = str[start];

 

        str[start] = str[end];

 

        str[end] = temp;

 

        start++;

 

        end--;

 

    }

}

 

 

/*

* main function which accepts input file name as a command line arguments

* and reads input data from that file and finds the following integer of

* read input. It treats each line as one input from the file until it finds

* end of file. It uses byte_swap and string_reversal helper functions to

* solve the problem.

* On success it outputs following integers for each line of input

* otherwise it retuens (-1).

*

* Input: @argv - input file name and path.

*

* Output: Prints valid following integer for each input in the file.

*/

 

int main(int argc, char *argv[]) {

 

 

 

    char buff[BUFF_SIZE];

 

    FILE *fp = NULL;

 

 

 

    /*

     * opening input file for reading input integers.

     */

    if ((fp = fopen(argv[1], "r")) == NULL) {

 

        printf("Input file not found...\n");

 

        return -1;

 

    }

 

    /*

     * loop through all the inputs present in the file.

     * it breaks when there is no more input (EOF)

     */

    while (fgets(buff, sizeof(buff), fp) != NULL) {

 

        int i = 0, cur = 0, len = 0;

 

        if (buff[strlen(buff) - 1] == '\n') {

 

            buff[strlen(buff) - 1] = '\0';

 

        }

 

        len = strlen(buff);

 

        cur = len - 2;

 

        /*  Traverse the number Right to left to check if the digits are in

         *  ascending order if not break from the loop to get the index

         *  where the order is broken

         */

 

        while ((cur >= 0) && (buff[cur] >=  buff[cur + 1])) {

 

            cur -= 1;

 

        }

 

        /* Case 1: If the suffix is whole range with no prefix */

 

        if (cur == INVALID_INDEX) {

 

            /* Reverse the Number to get 248 */

 

            string_reversal(buff, 0, len - 1);

 

            if (buff[0] == '0') {

 

                int indx = 1;

 

                while (buff[indx] == '0') indx++;

 

                byte_swap(&buff[0], &buff[indx]);

            }

 

 

            /* After reversing the number add 0 after 1st digit to get 2048 */

 

            for (i = 0; i < len; i += 1) {

 

                putchar(buff[i]);

 

                if (i == 0) putchar('0');

 

            }

 

            putchar('\n');

 

        } else {

 

            /* Case 2: If the suffix is not whole range and has a prefix */

 

            int end = len - 1;

 

            while ((end > cur) && (buff[end] <= buff[cur])) end -= 1;

 

            byte_swap(&buff[cur], &buff[end]);

 

            /* Reverse the Suffix */

 

            string_reversal(buff, cur+ 1, len -1);

 

            for (i = 0; i < len; i += 1) {

 

                /*Display the Result */

                putchar(buff[i]);

            }

 

            putchar('\n');

        }

    }

 

    fclose(fp);

 

    return 0;

}

 