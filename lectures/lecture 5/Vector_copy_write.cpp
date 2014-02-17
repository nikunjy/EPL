#include <iostream>
#include <stdexcept>
using namespace std;
class Foo {
private:
	int data; 
public:
	static int constructions; 
	static int destuctions; 
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
	Foo(const Foo &&obj) { 
		this->data = obj.data;
	}
};
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
			data = (T*)operator new(sizeof(T) * 8); 
		}
		Core(const Core &core) { 
			this->capacity = core.size(); 
			start = 0; 
			end = core.size() - 1;
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
		int size() const { 
			return end - start;
		}
		const T& operator[](int k) { 
			if ( k < end - start) { 
				return data[k + start];
			}
			throw std::out_of_rande("out of range index");
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
	void copy(const String &that) { 
		this->core = that.core; 
		this->counter = that.counter; 
		counter->increment();
	}
	void move(String &&that)  { 
		this->core = that.core; 
		this->counter = that.counter; 
		that.core = nullptr; 
		that.counter = nullptr;
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
			Core *new_core = new Core(this->core); 
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
	const T& operator[](int k) {
		return core[k];
	}
	void push_back(const T& obj) {
		force_unique(); 
		core->push_back(obj);
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
	cout << Foo::constructions << " " <<Foo::destructions; 

}