#pragma once

#define DEBUG_BUILD

#ifdef DEBUG_BUILD

#include <iostream>

#define ASSERT(x, y) \
	if (!(x)) \
	{ \
		std::cerr << "ERR::ASSERT\t" \
		<< (y) << "\n\t\t" << __FILE__ << "\n\t\tLine " \
		<< __LINE__ << "\n"; \
		exit(0); \
	}
	
#define DEBUG(x) \
	std::cout << "SYS::DEBUG\t" << (x) << "\n";
	
#define FATAL(x) \
	std::cerr << "ERR::FATAL\t" << (x) << "\n\t\t" \
	<< __FILE__ << "\n\t\tLine " << __LINE__ << "\n"; \
	exit(0);
	
#else

#define ASSERT(x, y) \
	do \
	{ \
	(x); \
	} \
	while (0)

#define DEBUG(x) \
	do \
	{ \
	(x); \
	} \
	while (0)
	
#define FATAL(x) \
	do \
	{ \
	(x); \
	exit(0); \
	} \
	while (0)

#endif