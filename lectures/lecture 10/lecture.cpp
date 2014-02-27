#include <iostream>
#include <cstdint> 
#include <complex> 
#include <typeinfo>
using std::cout; 
using std::endl; 
using std::complex;
template <typename T>
constexpr T max(T x, T y) { 
	return (x < y) ? y : x; 
}
template <typename T> 
struct SRank; 
template <> struct SRank<int> { static constexpr uint32_t value = 1;};
template <> struct SRank<float> { static constexpr uint32_t value = 2;};
template <> struct SRank<double> { static constexpr uint32_t value = 3;};

template<typename T> struct SRank<complex<T>> { 
	static constexpr uint32_t value = SRank<T>::value;
};

template<typename T> struct CRank { 
	static constexpr bool value = false;  
};
template<typename T> struct CRank<complex<T>> { 
	static constexpr bool value = true;
};

template<typename T, bool complexity> 
struct CType; 

template<typename T> struct CType<T, true> { 
	using type = std::complex<T>;
};
template<typename T> struct CType<T, false> { 
	using type = T;
};
/*
	You can fucking template  a typedef!!  
*/
template<typename T, bool complexity> 
using CompType = typename CType<T, complexity>::type; 

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
	using stype = typename SType<max_rank>::type;  
	/*
		max_rank is unkown at the compile time when checking syntax. Therefore you 
		need to use typename in front of SType<max_rank>
	*/
	static constexpr bool t1_comp = CRank<T1>::value; 
	static constexpr bool t2_comp = CRank<T2>::value; 
	static constexpr bool complexity = t1_comp || t2_comp; 
	
	/*
		using type = typename CType<stype, complexity>::type; 
		typename is required because prior to knowing t1 and t2. We can know that this is a typedef.
	*/

	using type = CompType<stype, complexity>;

};
template <typename T1, typename T2>  
typename better_choose<T1, T2>::type doit(T1 x, T2 y) { 
	using RetType = typename better_choose<T1, T2>::type; 
	cout << "The deducted type is " << typeid(RetType).name() << endl;
	return RetType{};
}

template <typename T1, typename T2>  
typename better_choose<T1,T2>::type max(T1 x, T2 y) { 
	if ( x < y) { 
		return y;
	} else { 
		return x;
	}
}
int main() { 
	//cout << doit(3, 4.3);
	/*
	 How about now ? 
	 cout << max(complex<float>{0.0,0.0}, 1.5); 
	 Need to define SRank for complex and what is max going to look like;
	*/
	 cout << doit(1.4, 1.5); 


}