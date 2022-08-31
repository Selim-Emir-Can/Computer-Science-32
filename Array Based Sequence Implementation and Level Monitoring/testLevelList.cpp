#include"Sequence.h"
#include"LevelList.h"
#include<cassert>
#include<iostream>
#include<string>
#include<cstddef>
#include<cstdlib>

int main()
{
	LevelList ss;
	assert(ss.remove(0) == false);
	assert(ss.remove(1) == false);
	assert(ss.remove(30) == false);
	assert(ss.remove(400) == false);
	assert(ss.add(0) == false);
	assert(ss.add(3) == false);
	assert(ss.add(30) == true);
	assert(ss.add(400) == true);
	assert(ss.add(401) == false);
	assert(ss.size() == 2);
	assert(ss.maximum() == 400);
	assert(ss.minimum() == 30);

	return(0);
}