### Default Constructors
* Throughout the class we will take the example of String class.
* You can write a default constructor like this 
```
 String(void) = default;
```
* Default constructor is going to be generated with the syntax written above. Even if you don't write it its fine, compiler will generate a default constructor for you. 
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

So when do I use delete, delete[]  ?  

Well use delete when you have used new, use delete[] when you used new[] to allocate memory and operator delete when you used operator new and so on so forth.

### Explicit Constructor 
You will always see in any code worth looking at, that constructors with single argument have keyword explicit in front of them.  

This is because C++ tries to do an implicit conversion. A good example is the following : 

```
class Foo { 
 public: 
  int x;
  Foo(int _x) {
  	this->x = _x;
  }
};
void function(Foo f) {
	 //do something with f
}
int main() { 
  function(42); //This is the problem 
}
```

As you see in this example, C++ can convert the integer because there is a constructor with integer argument. Explicit constructor stops the calling the constructor for implicit conversions. 

###Copy Constructor 
In C++ you operate in copies, copies are always allowed. So either delete the copy constructor or make a copy constructor that can do deep copy. If you want to avoid the problem of double delete. You can look at this in the String_first_version.cpp in this folder. Just turn on the DOUBLE_DELETE_PROBLEM macro. 
There might be valid scenarios where you don't want the object to be copied at all, like file handlers, or threads. In that case you have to declare the copy constructor or the assignment operator as deleted. Notice the source Stirng_first_version.cpp and follow the use of the macro COPY_DISABLED

###Assignment Operator 
It should be pretty much same as the copy constructor. Keep in mind some things : 
* Assignment operator should delete the object contained within and copy the argument 
* Assignment operator should return a reference to the object because you can have cascading operators like a = b = c.  
* Ofcourse you can decide between returning a value, a reference or a const reference for that matter. 
* In assignment operator always check if (this == &that), because somebody can do X = X and you don't want to delete this and then copy that as written in the first point in that case.
* Generally people make private methods copy(), destroy() and move() and just use them in copy constructors, move constructors, assignemnt operators. 