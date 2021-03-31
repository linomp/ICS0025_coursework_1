#include "RandomUtils.h"
#include <string>
#include <random>
#include<vector>

RandomUtils::RandomUtils(std::default_random_engine g)
{
    Generator = g;
}

int RandomUtils::getRandomInt(int lower_bound, int upper_bound)
{
    std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);

    return distribution(Generator);
}


int RandomUtils::getRandomSubgroup()
{
    return getRandomInt(0,99);
}

char RandomUtils::getRandomGroup()
{
    return (char) getRandomInt(65, 90);;
}

std::string RandomUtils::getRandomName()
{
    // TODO open file and get random element from it
    return std::string("test");
}

Date RandomUtils::getRandomTimestamp()
{
    return Date::CreateRandomDate(Date(1, 1, 2000), Date(1, 1, 2020));
}
