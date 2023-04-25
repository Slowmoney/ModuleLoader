#pragma once
#include "Resource.h"
namespace alt {
	class DlcResource : public Resource
	{
		DlcResource(alt::ICore*core, alt::IResource::CreationInfo info, std::string path): Resource(core, info, path){}
	};
}


