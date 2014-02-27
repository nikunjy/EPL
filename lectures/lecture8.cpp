#include <cstdint> 
#include <iostream>
using std::cout; 
using std::endl;
template <typename T> 
class Foo { 
	T data;
public:
	//A member function in a template class is itself a template function
	Foo(const T&);
	Foo(T, double) { 
		cout << "Other Constructor";
	}
	template <typename AltType>  
	Foo<T>& operator=(const AltType& rhs) { 
		T var = (T) rhs; 
		data = var;
		return *this;
	} //Don't try to define this outside, pretty bad practice 
};
template <typename U> 
Foo<U>::Foo(const U& val) {
	cout << "Constructor\n";
}

template <typename T, typename... Args> 
T* make_thing(Args... args) {
	return new T(args...);
}

int main() { 
	Foo<int> x(42);
	/* x.operator=<double>(3.14159);  
	Nobody does this, there would be places 
	though where you would want to specify the type like this */

	 x = 3.14159;
	 Foo<int>* p = make_thing<Foo<int>>(42, 3.14159); // Args is going to be resolved here to list of two types


}