### Using new in different ways 
There would be scenarios where copy should not be allowed like file handlers, thread etc. In that case you need to declare the copy constructor and the assignment operator as deleted. 
We shall address the following questions: 
* How do we allocate memory for objects but not calle their constructors ? 
* How do we delete the objects but not de allocate the memory for example in case of vectors ? 
Consider this : 
``` 
  Foo *p = new Foo[10]; 
  (p+9)->~Foo(); 
  delete[] p //This deallocates the memory for the array.  
```
For getting  a fine control on the memory, use the operator new and operator delete. 
Write a code that allocates the memory for 10 objects of foo, initialize one of them and then delete it.  
``` 
  Foo *p = (Foo*)operator new (sizeof(foo)*10);
  new (p+2) Foo();
  (p+2)->~Foo();
  operator delete(p);
````

###Templates
```
 template<typename T>  
 class TemplateFoo {
 	T x;
 };
````
* In Java and C# the code is generated with a generic type (like void * in C), and then available for all the data types with appropriate casts generated. 
* In case of C no such generation of code takes place at the compile time.  Compiler does the text substitution when you say TemplateFoo<Foo> f; 
* No checking done whatsoever because in C++ only that part of the class is generated which is used. For example: 
``` 
template <typename T> 
class Vector { 
 public:
 	T *buffer; 
 	Vector() { 
 		buffer = new T[2];
 	}
 	Vector(int size) { 
 		buffer = new T[size]; //You are assuming the object to have a default constructor
 	}
 	void oops() { 
 		T x = *buffer; 
 		x.function_does_not_exist();
 	}
 	T& operator[](int k) {
 		return buffer[k];
 	}
};
Vector<Foo> v; 
```