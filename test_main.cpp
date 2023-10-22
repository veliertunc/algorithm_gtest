#include "fixture.hpp"

typedef std::vector<int> VecInt_t;

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
    VecInt_t::iterator it = std::find(v_.begin(), v_.end(), 0x10);
    EXPECT_EQ(it, v_.end());
}

TEST_F(AlgoTest, TestFindIf)
{
    auto lambda = [](int i) { return i > 0x50;};
    VecInt_t::iterator it = std::find_if(v_.begin(), v_.end(), lambda);
    EXPECT_EQ(*it, 0x55);
}

TEST_F(AlgoTest, TestFindIfNot)
{
    auto lambda = [](int i) { return i < 0xF0;};
    VecInt_t::iterator it = std::find_if_not(v_.begin(), v_.end(), lambda);
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
    VecInt_t v2 = {0x33,0x44,0x00,0x11,0x22};
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
    VecInt_t v(3);
    VecInt_t::iterator it = std::copy(
        v_.begin(), v_.begin()+3,
        v.begin());

    int sum = *it + *(it - 1) + *(it - 2);
    EXPECT_EQ(sum, 0x33);
}

TEST_F(AlgoTest, TestCopyN)
{
    VecInt_t v(2);
    VecInt_t::iterator it = std::copy_n(
        v_.begin(), 2, v.begin());

    int sum = *it + *(it - 1);
    EXPECT_EQ(sum,0x11);// 0x00 + 0x11

}

TEST_F(AlgoTest, TestCopyIf)
{
    VecInt_t v(3);
    auto lambda = [](int i) {return i<0x30;};
    VecInt_t::iterator it = std::copy_if(
        v_.begin(), v_.end(),
        v.begin(), lambda);
    EXPECT_EQ(*(it-1), 0x22);//Copy if returns end iterator
}

TEST_F(AlgoTest, TestCopyBackward)
{
    VecInt_t v(16);
    VecInt_t::iterator it = std::copy_backward(
        v_.begin(), v_.end(),
        v.end());

    EXPECT_EQ(*it, 0x00);
}

TEST_F(AlgoTest, TestMove)
{
    VecInt_t v(16);
    VecInt_t::iterator it = std::move(
        v_.begin(), v_.end(), v.begin());

    EXPECT_EQ(*(it-1), 0xFF);
}

TEST_F(AlgoTest, TestMoveBackward)
{
    VecInt_t v(16);
    VecInt_t::iterator it = std::move_backward(
        v_.begin(), v_.end(), v.end());

    EXPECT_EQ(*(it+1), 0x11);
}

TEST_F(AlgoTest, TestSwap)
{
    std::swap(v_[0],*(v_.end()-1));
    EXPECT_EQ(*v_.begin(), 0xFF);
}

TEST_F(AlgoTest, TestSwapRanges)
{
    VecInt_t v(5);
    VecInt_t::iterator it = std::swap_ranges(
        v_.begin(), v_.begin()+4, v.begin());

    EXPECT_EQ(*(it-1), 0x33);
    EXPECT_EQ(*(v_.begin()+3), 0x00);
}

TEST_F(AlgoTest, TestIterSwap)
{
    VecInt_t::iterator it1 = v_.begin(); // Points to 1
    VecInt_t::iterator it2 = v_.end() - 1; // Points to 4
    
    std::iter_swap(it1, it2);

    EXPECT_EQ(*it1, 0xFF);
}

TEST_F(AlgoTest, TestTransform)
{
    
    VecInt_t v(5);
    auto lambda = [](int i) {return i << 2;};

    VecInt_t::iterator it = std::transform(
        v_.begin(), v_.begin()+4,
        v.begin(), lambda
    );

    EXPECT_EQ(*(it-1), 0xCC);
}

TEST_F(AlgoTest, TestReplace)
{
    std::replace(str_.begin(), str_.end(),
    'e','a');
    EXPECT_EQ(str_[1], 'a');
}

TEST_F(AlgoTest, TestReplaceIf)
{
    auto lambda = [](int i) { return i<0x50; };
    std::replace_if(v_.begin(), v_.end(),
    lambda,0x100);
    EXPECT_EQ(v_[0], 0x100);
}

TEST_F(AlgoTest, TestReplaceCopy)
{
    std::string s;
    std::string::iterator it = std::replace_copy(
        str_.begin(), str_.end(),
        s.begin(),'e','a');
    EXPECT_EQ(s[1], 'a');
}

TEST_F(AlgoTest, TestReplaceCopyIf)
{
    auto lambda = [](char c) { return isupper(c);};

    std::string::iterator it = std::replace_copy_if(
        str_.begin(), str_.end(),
        str_.begin(),lambda, ' ');
    EXPECT_EQ(str_, " eeny  eeny");
}

TEST_F(AlgoTest, TestFill)
{
    std::fill(v_.begin(),v_.end(), 0xFF);
    auto lambda = [](int i) { return i==0xFF;};

    bool result = std::all_of(v_.begin(),v_.end(),lambda);
    EXPECT_TRUE(result);
}

TEST_F(AlgoTest, TestFillN)
{
    std::fill_n(v_.begin(), 4,0xFF);
    auto lambda = [](int i) { return i==0xFF;};
    int count=std::count(v_.begin(),v_.end(),0xFF);
    EXPECT_EQ(count,5);
}

TEST_F(AlgoTest, TestGenerate)
{
    
    std::generate(v_.begin(),v_.end(), [](){
        // This is a random generator function
        return 0xFF;
    });

    auto lambda = [](int i) { return i==0xFF;};

    bool result = std::all_of(v_.begin(),v_.end(),lambda);
    EXPECT_TRUE(result);
}

