#include "PathTracingSystemComponent.h"
#include <PathTracing/PathTracingTypeIds.h>
#include <AzCore/Serialization/SerializeContext.h>

namespace PathTracing
{
AZ_COMPONENT_IMPL(PathTracingSystemComponent, "PathTracingSystemComponent", PathTracingSystemComponentTypeId);

void PathTracingSystemComponent::Reflect(AZ::ReflectContext* context)
{
  if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
  {
    serializeContext->Class<PathTracingSystemComponent, AZ::Component>()->Version(0);
  }
}

void PathTracingSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
{
  provided.push_back(AZ_CRC_CE("PathTracingService"));
}

void PathTracingSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
{
  incompatible.push_back(AZ_CRC_CE("PathTracingService"));
}

void PathTracingSystemComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& /*required*/) {}

void PathTracingSystemComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& /*dependent*/) {}

PathTracingSystemComponent::PathTracingSystemComponent()
{
  if (PathTracingInterface::Get() == nullptr)
  {
    PathTracingInterface::Register(this);
  }
}

PathTracingSystemComponent::~PathTracingSystemComponent()
{
  if (PathTracingInterface::Get() == this)
  {
    PathTracingInterface::Unregister(this);
  }
}

void PathTracingSystemComponent::Init() {}

void PathTracingSystemComponent::Activate()
{
  PathTracingRequestBus::Handler::BusConnect();
  AZ::TickBus::Handler::BusConnect();
}

void PathTracingSystemComponent::Deactivate()
{
  AZ::TickBus::Handler::BusDisconnect();
  PathTracingRequestBus::Handler::BusDisconnect();
}

void PathTracingSystemComponent::OnTick(float /*deltaTime*/, AZ::ScriptTimePoint /*time*/) {}

} // namespace PathTracing
