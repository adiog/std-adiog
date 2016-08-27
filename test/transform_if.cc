// This file is a part of std-adiog project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <transform_if>

#include <set>
#include <vector>

#include <gtest/gtest.h>


namespace {

auto aTransform = [](double iDouble) 
{
    return static_cast<int>(iDouble * iDouble);
};

auto aPredicate = [](double iDouble) 
{
    return iDouble > 5.7;
};

std::vector<int> transformIfVectorToVectorFixedLogic(std::vector<double> &v)
{
    return ::adg::transform_if(v, aTransform, aPredicate);
}

std::set<int> transformIfVectorToSetFixedLogic(std::vector<double> &v)
{
    return ::adg::transform_if(v, aTransform, aPredicate);
}

std::vector<double> buildInputVector()
{
    return {4.4, 5.5, 6.6, 7.7, 8.8};
}

std::vector<int> buildExpectedOutputVector()
{
    return {43, 59, 77};
}

std::set<int> buildExpectedOutputSet()
{
    return {43, 59, 77};
}

TEST(TransformIfTestSuite, VectorToVectorWithOutputParameter)
{
    auto anInputVector = buildInputVector();
    std::vector<int> anOutputVector;

    ::adg::transform_if(
        anInputVector,
        aTransform,
        aPredicate,
        anOutputVector);

    EXPECT_EQ(anOutputVector, buildExpectedOutputVector());
}

TEST(TransformIfTestSuite, VectorToVectorWithExplicitReturnType)
{
    auto anInputVector = buildInputVector();

    auto anOutputVector = ::adg::transform_if<std::vector<int>>(
        anInputVector,
        aTransform,
        aPredicate);

    EXPECT_EQ(anOutputVector, buildExpectedOutputVector());
}

TEST(TransformIfTestSuite, VectorToVectorWithImplicitReturnType)
{
    auto anInputVector = buildInputVector();

    std::vector<int> anOutputVector = ::adg::transform_if(
        anInputVector,
        aTransform,
        aPredicate);

    EXPECT_EQ(anOutputVector, buildExpectedOutputVector());
}

TEST(TransformIfTestSuite, VectorToVectorWithImplicitFunctionReturnType)
{
    auto anInputVector = buildInputVector();

    std::vector<int> anOutputVector = transformIfVectorToVectorFixedLogic(anInputVector);

    EXPECT_EQ(anOutputVector, buildExpectedOutputVector());
}

TEST(TransformIfTestSuite, VectorToSet)
{
    auto anInputVector = buildInputVector();

    {
        std::set<int> anOutputSet;

        ::adg::transform_if(
            anInputVector,
            aTransform,
            aPredicate,
            anOutputSet);

        EXPECT_EQ(anOutputSet, buildExpectedOutputSet());
    }

    {
        auto anOutputSet = ::adg::transform_if<std::set<int>>(
            anInputVector,
            aTransform,
            aPredicate);

        EXPECT_EQ(anOutputSet, buildExpectedOutputSet());
    }

    {
        std::set<int> anOutputSet = ::adg::transform_if(anInputVector, aTransform, aPredicate);

        EXPECT_EQ(anOutputSet, buildExpectedOutputSet());
    }

    {
        std::set<int> anOutputSet = transformIfVectorToSetFixedLogic(anInputVector);

        EXPECT_EQ(anOutputSet, buildExpectedOutputSet());
    }
}
}
