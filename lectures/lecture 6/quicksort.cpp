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
template <typename Ptr> 
Ptr partition(Ptr b, Ptr e) {
	Ptr x = b + 1; 
	Ptr p = b; 
	while (x != e) {
		if (*x < *b) {
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
template <typename Ptr> 
void sort(Ptr b, Ptr e) { 
	if ( epl::distance(b,e) < 2) { 
		return;
	}
	Ptr pivot = partition(b, e); 
	sort(b, pivot); 
	sort(pivot + 1, e);
}
}

int main() { 
	vector<int> v = { 1 , 4, 10, -1, 2, 5, 8, 9};
	epl::sort(v.begin(), v.end()); 
	epl::print(v.begin(), v.end());
}