#pragma once

#include <v8.h>

namespace Core::JS
{
	v8::Handle<v8::Value> Print (const v8::Arguments & args);
}
