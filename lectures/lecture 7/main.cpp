#include "LinkedList.h" 
#include "quicksort.h"
#include <iostream>
using namespace std;
int main() { 
	LinkedList<int> list; 
	for ( int i = 10; i > 0; i--) { 
		list.push_back(i);
	}
	epl::print(list.begin(), list.end());
	epl::sort(list.begin(), list.end());
	epl::print(list.begin(), list.end());
}