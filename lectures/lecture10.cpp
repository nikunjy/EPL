#include <iostream>
#include <cstdint> 
#include <vector> 
using namespace std; 

struct Identity { 
	double operator()(double in) { return in;}
};
template<typename LType, typename RType>
struct MulProxy { 
	LType left;  
	RType right;
	//typename RefType<LType>::type left; 
	//typename RefType<RType>::type right; 
	MulProxy(LType _l, RType _r):left(_l), right(_r) {  
	}
	double operator()(double in) const { 
		return left(in) * right(in);
	}
};
MulProxy<Identity, Identity> operator*(Identity left, Identity right) { 
	return MulProxy<Identity, Identity>(left, right);
}
MulProxy<MulProxy<Identity, Identity>, Identity> operator*(MulProxy<Identity, Identity> left, Identity right) { 
	return MulProxy<MulProxy<Identity, Identity>, Identity>(left, right);
}
MulProxy<Identity, MulProxy<Identity, Identity>> operator*(MulProxy<Identity, Identity> left, Identity right) { 
	return MulProxy<Identity, MulProxy<Identity, Identity>>(left, right);
}

template<typename L1, typename L2, typename R1, typename R2>
MulProxy<MulProxy<L1, L2>, MulProxy<R1, R2>> operator*(MulProxy<L1, L2> left, MulProxy<R1,R2> right) { 
	return MulProxy<MulProxy<L1, L2>, MulProxy<R1, R2>>(left, right);
}

/*
	This is not cool because it accepts all universal types.  
*/
template<typename L, typename R> 
MulProxy<L,R> operator*(L left, R right) { 
	return MulProxy<L, R>(left, right); 
}


template<typename func> 
double integrate(fun f, double start, double end, double incr) { 
	double result = 0.0; 
	for (double x = start; x < end; x += incr) { 
		result += f(x);
	}
	return result;
}

int main() { 
	Identity i; 
	/*
		As long as you have auto or some function that you are calling  
	*/
	auto fun = i * 1; 
	double x = integrate(i, 0, 5, 0.001); 
	cout << "The integral is : " << integrate( i * i * i, 0, 5, 0.001) << endl; 
}