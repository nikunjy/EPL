#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
namespace epl {
template<typename Ptr, typename Fun> 
typename iterator_traits<Ptr>::value_type get_max(Ptr b, Ptr e, const Fun &fun) { 
    using type = typename iterator_traits<Ptr>::value_type;
    type data = *b;
    b++;
    while (b != e) {
        if (fun(*b, data)) { 
            data = *b;
        }
        b++;
    }
    return data;
}

template<typename Ptr>
typename iterator_traits<Ptr>::value_type max(Ptr b, Ptr e) { 
    using type = typename iterator_traits<Ptr>::value_type;
    return get_max(b, e, std::greater<type>());
}

};
int main() { 
    vector<int> v; 
    for(int i = 0; i < 10; i++) { 
        v.push_back(i);
    }
    cout << epl::max(v.begin(),v.end());
}