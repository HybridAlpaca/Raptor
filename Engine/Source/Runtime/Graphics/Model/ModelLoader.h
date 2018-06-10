#pragma once

namespace Graphics::Model
{

class Model
{

public:

	Model ();
	Model (const Model & copy) = delete;
	~Model ();

	Model & operator= (const Model & rhs) = delete;
};

}
