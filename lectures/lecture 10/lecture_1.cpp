#include <iostream>
#include <cstdint>
#include <type_traits>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

/*
  Notes by me 
  I am going to decide that I can do + of two vector<int> but not strings. 
*/

namespace epl {
	template <typename T> struct is_arithmetic { 
		static constexpr bool value = false;
	};
	template <> struct is_arithmetic<int> { 
		static constexpr bool value = true;
	};

	template <bool pred, typename T = void>
	struct enable_if;

	template <typename T> 
	struct enable_if<true, T> {
		using type = T;
	};

	template <typename T>
	struct enable_if<false, T> {
		//Note that type is not defined therefore return type is empty in the operator overloaded below. 
	};

}
/*
Simple operator overload would be this and in case of strings you will get appended strings. 
So lets avoid that, please take care when you are writing math libraries that you don't enable 
operators for things that are not operable. Solution to allow/ban certain things follows: 
template <typename T>
vector<T> operator+(const vector<T>& x, const vector<T>& y) {
	vector<T> result;
	for (auto p = x.begin(), q = y.begin(); p != x.end() && q != y.end(); ++p, ++q) {
		result.push_back(*p + *q);
	}
	return result;
}
*/

/*

*/
template <typename T>
typename epl::enable_if<epl::is_arithmetic<T>::value,vector<T>>::type operator+(const vector<T>& x, const vector<T>& y) {
	vector<T> result;
	for (auto p = x.begin(), q = y.begin(); p != x.end() && q != y.end(); ++p, ++q) {
		result.push_back(*p + *q);
	}
	return result;
}


template <typename T>
std::ostream& operator<<(std::ostream& out, const vector<T>& x) {
	const char* prefix = "";
	for (const auto v : x) {
		out << prefix << v;
		prefix = ", ";
	}
	return out;
}

int main(void) {
	vector<int> x = {1, 2, 3, 4, 5};
	vector<int> y = {10, 20, 30, 40, 50};
	cout << x + y << endl;

	vector<string> a = {"hello", "world"};
	vector<string> b = {"whoa", "there"};
	//cout << a + b << endl;
}
