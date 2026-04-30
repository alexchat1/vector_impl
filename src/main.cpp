#include <print>
#include <vector.h>
struct Foo {
    int bar_;
    std::string baz_;
    Foo(int bar, std::string baz): bar_(bar), baz_(baz) {}
};
int main() { 
    // random tests....

    alex::Vector<Foo> v1;
    
    std::println("{}", v1.size());

    v1.emplace_back(3, "Japa");
    v1.emplace_back(6, "Mike");

    for (size_t i = 0; i < v1.size(); i++) {
        std::println("bar_ = {}, baz_ = {}", v1[i].bar_, v1[i].baz_);
    }
    return 0;
}