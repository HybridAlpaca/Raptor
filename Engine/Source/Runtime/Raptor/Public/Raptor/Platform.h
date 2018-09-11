#pragma once

#	if __GNUC__
#		define RPTR_ENV_GNU
#		if __x86_64__ || __ppc64__
#			define RPTR_ENV_64
#		else
#			define RPTR_ENV_32
#		endif
#	endif
