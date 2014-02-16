#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
class Foo {
public:
	static int32_t constructions;
	static int32_t destructions;

	int id;
	Foo(void) {
		id = constructions;
		constructions += 1;
	}

	~Foo(void) {
		destructions += 1;
	}
};

int32_t Foo::constructions = 0;
int32_t Foo::destructions = 0;
class Counter { 
private: 
	int count; 
public:
	Counter() {
		 count = 0;
	}
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
template <typename T>
class SmartPtr { 
private:
	T *ptr;
	Counter *counter;
	void destroy() {
		if (counter->decrement() == 0) { 
			if (ptr == nullptr) { 
				return;
			}
			delete ptr;
			delete counter;
		}
	}
public:
	explicit SmartPtr(T *ptr) { 
		this->ptr = ptr; 
		counter = new Counter{};
		counter->increment();
	}
	explicit SmartPtr(const SmartPtr &that) {
		this->ptr = that.ptr; 
		this->counter = that.counter; 
		counter->increment();
	}
	explicit SmartPtr(SmartPtr &&that) { 
		this->ptr = that.ptr;
		this->counter = that.counter;
		that.ptr = nullptr;
		that.counter = nullptr;
	}
	const T& operator*() { 
		return *ptr;
	}
	T* operator->() { 
		return ptr; 
	}
	SmartPtr& operator=(const SmartPtr &that) { 
		if (this != &that) { 
			destroy();
			this->ptr = that.ptr; 
			this->counter = that.counter;
			counter->increment();
		} 
	}
	SmartPtr& operator=(SmartPtr &&that) { 
		swap(this->ptr, that.ptr); 
		swap(this->counter, that.counter);
	}
	~SmartPtr() {
		if (ptr == nullptr) { 
			return;
		}
		destroy();
	}
};
using Pointer = SmartPtr<Foo>;
int main(void) {
	{ // first test
		Pointer p{new Foo};
		assert(p->id == 0);
	}
	assert(Foo::constructions == 1 && Foo::destructions == 1);
	cout << "first test passed\n";

	{ // second test
		std::vector<Pointer> v;
		v.reserve(10);
		v.push_back(Pointer{new Foo});
		v.push_back(v[0]);
		v.push_back(v[0]);
		assert(v[0]->id == 1 && v[1]->id == 1);
		v.push_back(Pointer{nullptr}); 
		assert(Foo::constructions == 2 && Foo::destructions == 1);
		Pointer p{new Foo};
		v[1] = p;
		assert((*p).id == 2 && v[1]->id == 2);
		assert(Foo::constructions == 3 && Foo::destructions == 1);
		v.pop_back(); // remove nullptr
		v.pop_back(); // remove v[2] (references same object as v[0], object id 1)
		v.pop_back(); // remove v[1] (references same object as p, object id 2)
		assert(Foo::constructions == 3 && Foo::destructions == 1);

		v.pop_back(); // remove v[0], forces destruction of object id 1
		assert(Foo::constructions == 3 && Foo::destructions == 2);
	} // p goes out of scope, forces destruction of object id 2
	assert(Foo::constructions == 3 && Foo::destructions == 3);
	cout << "second test passed\n";
}