#pragma once

#include <Raptor/Required.h>

#include <v8.h>

namespace Core::JS
{
	void ExecuteString (v8::Handle<v8::Context> context, cchar code, cchar title);
}
