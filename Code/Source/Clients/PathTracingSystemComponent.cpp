#include "PathTracingSystemComponent.h"
#include "PathTracingFeatureProcessor.h"
#include <PathTracing/PathTracingTypeIds.h>
#include <Atom/RPI.Public/FeatureProcessorFactory.h>
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

  PathTracingFeatureProcessor::Reflect(context);
}

void PathTracingSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
{
  provided.push_back(AZ_CRC_CE("PathTracingService"));
}

void PathTracingSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
{
  incompatible.push_back(AZ_CRC_CE("PathTracingService"));
}

void PathTracingSystemComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
{
  required.push_back(AZ_CRC_CE("RPISystem"));
}

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

  AZ::RPI::FeatureProcessorFactory::Get()->RegisterFeatureProcessor<PathTracingFeatureProcessor>();

  auto* passSystem{ AZ::RPI::PassSystemInterface::Get() };
  AZ_Assert(passSystem, "PathTracing Gem - cannot get the pass system.");
  m_loadTemplatesHandler =
    AZ::RPI::PassSystemInterface::OnReadyLoadTemplatesEvent::Handler([this]() { this->LoadPassTemplateMappings(); });
  passSystem->ConnectEvent(m_loadTemplatesHandler);
}

void PathTracingSystemComponent::Deactivate()
{
  AZ::RPI::FeatureProcessorFactory::Get()->UnregisterFeatureProcessor<PathTracingFeatureProcessor>();

  AZ::TickBus::Handler::BusDisconnect();
  PathTracingRequestBus::Handler::BusDisconnect();
}

void PathTracingSystemComponent::OnTick(float /*deltaTime*/, AZ::ScriptTimePoint /*time*/) {}

void PathTracingSystemComponent::LoadPassTemplateMappings()
{
  auto* passSystem{ AZ::RPI::PassSystemInterface::Get() };
  AZ_Assert(passSystem, "PathTracing Gem - cannot get the pass system.");

  constexpr const char* passTemplatesFile{ "Passes/PathTracingPassTemplates.azasset" };
  passSystem->LoadPassTemplateMappings(passTemplatesFile);
}
} // namespace PathTracing
