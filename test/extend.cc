// This file is a part of std-adiog project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <strong>
#include <forward>

#include <string>

#include <gtest/gtest.h>

EXTEND_STD_CLASS(ExtendString, string);
CONTAIN_STD_CLASS(ContainString, string);
USING_STRONG(Int32, int32_t);

TEST(ExtendTestSuite, ExtendString)
{
    ExtendString s;
    ExtendString s2{"abc"};
    ExtendString s3 = ExtendString("abcd", 2);
    std::string str = "hello";

    std::cout << s;
    std::cout << s2;
    std::cout << s3;

    s2 = str;

    ASSERT_EQ(str, s2);
}

TEST(ExtendTestSuite, ConainString)
{
    ContainString s;
    ContainString s2{"abc"};
    ContainString s3 = ContainString("abcd", 2);
    std::string str = "hello";

    std::cout << s.impl;
    std::cout << s2.impl;
    std::cout << s3.impl;


    s2 = str;

    ASSERT_EQ(str, s2.impl);
}
