#pragma once

#define DEBUG_BUILD

#ifdef DEBUG_BUILD

#include <iostream>

#define ASSERT(condition, message) \
	if (!(condition)) \
	{ \
		std::cerr << "ERR::ASSERT\t" \
		<< message << "\n\t\t" << __FILE__ << "\n\t\tLine " \
		<< __LINE__ << "\n"; \
		exit(0); \
	}
	
#define DEBUG(message) \
	std::cout << "SYS::DEBUG\t" << message << "\n";
	
#define FATAL(message) \
	std::cerr << "ERR::FATAL\t" << message << "\n\t\t" \
	<< __FILE__ << "\n\t\tLine " << __LINE__ << "\n"; \
	exit(0);
	
#else

#define ASSERT(condition, message) \
	do \
	{ \
	(condition); \
	(message); \
	} \
	while (0)

#define DEBUG(message) \
	do \
	{ \
	(message); \
	} \
	while (0)
	
#define FATAL(message) \
	do \
	{ \
	(message); \
	exit(0); \
	} \
	while (0)

#endif