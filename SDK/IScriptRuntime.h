#pragma once
#include "IResource.h"

#include <cstdint>
#include <functional>

namespace core
{
	class IScriptRuntime
	{
	public:
		virtual ~IScriptRuntime() = default;

		virtual bool RequiresMain() const { return true; }
		
		virtual IResource::Impl* CreateImpl(IResource* resource) = 0;
		virtual void DestroyImpl(IResource::Impl* impl) = 0;
		
		virtual void OnTick() { };
		virtual void OnDispose() { };
	};
}

