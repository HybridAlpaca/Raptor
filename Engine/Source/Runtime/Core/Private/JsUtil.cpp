#include <JsUtil.h>

#include <v8.h>

#include <iostream>

namespace Core::JS
{

	void ExecuteString (v8::Handle<v8::Context> context, cchar code, cchar title)
	{
		v8::Locker locker;
		v8::HandleScope handleScope;

		v8::Handle<v8::String> source = v8::String::New(code);

		v8::TryCatch tryCatch;

		v8::Context::Scope contextScope(context);

		v8::Handle<v8::Script> script = v8::Script::Compile(source, v8::String::New(title));

		v8::Handle<v8::Value> result = script -> Run();

		if (result.IsEmpty())
		{
			// Something fucked up bigtime
		}
		else if ((!result -> IsUndefined()) && (!result.IsEmpty()))
		{
			v8::String::Utf8Value str(result);

			std::cout << (* str) << "\n";
		}
	}
}
