
#include <PathTracing/PathTracingTypeIds.h>
#include <PathTracingModuleInterface.h>
#include "PathTracingSystemComponent.h"

namespace PathTracing
{
    class PathTracingModule
        : public PathTracingModuleInterface
    {
    public:
        AZ_RTTI(PathTracingModule, PathTracingModuleTypeId, PathTracingModuleInterface);
        AZ_CLASS_ALLOCATOR(PathTracingModule, AZ::SystemAllocator);
    };
}// namespace PathTracing

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), PathTracing::PathTracingModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_PathTracing, PathTracing::PathTracingModule)
#endif
