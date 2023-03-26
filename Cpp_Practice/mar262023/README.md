# Task:
1. In the box, there are two apples, each of which can be light or heavy. The box is considered light if both apples in it are light. Define the base class "Box" and the derived classes "HeavyBox" and "LightBox". The base class data fields should only contain information about the two apples in the box. Overload the operator ^ so that it can be used with objects of both the "HeavyBox" and "LightBox" classes. When this operation is performed, one apple is selected from each operand box, which are then placed in a new box. If the resulting box has a weight (heavy or light) that matches the weight of at least one of the operands, the ^ operator should return true, otherwise false.

2. Add a method to the classes that outputs the weight of the box and the apples in it to the standard output. In the base class, this method should be abstract, and there should be no additional data fields in the classes. Overload the + operator so that it does the same thing as the ^ operator, but returns a pointer to the dynamic memory area where an object of either the "HeavyBox" or "LightBox" class is located, depending on the type of the received box.  

3. (alternative version of task 2 for +1 point) Using "smart" pointers or a class that emulates their work, override the + operator in such a way that its repeated application is correct: p1 + p2 + p3.  

4. (additional task for +1 point) Define the classes "Square General Matrix" and "Diagonal Matrix" in such a way that objects of the "General Matrix" class occupy N^2 variables of type double, and objects of the "Diagonal Matrix" class occupy N variables of type double, where N is the size of the matrix. Overload the + operator with two external functions so that the sum of two diagonal matrices gives a diagonal matrix, and the sum of a general matrix with any other matrix gives a general matrix.  

5. (additional task for +1 point) Write a class "Array of 2 integer elements" and overload the [] and << operators for it in such a way that writing to the array is successful, but reading from it results in an error (compile-time or run-time):  

Copy code
Array m;
m[0] = 1; // OK
m[1] = 2; // OK
cout << m; // Prints 1 2
m[1]++; // error
m[1] += 1; // error
m[1] = m[0] + m[1]; // error
int n = m[0]; // error

Hint: You can use custom auxiliary classes

Translation from Ru to Eng provided by ChatGPT
