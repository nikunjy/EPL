#include <iostream>
using namespace std;
class HotPotato {
public:
    ~HotPotato(void) { 
       cout << "burned";
    }
};
class Container {
   mutable HotPotato* pot;
public:
    Container(void) { pot = new HotPotato; }
    Container(Container &&ref) {
        this->pot = ref.pot;
        ref.pot = nullptr;
    }
    Container& operator=(const Container& that) { 
        if (this != &that) { 
            this->pot = that.pot;
            that.pot = nullptr;
        }
        return *this;
    }
    ~Container() {
        if (pot == nullptr) { 
            return;
        }
        delete pot;
        
    }
};
Container pass(Container& c) { 
    return std::move(c); 
}
int main(void) {
   Container c;
   for (int k = 0; k < 10; k += 1) {
      c = pass(c);
   }
}