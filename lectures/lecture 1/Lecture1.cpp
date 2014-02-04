#include <iostream>
using namespace std;
/* 
	This example shows you : 
	 1. Use of static member inside the class. 
	 2. A member function can access the private parts of any object. Even if called from the scope of other object. 
	 3. 2nd is true because member function actually isn't located in memory of one object but common to a class. 
*/
class Foo { 
	private: 
		static int x; 
		int y;
	public:
	  static void function(Foo &obj) { 
			cout<<obj.y<<endl;
		}
		void privateParts(Foo &obj) { 
			cout<<obj.y<<endl;
		}	
		void hello() { 
			cout<<"Hi"<<x;
		}
};
int Foo::x;
int main() { 
	Foo f; 	
	f.hello();
	cout<<endl;
	Foo g;
	f.privateParts(g);
	cout<<endl;
	Foo::function(f);
}
