#include "fixture.hpp"

TEST_F(AlgoTest, TestAllOf)
{
    auto lambda = [](int i) { return i > 0x01; };
    bool result = std::all_of(v_.begin(), v_.end(), lambda);
    EXPECT_FALSE(result);
}

TEST_F(AlgoTest, TestAnyOf)
{
    auto lambda = [](int i) { return i < 0x55; };
    bool result = std::any_of(v_.begin(), v_.end(), lambda);
    EXPECT_TRUE(result);
}

TEST_F(AlgoTest, TestNoneOf)
{
    auto lambda = [](int i) { return i < 0; };
    bool result = std::none_of(v_.begin(), v_.end(), lambda);
    EXPECT_TRUE(result);
}

TEST_F(AlgoTest, TestForEach)
{
    auto lambda1 = [](int& i) { i*=-1; };
    // Multiply each element with -1
    std::for_each(v_.begin(), v_.end(), lambda1);
    auto lambda2 = [](int i) { return i<1; };
    // Check if all elements < 0
    bool result = std::all_of(v_.begin(), v_.end(), lambda2);
    EXPECT_TRUE(result);
}

TEST_F(AlgoTest, TestFind)
{
    std::vector<int>::iterator it = std::find(v_.begin(), v_.end(), 0x10);
    EXPECT_EQ(it, v_.end());
}

TEST_F(AlgoTest, TestFindIf)
{
    auto lambda = [](int i) { return i > 0x50;};
    std::vector<int>::iterator it = std::find_if(v_.begin(), v_.end(), lambda);
    EXPECT_EQ(*it, 0x55);
}

TEST_F(AlgoTest, TestFindIfNot)
{
    auto lambda = [](int i) { return i < 0xF0;};
    std::vector<int>::iterator it = std::find_if_not(v_.begin(), v_.end(), lambda);
    EXPECT_EQ(*it, 0xFF);// Surrender at 20. GG!
}

TEST_F(AlgoTest, TestFindFirstOf)
{
    std::string pattern = "ee";
    std::string::iterator it = std::find_first_of(
        str_.begin(), str_.end(),
        pattern.begin(), pattern.end());
    std::string::iterator itT = std::find(str_.begin(), str_.end(), 'T');
    EXPECT_EQ(it, itT + 1);
}

TEST_F(AlgoTest, TestFindEnd)
{
    std::string pattern = "ee";    
    std::string::iterator it = std::find_end(
        str_.begin(), str_.end(),
        pattern.begin(), pattern.end());
    std::string::iterator itW = std::find(str_.begin(), str_.end(), 'W');
    EXPECT_EQ(it, itW + 1);
    
}

TEST_F(AlgoTest, TestAdjacentFind)
{  
    std::string::iterator it = std::adjacent_find(
        str_.begin(), str_.end());
    std::string::iterator itE = std::find(str_.begin(), str_.end(), 'e');
    EXPECT_EQ(it, itE);
}

TEST_F(AlgoTest, TestCount)
{
    int count = std::count(str_.begin(), str_.end(), 'e');
    EXPECT_EQ(count, 4);
}

TEST_F(AlgoTest, TestCountIf)
{
    auto lambda = [](char c) {return c < 'f' && c > 'a';};
    int count = std::count_if(str_.begin(), str_.end(), lambda);
    EXPECT_EQ(count, 4);
}

TEST_F(AlgoTest, TestMismatch)
{
    std::string s = "Teeny weeny";
    std::pair<std::string::iterator, std::string::iterator> p = std::mismatch(
        str_.begin(), str_.end(), s.begin()
    );
    EXPECT_EQ(*p.second, 'w');
}

TEST_F(AlgoTest, TestEqual)
{
    std::string s = "Teeny Weeny";
    bool result = std::equal(
        str_.begin(), str_.end(), s.begin()
    );
    EXPECT_TRUE(result);
}

TEST_F(AlgoTest, TestIsPermutation)
{
    std::vector<int> v2 = {0x33,0x44,0x00,0x11,0x22};
    bool result = std::is_permutation(v_.begin(), v_.begin()+5, v2.begin());
    EXPECT_TRUE(result);
}

TEST_F(AlgoTest, TestSearch)
{
    std::string pattern = "We";    
    std::string::iterator it = std::search(
        str_.begin(), str_.end(),
        pattern.begin(), pattern.end());
    std::string::iterator itW = std::find(str_.begin(), str_.end(), 'W');
    EXPECT_EQ(it, itW); //EXPECT_EQ(*it, 'W');
}

TEST_F(AlgoTest, TestSearchN)
{
    std::string::iterator it = std::search_n(
        str_.begin(),str_.end(),
        2, 'e'
    );
    std::string::iterator itE = std::find(str_.begin(), str_.end(), 'e');
    EXPECT_EQ(it, itE);
}

TEST_F(AlgoTest, TestLexCompare)
{
    std::string s = "teeny weeny";
    bool result = std::lexicographical_compare(
        str_.begin(), str_.end(),
        s.begin(),s.end());
    EXPECT_TRUE(result);
}

TEST_F(AlgoTest, TestCopy)
{
    std::vector<int> v(3);
    std::vector<int>::iterator it = std::copy(
        v_.begin(), v_.begin()+3,
        v.begin());

    int sum = *it + *(it - 1) + *(it - 2);
    EXPECT_EQ(sum, 0x33);
}

TEST_F(AlgoTest, TestCopyN)
{
    std::vector<int> v(2);
    std::vector<int>::iterator it = std::copy_n(
        v_.begin(), 2, v.begin());

    int sum = *it + *(it - 1);
    EXPECT_EQ(sum,0x11);// 0x00 + 0x11

}

TEST_F(AlgoTest, TestCopyIf)
{
    std::vector<int> v(3);
    auto lambda = [](int i) {return i<0x30;};
    std::vector<int>::iterator it = std::copy_if(
        v_.begin(), v_.end(),
        v.begin(), lambda);
    EXPECT_EQ(*(it-1), 0x22);//Copy if returns end iterator
}

TEST_F(AlgoTest, TestCopyBackward)
{
    std::vector<int> v(16);
    std::vector<int>::iterator it = std::copy_backward(
        v_.begin(), v_.end(),
        v.end());

    EXPECT_EQ(*it, 0x00);
}

TEST_F(AlgoTest, TestMove)
{
    std::vector<int> v(16);
    std::vector<int>::iterator it = std::move(
        v_.begin(), v_.end(), v.begin());

    EXPECT_EQ(*(it-1), 0xFF);
}

TEST_F(AlgoTest, TestMoveBackward)
{
    std::vector<int> v(16);
    std::vector<int>::iterator it = std::move_backward(
        v_.begin(), v_.end(), v.end());

    EXPECT_EQ(*(it+1), 0xFF);
}