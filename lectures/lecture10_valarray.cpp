#include <iostream>
using namespace std; 
/*
	Instead of writing different permutations and combinations. 
	You should remove the distinction between the Valarray and the proxy here . 
*/
template <typename T, typename R>  
struct Valarray : public R{ 
	explicit Valarray(uint64_t sz):R(sz) { 
	}	
};
template <typename T1, typename R1, typename T2, typename R2>  
Valarray<T1, AddProxy<R1, R2>> operator +(const Valarray<T1, R1> &x, const Valarray<T2, R2> &y) { 
	return ValArray<T1, AddProxy<R1, R2>>(x, y);
}
int main() { 
	Valarray<double> x(10); 
	Valarray<double> y(10); 
	cout << x + y;
}ar