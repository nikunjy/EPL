/*
 Author : Nikunj Yadav 
 This file features the following : 
   1. How you can run in double delete problem. function(s) makes a copy of the string (shallow) and then destructs the string therefore destructing the resource 
      of the original string since we only did a shallow copy. Turn on #define DOUBLE_DELETE_PROBLEM
   2. How to do a deep copy. Always make the following private methods : destroy() copy() and move(). Look at the copy constructor. 
   3. Assignment operator, always delete yourself first and then copy over what was passed to you.
   4. Notice that the constructor with the single argument is declared as explicit.
   5. You can disable copy constructor, just define the macro COPY_DISABLED
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
class String {
 private: 
  	char *data; 
  	int len;
  	void copy(const String &that) { 
  		len = that.len; 
 		data = new char[len+1];
 		strcpy(data,that.data);
  	}
  	void destroy() { 
  		if (data == nullptr) { 
  			return;
  		}
  		delete[](data); 
  		len = 0;
  	}
 public: 
 	String() { 
 		len = 0; 
 		data = nullptr;
 	}
 	explicit String(const char *_data) {
 		len = strlen(_data);
 		data = new char[len+1];	
 		strcpy(data,_data);
 	}
 #ifdef COPY_DISABLED

 	String(const String&that) = delete;
 	String& operator=(String &that) =  delete;

 #else 

 	String (const String &that) { 
 	  #ifdef DOUBLE_DELETE_PROBLEM
 		this->data = that.data; 
 		//Just doing this is a problem do deep copy instead
 	  #else 
 		copy(that);
 	  #endif
 	}
 	String& operator=(String &that) { 
 		cout<<"\nAssignment operator"<<endl;
 		/*
 			Destroy myself and copy that.
 		*/
 		if (this != &that) {
 			destroy(); 
 			copy(that);
 		}
 		return *this;
 	}

 #endif
 	friend ostream &operator<<( ostream &output, const String &obj) {
 		output << obj.data << "\n";
 	}
 	~String() { 
 		destroy();
 	}

};
void function(String s) { 
	cout << s; //You could see the problem of double delete here if there was no deep copy implemented.
}
int main() { 
	String s("hello"); 
	function(s);
	String x; 
	x = s; 
	cout << x;
}