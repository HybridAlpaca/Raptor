#pragma once

#include "PluginsApi.h"

#include <Graphics/EngineApi.h>

#include <iostream>

namespace Core
{
	void * GetEngineApi (EngineApi api, uint32 version)
	{
		switch (api)
		{
			case EngineApi::GRAPHICS:
			{
				if (version == 0)
				{
					static Graphics::Api::v0 api;
					return & api;
				}

				// If an improper version is given, return a null API
				return nullptr;
			}
		}

		// We didn't recognize the API requested, so return a null API
		return nullptr;
	}
}
