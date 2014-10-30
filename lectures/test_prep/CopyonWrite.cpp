#include <iostream>
#include <vector>
using namespace std;
template<typename T>
struct Vector {
    struct condition_block  {
        int counter;        
        condition_block() { 
            counter = 1;
        }
        int increment() { 
            counter++;
            return counter;
        }
        int decrement() { 
            counter--; 
            return counter;
        }
    }; 
    struct RefProxy { 
        Vector<T> *me;
        int index;
        T& operator=(const T& obj) { 
            me->detach();
            me->data->at(index) = obj;
            return me->data->at(index);
        }
        operator T() const{ 
            return (const_cast<const vector<T>*>(me))->data->at(index);
        }
    };
    void copyItems(const vector<T> &data_) {
        data = new vector<T>(); 
        for (int i = 0; i < data_.size(); i++) { 
            data->push_back(data_[i]);
        }
    }
    void copy() { 
    
    }
    void destroy() { 
        if (block->decrement() == 0) { 
            delete data;
            delete block;
        }
    }
    void move() { 

    }
    void detach() { 
        if (block->counter > 1) { 
            copyItems(*data); 
        }
    }
    vector <T> *data;
    mutable condition_block *block;
    Vector(int size) { 
        data = new vector<T>();
        data.resize(size);
        block = new condition_block();
    }
    Vector() { 
        data = new vector<T>();
        block = new condition_block();
    }
    Vector(const Vector& that) { 
        this->data = that.data; 
        this->block = that.block; 
        block->increment();
    }
    void push_back(const T& obj) { 
        detach();
        data->push_back(obj);
    }
    size_t size() const { 
        return data->size();
    }
    RefProxy operator[](int index) { 
        RefProxy proxy; 
        proxy.me = this;
        proxy.index = index;
        return proxy;
    }
    const T& operator[](int index) const { 
        return data->at(index);
    }
};
template<typename T> 
ostream& operator<<(ostream& output, const Vector<T>& v) { 
  for (int i = 0; i < v.size(); i++) { 
    output << v[i] << "\t";
  }
  return output;
}
int main() { 
    Vector<int> v; 
    for(int i = 0; i < 3; i++) { 
        v.push_back(10); 
    }
    cout << v << endl;
    Vector<int> x = v;
    cout << x << endl; 
    x[0] = 111;
    cout << "v :\t" << v <<endl << "x :\t" << x << endl;
    
}