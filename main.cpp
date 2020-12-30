#include <iostream>
#include <string>
#include <memory>

template<typename T, class Allocator = std::allocator<T>>
class custom_vector {
private:
    size_t size = 0;
    T *v = nullptr;
    Allocator Alloc;
    void construct_vector(T* first){
        T *last = first + size;
        while(first != last) {
            Alloc.construct(first++); // use std::construct_at(first++); if your compiler has -std=c++20 flag
        }
    }
public:
    custom_vector<T, Allocator>(const size_t &size) {
        this->size = size;
        this->v = Alloc.allocate(size);
        construct_vector(v);
    }
    size_t get_size() {
        return size;
    }

    T &at(const size_t &pos) {
        return *(v + pos);
    }
    T &operator[](const size_t &pos) {
        return at(pos);
    }
    const T &at(const size_t &pos) const {
        return *(v + pos);
    }
    const T &operator[](const size_t &pos) const {
        return at(pos);
    }

    void add(T arg) {
        size++;
        T *new_v = Alloc.allocate(size);
        construct_vector(new_v);
        std::move(v, v + size - 1, new_v);
        Alloc.deallocate(v, size - 1);
        v = new_v;
        *(new_v + size - 1) = arg;
    }

    void test() {
        *(v + 1) = "TEST1";
        std::cout << "TEST" << "\n";
    }
};

int main() {
    //TEST <double>
    custom_vector<double> v1(3);
    for(int i = 0; i < v1.get_size(); i++) {
        v1.at(i) = 2.0 / 3.0;
    }
    v1.add(2.5);
    for(int i = 0; i < v1.get_size(); i++) {
        std::cout << v1[i] << "\n";
    }

    // //TEST <string>
    custom_vector<std::string> v2(3);
    std::string str = "hello world";
    v2.test();

    for(int i = 0; i < v2.get_size(); i++) {
        v2.at(i) = str;
    }
    v2.add("bye world");
    for(int i = 0; i < v2.get_size(); i++) {
        std::cout << v2[i] << "\n";
    }
}



