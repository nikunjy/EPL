#include <iostream>
#include <utility>
using namespace std;
struct X {
    virtual ~X() {
        cout << "X destructor" << endl;
    }
};
struct Y : public X {
    int x;
    void doit() const { 
    }
    void doit() { 
    }
    Y() { 
        //BIG ALLOC
    }
    static string myType() { 
        return "Y";
    }
    ~Y() { 
        cout << "Y destructor" << endl;
    }
};
string function(const int&) {
    return "int";
}
template<typename T> 
string function(T) {
    if (is_class<T>()) { 
        return T::myType();
    }
}
template<typename T> 
string function(T*) {
    return "pointer of " +function(T{});
}

template<typename T> 
bool isTemp(const T&) { 
    return false;
}
template<typename T> 
bool isTemp(T&&) { 
    return true;
}
void doit(int x) { 
    cout << x;
}
int main() { 
    int **a; 
    cout << function(a) << endl;
    cout << function(new Y()) << endl;

    cout << std::boolalpha;
    int x,y;
    int *p;
    cout << isTemp(x+y) << endl;

    int array[10]; 
    *array = 10;
    doit(*array);

}