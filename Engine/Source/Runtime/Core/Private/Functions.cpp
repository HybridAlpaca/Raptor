#include <Functions.h>

#include <iostream>

namespace Core::JS
{
	v8::Handle<v8::Value> Print (const v8::Arguments & args)
	{
		v8::Locker locker;
		v8::HandleScope scope;

		if (args.Length())
		{
			v8::String::Utf8Value message(args[0] -> ToString());

			if (message.length())
			{
				//Print the message to stdout
				std::cout << (* message);

				bool newline = true;

				if (args.Length() == 2)
				{
					newline = args[1] -> ToBoolean() -> BooleanValue();
				}

				if (newline) std::cout << std::endl;
			}
		}

		return v8::Undefined();
	}
}
