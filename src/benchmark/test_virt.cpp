
#include "test_virt.h"

void test::virt_next(int& i, int& sum)
{
	sum += i;
	i = -i;
}

void test::next(int& i, int& sum)
{
	sum += i;
	i = -i;
}