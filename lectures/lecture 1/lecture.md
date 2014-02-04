### Class Basics
* class default access private 
* struct default access public   
* use any of these, struct just for backward compatible 
* Get used to using int32_t int64_t uint32_t etc, these are found in #include <cstdin> 

```
class Foo {
   private : 
      int32_t x;
      double y; 
      static int32_t z;
};
Foo f; 
```
* sizeof(f) can be 12 or 16 depending on the compiler optimization because bytes are padded in the end to make access aligned

### Static Variables in Classes or Struct 
* Getting a static component makes no difference to the sizeof(f). Static is basically a global variable. Why would you use the static variable? Namespace would be an example when you don’t want to conflict the global names.  
* You need to explicitly define a static variable, a public or a private member can be defined like this
 * int32_t Foo::z
 * Even private variables are defined like this. 
 * Why is that ? Because static is there in the header files and if the static members were by default defined then on multiple inclusions of the file multiple instances of the memory would be allocated. Hence by default declaration and can only be defined once.  
 * The members of struct can be defined default.  However static members can NOT be given a default value in 
  struct or classes unlike in java. 
  ```
  struct blah { 
    int y = 10; 
  }
  ```

*Lets add another function as a public function. What is the sizeof(f) after adding a member function ? Well, nothing changes. Member functions do not live in the objects.  DUHH!
* What is the difference between member function and normal c++ functions ?  
 * Well not much, if there was a static function in a class and compared to the ordinary C function, there is no difference with respect to the machine code. So why have this at all ? 
 * For the namespace problems 
 * Static functions of a class can access the private members of any of the objects.  ( You can pass the objects to the static functions ofcourse) 
    
 * You can of course NOT access the member of the class without specifying an object in a static function.  
  ```
    class Foo { 
      int x; 
      static void foo () { 
       cout<<x; 
      }
    };
  ```
This will not work because there is no object binding, for every normal function when you call it through an object the default parameter is this.  

### Member functions 
* class name prepend to function name as a convention.
* Function gains access to private 
* Private access specifier is a runtime concept, and doesn’t really have guarantee to protect the data. 
* Difference between static and non static functions is only the implicit parameter "this", you can think of "this" parameter being passed as a parameter 

### What is this “this” 
* If you could declare “this”, it would be Foo * const this, its a pointer to the object and it can't be changed or incremented.  
* You wanna be able to do this->x = 42; when you write x = 42., its implicit 
* When you specify a variable (symbol) then compiler uses the scope resolution rules to find out what is x. It looks at local scope, then the parameters of the function, then try sticking a this in front of it, and then global scope.  
* If you want to access the global variables then you use the “::” scope resolution
* Private member functions can access the private parts of any object 

### Object Initialization  
```
 struct Foo { 
    int32_t X; 
    int 32_t Y; 
  };  
 Foo f = {10,20}; 
```
* Objects initialized in the order they are written 
* With c++11 you can call the constructor by writing  
```
 Foo f = {10,20} 
 Foo f {10,20} 
```
  * Why would you NOT want the Foo huh(), because this is ambiguous because this might be a function as well as an object with default constructor. Therefore by using the curly braces you get rid of the ambiguity.  
  * You can also do Foo *p = new Foo { 10,15} 
  * Constructors don’t have a return type, can’t even be void (no idea why) 
  * If constructor throws an exception is there a memory leak? No there is no memory leak its freed. [Stack Overflow reference](http://stackoverflow.com/questions/1674980/who-deletes-the-memory-allocated-during-a-new-operation-which-has-exception-in) 
  * In c++11 you can give the default values to the members of the struct and classes
### Memory and Destructors 
  * If you write a C++ program which has some shared resource, it is managed by constructor and destructor. 
  * Why is that design methodology preferred ?  Exception handlers understand the destructors. RAII - resource allocation is initialization 
  * Destructors are called when the object goes out of scope 
  * For resources allocated on heap you would have to explicitly delete them.  
  * Objects are destructed in the exact opposite order of way they are constructed 
  * Global members are initialized before main and are destructed before main terminates. Main is the only function which has special prolog and epilog. 
  * When do you write a destructor ? When you have an external resource being used in the object. For normal objects doesn’t really matter.  
  * For c style string operations strings are null terminated, and pay attention to this fact when copying using strcpy, allocated buffer of atleast one more length than the original string.  
  ```
  class String { 
    char * data; 
    uint32_t length; 
    public: 
     String(const char *s) { 
      length = strlen(s); 
      data = new char[length]; 
      strcpy(data, s);   ← This is problem 
     }

     int main() { 
      string a { “hello”}; 
      fun(a); 
     }
  ```
  * null terminated is not much of a problem but here even though a is going out of scope but if you don’t have special destructor here then the data you allocated in the class would still persist on heap.  
  * If you are passing the string a to the function there is a shallow copy performed to make the parameter, so therefore when that function is over and destructor is called on the parameter, you might deallocate the resource you constructed for a. And then later you might run in problem of double delete
