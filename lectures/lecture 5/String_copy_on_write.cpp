#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
class Counter { 
private: 
	int count;
public:
	Counter() { 
		count = 0; 
	}
	int getCount() { 
		return count;
	}
	int increment() { 
		count++;
		return count;
	}
	int decrement() {
		 count--;
		 return count;
	}
};
class String { 
private:
	char *data;
	int len;
	Counter *counter;
	void force_unique() { 
		if (counter->getCount() > 1) {
			char * temp = data; 
			data = new char[len + 1];
			strcpy(data, temp);
			counter->decrement(); 
			counter = new Counter(); 
			counter->increment();
		}
	}
	void destroy() { 
		if (counter->decrement() == 0) { 
			if (data == nullptr) { 
				return;
			}
			delete data; 
			delete counter;
			len = 0;
		}
	}
public:
	String() {
		data = nullptr; 
		len = 0;
	}
	String(const char *_data) {
		this->len = strlen(_data);
		data = new char[len + 1];
		counter = new Counter();
		counter->increment();
		strcpy(data, _data);
	}
	String(const String &that) {
		this->len = that.len;
		this->data = that.data;
		this->counter = that.counter;
		counter->increment();
	}
	char& operator[](int k) { 
		if (k < len) { 
			force_unique();
			return data[k];
		}
	}
	String& operator=(String &that) {
		if (this != &that) { 
			destroy(); 
			this->data = that.data; 
			this->len = that.len; 
			this->counter = that.counter;
		}
	}
	friend ostream &operator<<( ostream &output, const String &obj) {
 		output << obj.data << "\n";
 	}
	~String() {
		destroy();
	}
};
void function(String temp) { 
	//no problem of double delete.
}
int main() {
	String s("hello world!");
	String x(s);
	cout << s << x;
	x[0] =	'b';
	cout << s << x;
	function(s);
	cout << s;
}