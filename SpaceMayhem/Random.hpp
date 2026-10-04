#ifndef RANDOM_HPP
#define RANDOM_HPP

static class Random
{
public:
	static bool getBool(double percentage);
	static bool getBool(int percentage);
	static int getInt(int min, int max);
	static int getInt(int range);
};

#endif
