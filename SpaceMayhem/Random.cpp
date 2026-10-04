#include "Random.hpp"
#include <stdlib.h>
#include <time.h>

class RandomImp
{
public:
	static RandomImp& GetInstance(void)
	{
		static RandomImp instance;
		return instance;
	}

	bool getBool(double percentage)
	{
		return ((double)rand() / (double)RAND_MAX) < percentage;
	}

	bool getBool(int percentage)
	{
		return getInt(100) < percentage;
	}

	int getInt(int min, int max)
	{
		int range = max - min + 1;
		int value = rand() % range;
		return min + value;
	}

	int getInt(int range)
	{
		return rand() % range;
	}

private:
	RandomImp()
	{
		srand((unsigned int)time(NULL));
	}
};

bool Random::getBool(double percentage)
{
	return RandomImp::GetInstance().getBool(percentage);
}

bool Random::getBool(int percentage)
{
	return RandomImp::GetInstance().getBool(percentage);
}

int Random::getInt(int min, int max)
{
	return RandomImp::GetInstance().getInt(min, max);
}

int Random::getInt(int range)
{
	return RandomImp::GetInstance().getInt(range);
}
