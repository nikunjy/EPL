### Const Methods  
* Can't change the members of the class 
* When you call the const method of the class you are basically passing const Foo * as the first parameter instead of Foo * 
* You can overload the same method with everything same but only difference of const-ness 

### Copy on Write 
* You will be able to do shallow copies, and maintain the reference counters. 
* On an operator that mutates the data ( the one you didn't deep copy), based on the information of the reference counter you deep copy. 
* Above point is done when the reference counter is > 1 because that means that there are more than one copies of the data.
* Copy on write is totally useless since we have copy and move in C++ now.  

### Operators and const-ness 
* If we lets say did copy and write with vectors. And we have the following code. There is no differentiation between line 2 and line 3.
```
 Vector<Foo> x; 
 cout << x[0]; 
 x[0] = Foo();
```
* C++ doesn't resolve the operators based on the left hand and right hand operators but based on constness. Therefore here even though we should not be de-coupling copies in the line 2 we still do. 
* The solution to this is introducing a level of indirection: 
```
struct Proxy { 
	Vector<T> *me; 
	int k; 
	Proxy operator=(const T& obj) { 
		me->at(k) = obj;
		return *this;
	}
	operator T() const { 
		const_cast<const Vector<T>*>(me)->at(k);
	}
}; 
Proxy operator[](int k) { 
	Proxy prox { this, k};
	return prox;
}
```
* The reason this solution works is because when you say cout << x[0] it will try to resolve the value operator for the returned proxy. Which is available and returns a const value. 
* This solution would fail if you have a function that expects a T& and you pass the function v[0] because you are sending proxy type object. 
* Proxy can't be on the heap, we don't want to share the same proxy across all v[0] v[1] etc. Therefore proxy needs to be on the stack. 
* As a matter of fact using this proxy is free, because when you turn on optimization for the program v[0] will actually be replaced by the const type cast you did in the proxy.  