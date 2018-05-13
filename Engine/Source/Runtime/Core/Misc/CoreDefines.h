#pragma once

#ifdef DEBUG_BUILD

#include <iostream>

#define ASSERT(x, y) \
	if (!(x)) \
	{ \
		std::cerr << "ERR::ASSERT\t[" \
		<< y << "]\t" << __FILE__ << " : "\
		<< __LINE__ << "\n"; \
		exit(0); \
	}
	
#define DEBUG(x) \
	std::cout << "SYS::DEBUG\t" << (x) << "\n";
	
#else

#define ASSERT(x, y) \
	do \
	{ \
	(x) \
	} \
	while (0)

#define DEBUG(x) \
	do \
	{ \
	(x); \
	} \
	while (0)

#endif