TEST_F(AlgoTest, TestGenerateN)
{
    std::generate_n(v_.begin(), 4,[](){
        return 0xFF;
    });
    auto lambda = [](int i) { return i==0xFF;};
    int count=std::count(v_.begin(),v_.end(),0xFF);
    EXPECT_EQ(count,5);
}

TEST_F(AlgoTest, TestRemove)
{
    std::string::iterator it = std::remove(
        str_.begin(), str_.end(),'e'
    );

    EXPECT_EQ(str_, "Tny Wnyeeny");
}

TEST_F(AlgoTest, TestRemoveIf)
{
    std::string s = str_;
    auto lambda = [s](char c){
        return std::count(s.begin(),s.end(),c)<2;
    };

    std::string::iterator it = std::remove_if(
        str_.begin(), str_.end(),lambda
    );

    EXPECT_EQ(str_, "eenyeenyeny");
}

TEST_F(AlgoTest, TestRemoveCopy)
{
    VecInt_t res(16);
    VecInt_t::iterator it = std::remove_copy(
        v_.begin(),v_.end(),res.begin(),0xFF
    );
    
    EXPECT_EQ(*(res.end()-1), 0x00);
}

TEST_F(AlgoTest, TestRemoveCopyIf)
{
    VecInt_t res(16);
    auto lambda = [](int i) { return i%2!=0; };

    VecInt_t::iterator it = std::remove_copy_if(
        v_.begin(),v_.end(),res.begin(),lambda
    );
    int zeroCnt = std::count(
        res.begin(),res.end(), 0x00
    );

    EXPECT_GE(zeroCnt, 0x05);
}

TEST_F(AlgoTest, TestUnique)
{
    VecInt_t v {1,2,2,3,3,3,4,4,4,4};
    VecInt_t res {1,2,3,4,3,3,4,4,4,4};
    VecInt_t::iterator it = std::unique(v.begin(),v.end());
    EXPECT_EQ(v,res);    
}

TEST_F(AlgoTest, TestUniqueCopy)
{
    VecInt_t v {1,2,2,3,3,3,4,4,4,4};
    VecInt_t res(10);
    const VecInt_t r {1,2,3,4,0,0,0,0,0,0};
    VecInt_t::iterator it = std::unique_copy(
        v.begin(),v.end(), res.begin()
    );
    EXPECT_EQ(r,res);
}

TEST_F(AlgoTest, TestReverse)
{
    VecInt_t v {1,2,3,4};
    VecInt_t res {4,3,2,1};
    std::reverse(v.begin(),v.end());
    EXPECT_EQ(v,res);    
}

TEST_F(AlgoTest, TestReverseCopy)
{
    VecInt_t v {1,2,3,4};
    VecInt_t res(4);
    const VecInt_t r{4,3,2,1};
    VecInt_t::iterator it = std::reverse_copy(
        v.begin(),v.end(),res.begin()
    );

    EXPECT_EQ(r,res);
}

TEST_F(AlgoTest, TestRotate)
{
    VecInt_t v {1,2,3,4};
    VecInt_t res {3,4,1,2};
    VecInt_t::iterator it = v.begin()+2;
    std::rotate(v.begin(),it,v.end());
    EXPECT_EQ(v,res);    
}

TEST_F(AlgoTest, TestRotateCopy)
{
    std::vector<int> v{ 1, 2, 3, 4 };
    std::vector<int> res(4);std::vector<int>::iterator it1 = v.begin() + 2;
    const VecInt_t r{3,4,1,2};
    std::vector<int>::iterator it2 = std::rotate_copy(
        v.begin(), it1, v.end(), res.begin()
    );

    EXPECT_EQ(r,res);
}

TEST_F(AlgoTest, TestIsPartitioned)
{
    VecInt_t v {1,3,5,2,4,6};
    auto lambda = [](int i){return i%2!=0;};
    bool res = std::is_partitioned(
        v.begin(), v.end(),lambda
    );
    EXPECT_TRUE(res);

    res = std::is_partitioned(
        v_.begin(), v_.end(),lambda
    );
    EXPECT_FALSE(res);
}

TEST_F(AlgoTest, TestPartition)
{
    auto lambda = [](int i){return i%2!=0;};
    VecInt_t::iterator it = std::partition(
        v_.begin(),v_.end(),lambda
    );
}

TEST_F(AlgoTest, TestStablePartition)
{
    auto lambda = [](int i){return i%2!=0;};
    VecInt_t::iterator it = std::stable_partition(
        v_.begin(),v_.end(),lambda
    );
    const VecInt_t r{
        0x11,0x33,0x55,0x077,0x99,0xBB,0xDD,0xFF,
        0x00,0x22,0x44,0x66,0x88,0xAA,0xCC,0xEE
    };
    EXPECT_EQ(v_,r);
}

TEST_F(AlgoTest, TestSort)
{
    std::vector<int> v{ 5, 3, 4, 2, 1 };
    std::sort(v.begin(), v.end());
    const VecInt_t r{1,2,3,4,5};
    EXPECT_EQ(v,r);
}

TEST_F(AlgoTest, TestStableSort)
{
    std::vector<int> v{ 5, 3,1, 4, 2, 1 };
    std::stable_sort(v.begin(), v.end());
    const VecInt_t r{1,1,2,3,4,5};
    EXPECT_EQ(v,r);
}

TEST_F(AlgoTest, TestIsSorted)
{
    EXPECT_TRUE(std::is_sorted(v_.begin(),v_.end()));
}
