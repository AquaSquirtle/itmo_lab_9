#include <gtest/gtest.h>
#include <lib/adapter.hpp>
#include "algorithm"
#include "map"
#include "set"

TEST(AdapterTest, EmptyVector) {
    std::vector<int> empty_vector;
    std::vector<int> result_vector;
    auto changed_vector = empty_vector | transform([](int i){return i * i;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));

    auto result_filter = empty_vector | filter([](int i){return i % 2 == 0;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));

    auto result_take = empty_vector | take(3);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));

    auto result_drop = empty_vector | drop(3);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));

    auto result_reverse = empty_vector | reverse();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(AdapterTest, EmptyMap) {
    std::map<int, int> empty_map;
    std::map<int, int> result_map;
    std::vector<int> result_vector;
    auto result_keys = empty_map | keys();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result_keys.begin()));

    auto result_values = empty_map | values();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result_values.begin()));

    auto result_filter = empty_map | filter([](const std::pair<int, int>& p){return p.second % 2 == 0;});
    EXPECT_TRUE(std::equal(result_filter.begin(), result_filter.end(), result_map.begin()));

}

TEST (Adapter_test, TransformAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {1,4,9,16,25};
    auto changed_vector = test_vector | transform([](int i){return i*i;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, FilterAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {1,3,5};
    auto changed_vector = test_vector | filter([](int i){return i%2;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, TakeAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {1,2,3};
    auto changed_vector = test_vector | take(3);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, DropAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {4,5};
    auto changed_vector = test_vector | drop(3);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, ReverseAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {5,4,3,2,1};
    auto changed_vector = test_vector | reverse();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, MapKeysAdapter) {
    std::map<int,int> test_map {{1,1},{2,2},{3,3},{4,4},{5,5}};
    std::vector<int> result_vector {1,2,3,4,5};
    auto changed_vector = test_map | keys();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, SetKeysAdapter) {
    std::set<int> test_set{1,2,3,4,5};
    std::vector<int> result_vector {1,2,3,4,5};
    auto changed_vector = test_set | keys();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}


TEST(Adapter_test, MapValuesAdapter) {
    std::map<int,int> test_map {{1,1},{2,2},{3,3},{4,4},{5,5}};
    std::vector<int> result_vector {1,2,3,4,5};
    auto changed_vector = test_map | values();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, SetValuesAdapter) {
    std::set<int> test_set{1,2,3,4,5};
    std::vector<int> result_vector {1,2,3,4,5};
    auto changed_vector = test_set | values();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}


TEST(Adapter_test, DropFilterAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {5};
    auto changed_vector = test_vector | drop(3) | filter([](int i){return i % 2;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, FilterDropAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {3,5};
    auto changed_vector = test_vector | filter([](int i){return i % 2;}) | drop(1);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, TransformFilterAdaptor) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {3,9,15};
    auto changed_vector = test_vector | transform([](int i){return i * 3;})| filter([](int i){return i % 2;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, FilterTransformAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {3,9,15};
    auto changed_vector = test_vector | filter([](int i){return i % 2;}) | transform([](int i){return i*3;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}


TEST(Adapter_test, ReverseTakeAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {5,4};
    auto changed_vector = test_vector | reverse() | take(2);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, ReverseDropAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {3,2,1};
    auto changed_vector = test_vector | reverse() | drop(2);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, TransformKeysAdapter) {
    std::map<int,int> test_map {{1,1},{2,2},{3,3},{4,4},{5,5}};
    std::vector<int> result_vector {10,20,30,40,50};
    auto changed_vector = test_map | transform([](std::pair<int,int> i){return std::make_pair(i.first * 10, i.second / 2);}) | keys();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, TransformValuesAdapter) {
    std::map<int,int> test_map {{1,1},{2,2},{3,3},{4,4},{5,5}};
    std::vector<int> result_vector {0,1,1,2,2};
    auto changed_vector = test_map | transform([](std::pair<int,int> i){return std::make_pair(i.first * 10, i.second / 2);}) | values();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, FilterKeysAdapter) {
    std::map<int,int> test_map {{1,4},{2,2},{3,5},{4,5},{5,5}};
    std::vector<int> result_vector {1,2};
    auto changed_vector = test_map | filter([](std::pair<int,int> i){return i.second % 2 == 0;}) | keys();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, FilterValuesAdapter) {
    std::map<int,int> test_map {{1,4},{2,2},{3,5},{4,5},{5,5}};
    std::vector<int> result_vector {4,2};
    auto changed_vector = test_map | filter([](std::pair<int,int> i){return i.second % 2 == 0;}) | values();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}

TEST(Adapter_test, FilterKeysTransformAdapter) {
    std::map<int,int> test_map {{871,24},{22,92},{53,59},{674,589},{1238,3455}, {10,764},{56,2123},{89,5653},{99,5234},{100,15123}};
    std::vector<int> result_vector {2,5,24,217};
    auto changed_vector = test_map | filter([](std::pair<int,int> i){return i.second % 2 == 0;}) | keys() | transform([](int i){return i / 4;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}


TEST(Adapter_test, FilterValuesTransformAdapter) {
    std::map<int,int> test_map {{871,24},{22,92},{53,59},{674,589},{1238,3455}, {10,764},{56,2123},{89,5653},{99,5234},{100,15123}};
    std::vector<int> result_vector {191, 23, 530, 3780, 147, 863};
    auto changed_vector = test_map | filter([](std::pair<int,int> i){return i.first % 2 == 0;}) | values() | transform([](int i){return i / 4;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), changed_vector.begin()));
}


TEST(AdapterTest, DropBeforeFilterAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {5};
    auto result = test_vector | drop(3) | filter([](int i){return i % 2;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, FilterBeforeDropAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {3,5};
    auto result = test_vector | filter([](int i){return i % 2;}) | drop(1);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, TransformFilterAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {3,9,15};
    auto result = test_vector | transform([](int i){return i * 3;}) | filter([](int i){return i % 2;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, FilterTransformAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {3,9,15};
    auto result = test_vector | filter([](int i){return i % 2;}) | transform([](int i){return i*3;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, ReverseBeforeTakeAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {5,4};
    auto result = test_vector | reverse() | take(2);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, ReverseBeforeDropAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {3,2,1};
    auto result = test_vector | reverse() | drop(2);
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, TransformKeysAdapter) {
    std::map<int,int> test_map {{1,1},{2,2},{3,3},{4,4},{5,5}};
    std::vector<int> result_vector {10,20,30,40,50};
    auto result = test_map | transform([](std::pair<int,int> i){return std::make_pair(i.first * 10, i.second / 2);}) | keys();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, TransformValuesAdapter) {
    std::map<int,int> test_map {{1,1},{2,2},{3,3},{4,4},{5,5}};
    std::vector<int> result_vector {0,1,1,2,2};
    auto result = test_map | transform([](std::pair<int,int> i){return std::make_pair(i.first * 10, i.second / 2);}) | values();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, FilterKeysAdapter) {
    std::map<int,int> test_map {{1,4},{2,2},{3,5},{4,5},{5,5}};
    std::vector<int> result_vector {1,2};
    auto result = test_map | filter([](std::pair<int,int> i){return i.second % 2 == 0;}) | keys();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, FilterValuesAdapter) {
    std::map<int,int> test_map {{1,4},{2,2},{3,5},{4,5},{5,5}};
    std::vector<int> result_vector {4,2};
    auto result = test_map | filter([](std::pair<int,int> i){return i.second % 2 == 0;}) | values();
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, FilterKeysTransformAdapter) {
    std::map<int,int> test_map {{871,24},{22,92},{53,59},{674,589},{1238,3455}, {10,764},{56,2123},{89,5653},{99,5234},{100,15123}};
    std::vector<int> result_vector {2,5,24,217};
    auto result = test_map | filter([](std::pair<int,int> i){return i.second % 2 == 0;}) | keys() | transform([](int i){return i / 4;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, FilterValuesTransformAdapter) {
    std::map<int,int> test_map {{871,24},{22,92},{53,59},{674,589},{1238,3455}, {10,764},{56,2123},{89,5653},{99,5234},{100,15123}};
    std::vector<int> result_vector {191, 23, 530, 3780, 147, 863};
    auto result = test_map | filter([](std::pair<int,int> i){return i.first % 2 == 0;}) | values() | transform([](int i){return i / 4;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, EmptyVectorFilterAndTransform) {
    std::vector<int> test_vector;
    std::vector<int> result_vector;
    auto result = test_vector | filter([](int i){ return i % 2 == 0; }) | transform([](int i){ return i * i; });
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, ReverseTakeFilterAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {5,3};
    auto result = test_vector | reverse() | take(3) | filter([](int i){return i % 2 != 0;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

TEST(AdapterTest, TakeReverseTransformAdapter) {
    std::vector<int> test_vector {1,2,3,4,5};
    std::vector<int> result_vector {9,4,1};
    auto result = test_vector | take(3) | reverse() | transform([](int i){return i * i;});
    EXPECT_TRUE(std::equal(result_vector.begin(), result_vector.end(), result.begin()));
}

