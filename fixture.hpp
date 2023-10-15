#include <iostream>
#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

class AlgoTest: public ::testing::Test
{
protected:
    void SetUp() override {
        for (size_t i = 0; i < 16; i++)
        { v_.push_back(0x11*i); }      
        str_ = "Teeny Weeny";  
    }

    std::vector<int> v_;
    std::string str_ = "Teeny Weeny";
};

