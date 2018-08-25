#pragma once

namespace Graphics
{

class ResourceContext
{

public:

	ResourceContext ();

	/// Temporarily non-copyable
	ResourceContext (const ResourceContext & copy) = delete;

	~ResourceContext ();

	/// Temporarily non-copyable
	ResourceContext & operator= (const ResourceContext & rhs) = delete;
};

}
