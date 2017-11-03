// This file is a part of LoremFeed project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <LoremFeed.h>
#include <iostream>

int main()
{
    std::cout << "for(auto r : LoremFeed::RandomInteger<unsigned char>().limit(10)):\n";
    for(auto r : LoremFeed::RandomInteger<unsigned char>().limit(10))
    {
        std::cout << int(r) << ',';
    }
    std::cout << "\n\n";

    std::cout << "for(auto r : LoremFeed::RandomInteger<short>().limit(10)):\n";
    for(auto r : LoremFeed::RandomInteger<short>().limit(10))
    {
        std::cout << r << ',';
    }
    std::cout << "\n\n";

    std::cout << "for(auto r : LoremFeed::RandomInteger<int>().limit(10)):\n";
    for(auto r : LoremFeed::RandomInteger<int>().limit(10))
    {
        std::cout << r << ',';
    }
    std::cout << "\n\n";

    std::cout << "for(auto r : LoremFeed::UniformInteger<int>(-3, 15).limit(10)):\n";
    for(auto r : LoremFeed::UniformInteger<int>(-3, 15).limit(10))
    {
        std::cout << r << ',';
    }
    std::cout << "\n\n";

    std::cout << "for(auto r : LoremFeed::RandomByDistribution<unsigned int>(std::poisson_distribution<unsigned int>(42)).limit(10)):\n";
    for(auto r : LoremFeed::RandomByDistribution<unsigned int>(std::poisson_distribution<unsigned int>(42)).limit(10))
    {
        std::cout << r << ',';
    }
    std::cout << "\n\n";

    std::cout << "for(auto r : LoremFeed::UniformFloat<float>(-10.0F, 10.0F).limit(10)):\n";
    for(auto r : LoremFeed::UniformFloat<float>(-10.0F, 10.0F).limit(10))
    {
        std::cout << r << ',';
    }
    std::cout << "\n\n";

    std::cout << "for(auto r : LoremFeed::RandomByDistribution<float>(std::normal_distribution(0.0F, 1.0F)).limit(10)):\n";
    for(auto r : LoremFeed::RandomByDistribution<float>(std::normal_distribution(0.0F, 1.0F)).limit(10))
    {
        std::cout << r << ',';
    }
    std::cout << "\n\n";

    struct POD {
        int a;
        float b;
        char c;
    };

    auto aGen = LoremFeed::UniformInteger(2,6);
    auto bGen = LoremFeed::UniformFloat(6.0F, 10.0F);
    auto cGen = LoremFeed::UniformInteger<char>(-5,5);
    for(auto r : LoremFeed::Pod<POD>([&aGen](){return aGen.get();},
                                     [&bGen](){return bGen.get();},
                                     [&cGen](){return cGen.get();}).limit(10))
    {
        std::cout << r.a << ',' << r.b << "," << int(r.c) << " ";
    }
    std::cout << "\n\n";

    const char* stringPtr = "This is truncated Hello World! string.";
    auto lenGen = LoremFeed::UniformInteger(20,30);
    std::cout << "for(const auto& r : LoremFeed::Emplace<std::string>([&stringPtr](){return stringPtr;},:\n";
    std::cout << "                                                    [&lenGen](){return lenGen.get();}).limit(10)):\n";
    for(const auto& r : LoremFeed::Emplace<std::string>([&stringPtr](){return stringPtr;},
                                                        [&lenGen](){return lenGen.get();}).limit(10))
    {
        std::cout << r << "\n";
    }
    std::cout << "\n\n";

    std::cout << "for(const auto& r : LoremFeed::StringFeed(8).limit(10)):\n";
    for(const auto& r : LoremFeed::StringFeed(8).limit(10))
    {
        std::cout << r << " - ";
    }
    std::cout << "\n\n";

    std::cout << "for(const auto& r : LoremFeed::RandomLengthString(4,12).limit(10)):\n";
        for(const auto& r : LoremFeed::RandomLengthString(4,12).limit(10))
    {
        std::cout << r << " - ";
    }
    std::cout << "\n\n";

    return 0;
}

