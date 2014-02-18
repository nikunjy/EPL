#include <iostream>
#include <vector>
using namespace std;
namespace epl { 
template <typename Ptr>  
int distance(Ptr a, Ptr b) { 
	int count = 0;
	while(a != b) {
		 a++;
		 count++;
	}
	return count;
}
template <typename Ptr, typename CompType> 
Ptr partition(Ptr b, Ptr e, CompType comp) {
	if ( b == e) { 
		return b;
	}
	Ptr x = b + 1; 
	Ptr p = b; 
	while (x != e) {
		if (comp(*x,*b)) {
			p++;
			swap(*p, *x);
		}
		x++;
	}
	swap(*b, *p);
}
template <typename Ptr> 
void print(Ptr b, Ptr e) { 
	while(b != e) { 
		cout << *b <<" ";
		b++;
	}
	cout << endl;
}
template <typename T>
struct DefaultComp { 
	bool operator()(T a, T b) { 
		return a < b;
	}
};
template <typename It>
struct iterator_traits { 
	using value_type = typename It::value_type;
};
template <typename T>
struct iterator_traits<T*> { 
	using value_type = T;
};

template <typename Ptr, typename CompType> 
void sort(Ptr b, Ptr e, CompType comp) { 
	if ( epl::distance(b,e) < 2) { 
		return;
	}
	Ptr pivot = partition(b, e, comp); 
	sort(b, pivot, comp); 
	sort(pivot + 1, e, comp);
}

template <typename Ptr> 
void sort(Ptr b, Ptr e) { 
	if ( epl::distance(b,e) < 2) { 
		return;
	}
	using T = typename iterator_traits<Ptr>::value_type;
	Ptr pivot = partition(b, e, DefaultComp<T>()); 
	sort(b, pivot); 
	sort(pivot + 1, e);
}
}
struct IntComparison { 
	bool operator()(int a, int b) { 
		return a < b;
	}
};