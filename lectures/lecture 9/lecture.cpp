#include <iostream>
#include <cstdint> 
using std::cout; 
using std::endl; 
/* You can write specific implementations with respect to data type rather than generic 
template <typename T>  
T max(T x, T y) { 
	if ( y > x) { return y;}
	else { return x;}
}
char* max(char* x, char *y) { 
}
*/
/* 
Here be a dick and write this :

template <typename T1, typename T2> 
T1 max(T1 x, T2 y) { 
	if ( x < y) { 
		return y;
	} else { 
		return x;
	}
}

This will not compile because your if block is returning T2 in one condition and T1. Let's fix this
*/
template <typename T>
constexpr T max(T x, T y) { 
	if ( x > y) { 
		return x;
	} else {
		return y;
	}
}
template <typename T1, typename T2>  
struct choose; //template doesn't have to exist it just needs to be declared.  

template<> struct choose<int, int>  { using type  = int; };
template<> struct choose<float, int>  { using type  = float; };
template<> struct choose<double, int>  { using type  = double; };
//This is a shitty implementation because You will have to define all the combinations. 

template <typename T> 
struct SRank; 
template <> struct SRank<int> { static constexpr uint32_t value = 1;};
template <> struct SRank<float> { static constexpr uint32_t value = 2;};
template <> struct SRank<double> { static constexpr uint32_t value = 3;};

template <uint32_t rank> 
struct SType; 
template <> struct SType<1> { using type = int;};
template <> struct SType<2> { using type = float;};
template <> struct SType<3> { using type = double;};

template<typename T1, typename T2> 
struct better_choose { 
	static constexpr uint32_t t1_rank = SRank<T1>::value; 
	static constexpr uint32_t t2_rank = SRank<T2>::value;  
	static constexpr uint32_t max_rank = max(t1_rank, t2_rank); 
	using type = typename SType<max_rank>::type;  
	/*max_rank is unkown at the compile time when checking syntax. Therefore you 
	need to use typename in front of SType<max_rank>
	*/
};
template <typename T1, typename T2>  
typename better_choose<T1,T2>::type max(T1 x, T2 y) { 
	if ( x < y) { 
		return y;
	} else { 
		return x;
	}
}


int main() { 
	/*
	valarray<double> x, y z; 
	cout << x + y + z << endl;  
	This would probably create temporaries from x and y and then add with z. So you 
	will have more loops than you need to and more temporaries. 
	You could do this instead : 
		for (....) { 
			cout << x[k] + y[k] + z[k];
		}
	You will get to use expression templates for making this better. 
	*/
	cout << max(3, 4.3);

}