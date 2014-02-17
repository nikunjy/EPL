/*
	Author: Nikunj Yadav <nikunj@cs.utexas.edu> 
	This file conains the following thigs: 
		1. This implements copy on write. Every object maintains the reference counter. So for any operation which mutates the data, you do the following: 
			a) Check if the reference count is greater than one which means that there is another object that shares the core. 
			b) In the case a is true actually copy the data and then do the write. 
		2. For any construction of the object, you basically do shallow copy. Because 1st takes the care of deep copy for you when write is needed. 
		3. I also learnt that even though an object might be passed as a r value to a function f, if function f calls g which also accepts r value. This will not work 
		   You will have to explicitly call g with std::move(obj) as the argument. 
		___________________________________________________________________________________________________________________________________________________ 


*/
#include <iostream>
#include <stdexcept>
#include <cassert>
using namespace std;
class Foo {
private:
	int data; 
public:
	static int constructions; 
	static int destructions; 
	static int copies;  
	Foo() {  
		data = 0;
		constructions += 1;
	}
	Foo(const Foo &obj)  {
		data = 0; 
		copies +=1; 
		this->data = obj.data;
	}
	Foo(Foo &&obj) { 
		this->data = obj.data;
	}
};
int Foo::constructions = 0; 
int Foo::destructions = 0; 
int Foo::copies = 0;
class Counter {
private: 
	int count;
public: 
	int increment() { 
		count++;
		return count;
	}
	int decrement() { 
		count--;
		return count;
	}
	int getCount() {
		return count;
	}
};
template<typename T>
class Vector { 
private: 
	struct Core { 
		T *data; 
		int capacity; 
		int start; 
		int end;
		Core() { 
			capacity = 8;
			start = 0;
			end = 0;
			data = (T*)operator new(sizeof(T) * capacity); 
		}
		Core(const Core &that) { 
			this->capacity = that.size(); 
			start = 0; 
			end = that.size();
			data = (T*)operator new(sizeof(T) * capacity); 
			for (int i = that.start; i < that.end; i++) {
				new (data + i - that.start)T(that.data[i]);
			}
		}
		void grow() { 
			T *temp = data; 
			capacity *= 2;
			data = (T*)operator new(sizeof(T) * capacity);
			for (int i = start; i < end; i++) { 
				new (data + i)T(std::move(temp[i]));
				temp[i].~T();
			}
			operator delete(temp);
		}
		void push_back(const T &obj) { 
			if (end == capacity) {
				grow(); 
			}
			new (data + end) T(obj); 
			end++;
		}
		void push_back(T &&obj) {
			if (end == capacity) {
				grow(); 
			}
			new (data + end) T(std::move(obj)); 
			end++;	 
		}
		int size() const { 
			return end - start;
		}
		const T& operator[](int k) { 
			if ( k < end - start) { 
				return data[k + start];
			}
			throw std::out_of_range("out of range index");
		}
		~Core() { 
			for ( int i = start; i < end; i++) { 
				data[i].~T();
			}
			operator delete(data);
		}
	};
	Core *core;
	Counter *counter; 
	void copy(const Vector<T> &that) { 
		this->core = that.core; 
		this->counter = that.counter; 
		counter->increment();
	}
	void move(Vector<T> &&that) {
		swap(this->core, that.core); 
		swap(this->counter, that.counter);
	}
	void destroy() { 
		if (counter->decrement() == 0) {
			delete core; 
			delete counter;
		}
	}
	void force_unique() { 
		if (counter->getCount() > 1) { 
			counter->decrement();  
			counter = new Counter();
			counter->increment(); 
			Core *new_core = new Core(*(this->core)); 
			this->core = new_core;
		}
	}
public: 
	Vector() { 
		core = new Core(); 
		counter = new Counter(); 
		counter->increment();
	}
	Vector(const Vector<T> &that) { 
		copy(that);
	}
	Vector(Vector<T> &&that) { 
		move(that);
	}
	const Vector& operator=(const Vector<T> &that) { 
		if ( this != &that) { 
			destroy(); 
			this->core = that.core;
			this->counter = that.counter;
			counter->increment();
		}
	}
	const Vector& operator=(Vector<T> &&that) {
		move(that);
	}
	T& operator[](int k) { 
		force_unique(); 
		return core[k];
	}
	const T& operator[](int k) const {
		return core[k];
	}
	int size() const { 
		return core->size();
	}
	void push_back(const T& obj) {
		force_unique(); 
		core->push_back(obj);
	}
	void push_back(T&& obj) {
		force_unique(); 
		//Needed to type cast here again. WTF! 
		core->push_back(std::move(obj));
	}
	~Vector() {
		destroy();
	}

};
int main() { 
	Vector<Foo> v;
	for (int i = 0; i < 10; i++) { 
		v.push_back(Foo());
	}
	assert(Foo::constructions == 10); 
	assert(Foo::destructions == 0);
	Vector<Foo> x;
	x = v;
	assert(Foo::constructions == 10); 
	assert(Foo::destructions == 0);
	Vector<Foo> y(v); 
	assert(Foo::constructions == 10 && Foo::destructions == 0);
	y.push_back(Foo());
	assert(Foo::constructions == 11 && Foo::copies == 10 && Foo::destructions == 0);
	cout << "Test Passed";
}