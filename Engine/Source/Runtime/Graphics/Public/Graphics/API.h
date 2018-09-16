#pragma once

class GraphicsAPI
{

public:

	virtual ~GraphicsAPI () {}

	virtual void Clear () = 0;
	virtual void DrawIndexed () = 0;
};

struct Plugin
{
	virtual ~Plugin () {}

	virtual void Execute (GraphicsAPI * api) = 0;
};

typedef Plugin * (Create_T)();

typedef void Destroy_T (Plugin *);
