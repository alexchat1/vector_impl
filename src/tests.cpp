#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "vector.h"
#include <stdexcept>
#include <string>

TEST_CASE("Vector basic operations") {
    alex::Vector<int> v;

    CHECK(v.empty());
    CHECK(v.size() == 0);

    v.push_back(10);
    v.push_back(20);

    CHECK(v.size() == 2);
    CHECK(v[0] == 10);
    CHECK(v[1] == 20);
    v.pop_back();
    CHECK_THROWS_AS(v.at(1), std::out_of_range);
    CHECK(v[0] == 10);
}

TEST_CASE("Vector emplace_back") {
    struct Foo {
        int bar;
        std::string baz;
        Foo(int b, std::string z) : bar(b), baz(std::move(z)) {}
    };

    alex::Vector<Foo> v;
    v.emplace_back(42, "Test");

    CHECK(v.size() == 1);
    CHECK(v[0].bar == 42);
    CHECK(v[0].baz == "Test");
}

TEST_CASE("Vector reserve") {
    alex::Vector<int> v;
    v.reserve(50);
    CHECK(v.capacity() >= 50);
    CHECK(v.size() == 0);
}

TEST_CASE("Vector construction") {
    alex::Vector<std::string> v1(5);
    CHECK(v1.size() == 5);
    CHECK(v1[4] == "");

    alex::Vector<std::string> v2 = {"ab", "cd", "ef"};
    CHECK(v2[0] == "ab");
    CHECK(v2[1] == "cd");
    CHECK(v2[2] == "ef");

    alex::Vector<std::string> v3(std::move(v2));
    CHECK(v3[0] == "ab");
    CHECK(v3[1] == "cd");
    CHECK(v3[2] == "ef");
    CHECK(v2.size() == 0);

    v1 = std::move(v3);
    CHECK(v1.size() == 3);
    CHECK(v1[0] == "ab");
    CHECK(v1[1] == "cd");
    CHECK(v1[2] == "ef");
    CHECK(v3.size() == 0);

    alex::Vector<int> v4(3, -1);
    CHECK(v4.size() == 3);
    CHECK(v4[0] == -1);
    CHECK(v4[1] == -1);
    CHECK(v4[2] == -1);

    alex::Vector<std::string> v5(v1);
    CHECK(v1.size() == 3);
    CHECK(v1[0] == "ab");
    CHECK(v1[1] == "cd");
    CHECK(v1[2] == "ef");

    CHECK(v5.size() == 3);
    CHECK(v5[0] == "ab");
    CHECK(v5[1] == "cd");
    CHECK(v5[2] == "ef");

    v2 = v5;
    CHECK(v5.size() == 3);
    CHECK(v5[0] == "ab");
    CHECK(v5[1] == "cd");
    CHECK(v5[2] == "ef");

    CHECK(v2.size() == 3);
    CHECK(v2[0] == "ab");
    CHECK(v2[1] == "cd");
    CHECK(v2[2] == "ef");

}