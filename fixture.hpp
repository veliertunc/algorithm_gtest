#include <iostream>
#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

typedef std::vector<int> VecInt_t;
class AlgoTest: public ::testing::Test
{
protected:
    void SetUp() override {
        for (size_t i = 0; i < 16; i++)
        { v_.push_back(0x11*i); }      
        str_ = "Teeny Weeny";  
    }

   VecInt_t v_;
    std::string str_;
};

