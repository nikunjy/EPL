### Default Constructors
*Throughout the class we will take the example of String class.
*You can write a default constructor like this 
```
 String(void) = default;
```
*Default constructor is going to be generated with the syntax written above. Even if you don't write it its fine, compiler will generate a default constructor for you. 
* A default constructor constructs the members of the class with the default constructors of their corresponding data types. Needless to say watch out for the base class having a default constructor if you are inheriting from one. 

### delete vs delete[]
*delete operator is defined for scalars vs. delete[] for array. 
* Why ? Compiler goes in a loop over the array and calls the destructors over the objects.  
* When you allocate an array like new int[10] you store an allocated area on the heap but you also append the meta-data in the beginning about how many elements would exist here.
Let's look at an example 
```
String *myArray = new String[100]; 
delete myArray 
```` 
This code will fail becasue you have appended bytes to the allocated memory saying that there will follow 100 elements. When you use delete operator it doesn't know that there is 4 bytes added prefixed to the memory. 

### Explicit Constructor 
You will always see in any code worth looking at, that constructors with single argument have keyword explicit in front of them.  



