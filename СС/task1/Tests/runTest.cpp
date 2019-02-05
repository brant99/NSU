#include "gtest/gtest.h"
#include "TritSet.h"
class TritTest:public::testing::Test{
};
TEST_F(TritTest,verOperators){
    TritSet A(10),B(20),C(30);
    Trit ar[3]={True,False,Unknown};
    for(int i=0;i<10;i++) {
        A[i] = ar[i%3];
        B[i] = ar[(i+1)%3];
    }
    C=A&B;
    EXPECT_EQ(False, const_cast<const TritSet&>(C)[0]);
    EXPECT_EQ(False, const_cast<const TritSet&>(C)[1]);
    EXPECT_EQ(Unknown, const_cast<const TritSet&>(C)[2]);
    EXPECT_EQ(Unknown, const_cast<const TritSet&>(C)[20]);

    C=A|A;
    EXPECT_EQ(True, const_cast<const TritSet&>(C)[0]);
    EXPECT_EQ(False, const_cast<const TritSet&>(C)[1]);
    EXPECT_EQ(Unknown, const_cast<const TritSet&>(C)[2]);

    C=~A;
    EXPECT_EQ(False, const_cast<const TritSet&>(C)[0]);
    EXPECT_EQ(True, const_cast<const TritSet&>(C)[1]);
    EXPECT_EQ(Unknown, const_cast<const TritSet&>(C)[2]);

    C[20]=True;
    EXPECT_EQ(True, const_cast<const TritSet&>(C)[20]);

    A[1]=A[0];
    EXPECT_EQ(True, const_cast<const TritSet&>(A)[1]);
}
TEST_F(TritTest,testFunc){
    TritSet A(20);
    ASSERT_TRUE((20/(4* sizeof(uint)))<=A.capacity());
    EXPECT_EQ(A.length(),1);
    A[5]=True;
    EXPECT_EQ(A.length(),6);
    A.shrink();
    ASSERT_TRUE(A.capacity()>=6/4* sizeof(uint));
}