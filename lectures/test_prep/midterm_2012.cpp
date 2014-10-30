/* Attempt of mideterm 2012 */ 
#include <iostream>
#include <vector>
#include <iterator>
using std::cout;
using std::vector; 
using std::endl;
struct ProxyType { 
    int speed = 50; 
    int distance = 50;
    ProxyType() { 
        speed = 50;
        distance = 50;
    }
    ProxyType(const ProxyType &that) { 
        this->speed = that.speed;
        this->distance = that.distance;
    }
};
struct SpeedType { 
    int speed; 
    SpeedType() { 
        speed = 50;
    }
    ProxyType operator=(int speed) { 
        this->speed = speed;
        ProxyType proxy;
        proxy.speed = this->speed;
        return proxy;
    }
};
struct DistanceType { 
    int distance;
    DistanceType() { 
        distance = 50;
    }
    ProxyType operator=(int distance) { 
        this->distance = distance;
        ProxyType proxy;
        proxy.distance = this->distance;
        return proxy;
    }
};
ProxyType operator,(const ProxyType &a, const ProxyType &b) { 
    ProxyType c; 
    ProxyType ret;
    if (a.speed == c.speed) { 
        ret.speed = b.speed;
        ret.distance = a.distance;
    }
    if (a.distance == c.distance) { 
        ret.distance = b.distance;
        ret.speed = a.speed;
    }
    return ret;
}
SpeedType speed; 
DistanceType distance;
void doit(ProxyType proxy) { 
    cout << proxy.speed << " " << proxy.distance << "\n";
}

template<bool,typename T1, typename T2> 
struct Select; 
template<typename T1, typename T2> 
struct Select<true,T1,T2> { 
    using ret = T2;
};
template<typename T1, typename T2> 
struct Select<false,T1,T2> { 
    using ret = T1;
};
typedef typename Select<sizeof(int) < sizeof(double), int, double>::ret X;



template<typename T1, typename T2> 
struct List { 

};
template<typename T1>
struct ListSelect { 
    using type = T1;
};
template<typename T1, typename T2> 
struct ListSelect<List<T1,T2>>  {
    using type1 = T1; 
    using type2 = typename ListSelect<T2>::type;
    using type = typename Select<sizeof(type1) < sizeof(type2), type1, type2>::ret;
};
template<typename T1, typename T2>
struct is_equal { 
    static const bool value = false;
};
template<typename T>
struct is_equal<T,T>  {
    static const bool value = true;
};
void printIterator(std::random_access_iterator_tag) { 
    cout << "Random Access";
}
void printIterator(...) { 
    cout << "list access";
}
template<typename T> 
void ds_type(const T&) { 
    typename std::iterator_traits<typename T::iterator>::iterator_category type;
    printIterator(type);
    cout << "\n";
}

int main() { 
    doit(speed = 100);
    doit((speed = 100, distance = 20));
    X x;

    typedef List<char,List<double,List<float, char>>> ListType;
    typedef typename ListSelect<ListType>::type list;
    typedef typename Select<sizeof(int) < sizeof(list), int, list>::ret Y;
    cout << std::boolalpha;
    cout << is_equal<Y,double>::value << endl;
    ds_type(vector<int>());
}