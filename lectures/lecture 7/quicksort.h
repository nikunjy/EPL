#include <iostream>
#include <vector>
using namespace std;
namespace epl { 
template <typename It>
struct iterator_traits { 
	using value_type = typename It::value_type;
	using category_type = typename It::iterator_category;
};
template <typename T>
struct iterator_traits<T*> { 
	using value_type = T;
	using category_type = std::random_access_iterator_tag;
};
template<typename Ptr>
int distance(Ptr a, Ptr b, std::random_access_iterator_tag) { 
	return b - a;
}
template<typename Ptr>
int distance(Ptr a, Ptr b, std::forward_iterator_tag) { 
	int count = 0;
	while(a != b) {
		 a++;
		 count++;
	}
	return count;
}

template <typename Ptr>  
int distance(Ptr a, Ptr b) { 
	typename iterator_traits<Ptr>::category_type category;
	distance(a, b, category);
}
template <typename Ptr, typename CompType> 
Ptr partition(Ptr b, Ptr e, CompType comp) {
	if ( b == e) { 
		return b;
	}
	Ptr x = ++b; 
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
template <typename Ptr, typename CompType> 
void sort(Ptr b, Ptr e, CompType comp) { 
	if ( epl::distance(b,e) < 2) { 
		return;
	}
	Ptr pivot = partition(b, e, comp); 
	sort(b, pivot, comp); 
	sort(++pivot, e, comp);
}

template <typename Ptr> 
void sort(Ptr b, Ptr e) { 
	if ( epl::distance(b,e) < 2) { 
		return;
	}
	using T = typename iterator_traits<Ptr>::value_type;
	Ptr pivot = partition(b, e, DefaultComp<T>()); 
	sort(b, pivot); 
	sort(++pivot, e);
}
}
struct IntComparison { 
	bool operator()(int a, int b) { 
		return a < b;
	}
};