/*
 Author : Nikunj Yadav 
 This file features the following : 
  1. move constructor 
  2. move assignment
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
  explicit String(String && that) { 
    this->data = that.data; 
    this->len = that.len; 
  }
 	String (const String &that) { 
 		copy(that);
 	}
 	String& operator=(String &that) { 
 		if (this != &that) {
 			destroy(); 
 			copy(that);
 		}
 		return *this;
 	}
  String& operator=(String &&that) { 
    swap(this->data, that.data); 
    swap(this->len, that.len);
  }
 	friend ostream &operator<<( ostream &output, const String &obj) {
 		output << obj.data << "\n";
 	}
 	~String() { 
 		destroy();
 	}

};
int main() { 
	String s("hello"); 
	String t("bye");
  s = std::move(t); 
  cout << s << t;
}