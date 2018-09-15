#include <JsUtil.h>

#include <v8.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace Core::JS
{

	v8::Handle<v8::Value> ExecuteString (v8::Handle<v8::Context> context, v8::Handle<v8::String> code, cchar title)
	{
		v8::Locker locker;
		v8::HandleScope handleScope;

		v8::Handle<v8::String> source = code;

		v8::Context::Scope contextScope(context);

		v8::Handle<v8::Script> script = v8::Script::Compile(source, v8::String::New(title));

		v8::Handle<v8::Value> result = script -> Run();

		return result;
	}

	v8::Handle<v8::String> ReadFile (cchar filename)
	{
		v8::HandleScope scope;

		std::ifstream stream(filename);
		std::stringstream buffer;
		buffer << stream.rdbuf();

		v8::Handle<v8::String> value = v8::String::New(buffer.str().c_str());

		return scope.Close(value);
	}
}
