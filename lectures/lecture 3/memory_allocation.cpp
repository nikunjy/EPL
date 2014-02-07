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
int main() { 
	Foo x[10]; 
	cout << Foo::constructions << endl;
	Foo::reset();
	Foo *y; 
	y = new Foo[10]; 
	cout << Foo::constructions << endl;
	Foo::reset();
	Foo *z; 
	z = (Foo*)operator new (sizeof(Foo)*10); 
	cout << Foo::constructions << endl;
	for (int i = 0; i < 10; i++) { 
		new (z+i)Foo();
	}
	cout << Foo::constructions << endl;
	for (int i = 0; i < 10; i++) { 
		z[i].~Foo();
	}
	operator delete(z);
}