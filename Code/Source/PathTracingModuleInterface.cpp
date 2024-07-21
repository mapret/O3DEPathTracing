#include "PathTracingModuleInterface.h"
#include "Clients/PathTracingSystemComponent.h"
#include <PathTracing/PathTracingTypeIds.h>
#include <AzCore/Memory/Memory.h>

namespace PathTracing
{
AZ_TYPE_INFO_WITH_NAME_IMPL(PathTracingModuleInterface, "PathTracingModuleInterface", PathTracingModuleInterfaceTypeId);
AZ_RTTI_NO_TYPE_INFO_IMPL(PathTracingModuleInterface, AZ::Module);
AZ_CLASS_ALLOCATOR_IMPL(PathTracingModuleInterface, AZ::SystemAllocator);

PathTracingModuleInterface::PathTracingModuleInterface()
{
  // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
  // Add ALL components descriptors associated with this gem to m_descriptors.
  // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext
  // and EditContext. This happens through the [MyComponent]::Reflect() function.
  m_descriptors.insert(m_descriptors.end(),
                       {
                         PathTracingSystemComponent::CreateDescriptor(),
                       });
}

AZ::ComponentTypeList PathTracingModuleInterface::GetRequiredSystemComponents() const
{
  return AZ::ComponentTypeList{
    azrtti_typeid<PathTracingSystemComponent>(),
  };
}
} // namespace PathTracing
