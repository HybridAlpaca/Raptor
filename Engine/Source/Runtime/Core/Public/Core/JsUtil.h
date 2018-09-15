#pragma once

#include <Raptor/Required.h>

#include <v8.h>

namespace Core::JS
{
	v8::Handle<v8::Value> ExecuteString (v8::Handle<v8::Context> context, v8::Handle<v8::String>, cchar title);

	v8::Handle<v8::String> ReadFile (cchar filename);
}
