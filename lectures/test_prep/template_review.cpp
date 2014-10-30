#include <iostream>
#include <iterator>
#include <utility>
using namespace std;
/*
    Things related to type
*/
template<typename T>
struct TypeSequenceLength;
template<typename... Args> 
struct TypeSequence{
    int size() { 
        return TypeSequenceLength<TypeSequence<Args...>>::length;
    }
}; 
template<typename T> 
struct TypeSequenceLength<TypeSequence<T>> { 
    static const int length = 1;
};
template<typename T, typename... Tail> 
struct TypeSequenceLength<TypeSequence<T, Tail...>> { 
    static const int taillength = TypeSequenceLength<TypeSequence<Tail...>>::length;
    static const int length = taillength + 1;
};

template<typename T, typename... Tail> 
struct TypeSequenceFind; 

template<typename T, typename... Tail>
struct TypeSequenceFind<T, TypeSequence<T, Tail...>> { 
    static const int position = 1;
};
template<typename T, typename Head, typename... Tail>
struct TypeSequenceFind<T, TypeSequence<Head, Tail...>> { 
    static const int tailpos = TypeSequenceFind<T, TypeSequence<Tail...>>::position;
    static const int position = tailpos + 1;
};
/*
    End of things related to typesequence
*/

/*
    Start of Tuple 
*/
template<typename T,typename... Args> 
struct Tuple; 
template<int N, typename T, typename... Args> 
struct TupleType;
template<typename T, typename... Args> 
struct TupleType<0,T,Args...> { 
    using type = Tuple<T,Args...>;
    using value_type = T;
};
template<int N, typename T, typename... Args> 
struct TupleType { 
    using type = typename TupleType<N-1, Args...>::type;
    using value_type = typename TupleType<N-1, Args...>::value_type;
};
template<typename T> 
struct Tuple<T> { 
    T obj; 
    Tuple(T obj_)  { 
        this->obj = obj_;
    }
};
template<typename T, typename... Args>
struct Tuple : public Tuple<Args...> { 
    T obj;
    Tuple(T obj_, Args&& ...args):Tuple<Args...>(std::forward<Args>(args)...) { 
        this->obj = obj_; 
    }
};
template<int N,typename T,typename... Args>
constexpr typename TupleType<N,T,Args...>::value_type get(const Tuple<T,Args...> &tuple) { 
    using type = typename TupleType<N,T,Args...>::type;
    return (static_cast<type>(tuple)).obj;
}
/*
End of stuff for tuple
*/
/*
    Use of declval and decltype
    Fucking const is important
*/
template<typename A, typename B, typename = decltype(static_cast<const A&>(declval<B>()))>
std::true_type isBase(const A&, const B&);
template<typename A, typename B>
std::false_type isBase(...);
template<typename A, typename B>  
struct BaseHelper { 
    using type = decltype(isBase<A,B>(declval<A>(),declval<B>()));
    static const bool value = type::value;
};
class X { 
};
class Y : public X{ 
};
/*
    End of declval and decltype
*/

/* 
    Bunch of other templates 
*/
namespace epl {
template<typename T1, typename T2> 
struct is_equal { 
    static const bool value = false;
};
template<typename T> 
struct is_equal<T,T> {
    static const bool value = true;
};
template<typename T> 
struct SRank; 
template<> struct SRank<int> { 
    static const int value = 1;
};
template<> struct SRank<double> { 
    static const int value = 2;
};
template<typename T> 
struct is_arithmetic {
    static const bool value = false;
};
template<> struct is_arithmetic<int> { 
    static const bool value = true;
};
template<bool, typename T> 
struct enable_if { 

};
template<typename T>
struct enable_if<true,T> {
    using type = T;
};
};
int main() { 
    TypeSequence<int,float,double,char,bool> types; 
    cout << types.size() << endl;
    cout << TypeSequenceFind<double, TypeSequence<int,float,double,char,bool>>::position << endl;
    Tuple<double,int,char> tuple(1.0,2,'c');
    cout << endl<<endl << get<2>(tuple) << endl;
    cout <<std::boolalpha; 
    cout << BaseHelper<X,Y>::value;
    typedef typename epl::enable_if<is_arithmetic<int>::value, int>::type INT_TYPE;
    cout << endl << epl::is_equal<int,INT_TYPE>::value;
}