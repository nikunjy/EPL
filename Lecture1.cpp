#include <iostream>
using namespace std;
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
