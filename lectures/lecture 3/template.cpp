#include <iostream>
using namespace std;
class Foo { 
 public: 
 	static int constructions;
 	static int destructions;
 	Foo() { 
 		constructions++;
 	}
 	~Foo() { 
 		destructions++;
 	}
 	static void reset() { 
 		constructions = 0;
 		destructions = 0;
 	}
};
int Foo::constructions = 0; 
int Foo::destructions = 0;
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
int main() { 
	Vector<Foo> v;
}