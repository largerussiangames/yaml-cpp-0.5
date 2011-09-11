#include "yaml-cpp/null.h"

#if YAML_CPP_OLD_API
#include "yaml-cpp/node.h"
#endif

namespace YAML
{
	_Null Null;

#if YAML_CPP_OLD_API
	bool IsNull(const Node& node)
	{
		return node.Read(Null);
	}
#endif
}
