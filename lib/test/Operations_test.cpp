/**
 * @file Operations_test.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "gtest/gtest.h"
#include <iostream>
#include <math.h>

#include "../Factory.hpp"

class Operations_test : public testing::Test {};

TEST(Function_test, Arithmetic) {
    FunctionFactory F;

    auto A1 = F.Create("polynomial", {0, 2, 1});
    auto A2 = F.Create("polynomial", {0, 1, 2});
    auto A3 = *A1 + *A2;
    ASSERT_EQ(A3(1), 6);
    ASSERT_EQ(A3(2), 18);
    ASSERT_EQ((*A1 - *A2)(1), 0);
    ASSERT_EQ((*A1 - *A2)(2), -2);
    ASSERT_EQ((*A1 * *A2)(1), 9);
    ASSERT_EQ((*A1 * *A2)(2), 80);

    auto A4 = F.Create("exp", 0);
    ASSERT_EQ((A3 / *A4)(1), 6);
    ASSERT_EQ((A3 / *A4)(2), 18);

    auto A5 = A3 / *A4;
    auto A6 = F.Create("const", 18);
    ASSERT_EQ((A5 / *A6)(2), 1);
}

TEST(Function_test, Deriation) {
    FunctionFactory F;

    /* From example: */

    auto f = F.Create("power", 2);
    auto g = F.Create("polynomial", {7, 0, 3, 15});
    auto p = *f + *g;
    ASSERT_EQ(p.Deriative(1), 53);
    ASSERT_THROW(*f + "abc", std::logic_error);
    ASSERT_EQ(f->Deriative(3), 6);

    /* Other */

    auto k = F.Create("exp", 2);
    ASSERT_EQ((*k).Deriative(2), ((*k) + (*k))(2));
    ASSERT_EQ((*k).Deriative(20), ((*k) + (*k))(20));
}

TEST(Function_test, RootSearch) {
    FunctionFactory F;

    auto f = F.Create("ident", 1);
    ASSERT_EQ(FindRoot((*f), 2), 0);
    auto g = F.Create("polynomial", {4, -1});
    ASSERT_EQ(std::round(FindRoot((*g), 1000, -10)), 4);
    auto p = F.Create("polynomial", {1, 0, -1});
    ASSERT_EQ(std::round(FindRoot((*p), 20, -2)), -1);
    ASSERT_EQ(std::round(FindRoot((*p), 20, 2)), 1);
    auto h = F.Create("polynomial", {8, 0, 0, -1});
    ASSERT_EQ(std::round(FindRoot((*h), 1000, 2)), 2);

}

TEST(Function_test, LogicError) {
    FunctionFactory F;

    auto A1 = F.Create("polynomial", {0, 2});
    ASSERT_THROW(*A1 + "abc", std::logic_error);
    ASSERT_THROW(*A1 + A1, std::logic_error);

    auto A2 = F.Create("ident", 2);
    auto A3 = *A1 + *A2;
    ASSERT_THROW(A3 + "abc", std::logic_error);
    ASSERT_THROW(A3 + A1, std::logic_error);
}