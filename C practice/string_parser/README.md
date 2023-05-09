# This is a simple task of string parsing
(Attention: machine translation used)  
Write a program in C:  
Write a program that reads a string from the keyboard and displays its result on the screen.  
The string expression is an expression containing binary addition operations  
(denoted by the "+" symbol), subtraction (-), and multiplication (*).  
The priority of these operations is determined by the standard rules. Parentheses are also allowed in the expression  
to manipulate the precedence of the subexpressions in the main expression. The end of the string expression is determined by the end-of-line character.  
The operands of these operations can be strings and real non-negative numbers. Line  
is a sequence of Latin letters, numbers and question marks (?), enclosed on both   
sides in double quotes, the numbers are written in the decimal system according to the usual rules.  
String expression example:  
"abc" + ("a" + 1.1 * "b") * (2 - "c?" * 0.4) (1)  
Before the expression is evaluated, each real number x from it must be converted to  
a string consisting of floor(x) + 1 question marks with probability {x} = x − floor(x) and consisting of floor(x)
question marks with probability 1 − {x}
So, for example, expression (1) should be converted to one of the following:  
"abc" + ("a" + "?" * "b") * ("??" - "c?" * "") with probability 0.54 = 0.9 * 1 * 0.6 (2)  
"abc" + ("a" + "??" * "b") * ("??" - "c?" * "") with probability 0.06 = 0.1 * 1 * 0.6 (3)  
"abc" + ("a" + "?" * "b") * ("??" - "c?" * "?") with probability 0.36 = 0.9 * 1 * 0.4 (4)  
"abc" + ("a" + "??" * "b") * ("??" - "c?" * "?") with probability 0.04 = 0.1 * 1 * 0.4 (5)  
Further, the string expression is evaluated according to the following rules for performing operations:  
• The addition (+) operator concatenates strings:  
"abc" + "ba" → "abcba"  
"abc" + "???" → "abc???"  
• The subtraction (-) operation iterates over the characters in the second string.  
The string obtained from the first string by removing the first occurrences of the iterated characters is the result:  
"abcabc" - "ba" → "sabc"  
"abcabc" - "cab" → "abc"  
"abcabc" - "A" → "abcabc"  
"abc" - "abbaaccc" → ""  
The question mark character is a special character: the result of testing it for equality to any  
character is always true. For example, when trying to remove its first occurrence from the first row  
it always removes the first character of the string:  
"abcabc" - "???" → "abc"  
"abc???" - "???" → "???"  
"abc" - "A?" → "bc"  
"abc" - "?????" → ""  
"abc" - "??" → "c"  
"abc" - "" → "abc"  
If, when deleting the iterated character, a question mark was encountered in the first line before this character, then the question mark is removed:  
"a?b?c?" - "abc" → "bc?"  
"a?b?c?" - "cba" → "?c?"  
"a?b?c?" - "ccc" → "ab?"  
"a?b?c?" - "ABCD?" → "bc"  
"??" - "a" → "?"  
"" - "a" → ""  
• The multiplication operator (*) compares the lengths of the following two strings: the string that is obtained 
from the first string by replacing all question marks with copies of the second string, and the string obtained by replacing  
question marks of the second string by copies of the first string. The string with the largest  
length is declared as the result of the operation. If the lengths of the strings are the same, then the priority  
given to the string obtained by replacements from the first string:  
"a?c" * "b" → "abc"  
"a?" * "bcabc" → "abcabc"  
"a?b?c?" * "" → "abc"  
"abc"*"?" → "abc"  
"a?b?" * "A??" → "Aa?b?a?b?"  
"a?" * "A?" → "aA?"  
"abc" * "cba" → "abc"  
"abc" * "cbac" → "cbac"  
• If, as a result of the expression evaluated, a string consisting of only question marks is obtained, then  
it is converted to the number equal to the length of the string. In particular, an empty string is converted to a number  
zero.  
The program should display all possible variants of the value of the expression and their probabilities. For example,  
after calculating the results of expressions (2) - (5), we obtain the result of the expression (1) which is equal to  
(2) → "abc" + "ab" * "?" → "abcab" with probability 0.54  
(3) → "abc" + "abb" * "?" → "abcabb" with probability 0.06  
(4) → "abc" + "ab" * "" → "abcab" with probability 0.36  
(5) → "abc" + "abb" * "" → "abcabb" with probability 0.04  
After summing the probabilities for the same rows, we get that "abcab" has a probability of 0.9, and  
"abcabb" has a probability of 0.1. The output of the program should look like the following:  
"abcab", P=0.9  
"abcabb", P=0.1  
Other examples:  
• For Expression  
2*2  
the output should be:  
4, P=1  
• For Expression  
0.5*2  
the output should be:  
0, P = 0.5  
2, P = 0.5  
• For Expression  
0.5 * "a" + 0.5 * "b"  
the output should be:  
"ab", P=1  
Technical details:  
1. The calculation of probabilities can be done, if desired, both analytically (multiplying the probabilities) and  
and numerically (for example, Monte Carlo methods).  
2. It may be assumed that the numbers in the expression are written either as integers in the decimal system:  
1, 10, 123, or as floating-point real numbers with one-digit precision: 0.1, 12.5.  
3. It may be assumed that the expression is written correctly, error handling may be omitted.  
4. Line output may be done in any order.  
5. Spaces must be ignored, for example, the expression 2*2 must produce the same as 2    *     2
