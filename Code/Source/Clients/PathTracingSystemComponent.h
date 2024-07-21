#pragma once

#include <PathTracing/PathTracingBus.h>
#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>

namespace PathTracing
{
class PathTracingSystemComponent
  : public AZ::Component
  , protected PathTracingRequestBus::Handler
  , public AZ::TickBus::Handler
{
public:
  AZ_COMPONENT_DECL(PathTracingSystemComponent);

  static void Reflect(AZ::ReflectContext* context);

  static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
  static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
  static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
  static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

  PathTracingSystemComponent();
  ~PathTracingSystemComponent();

protected:
  ////////////////////////////////////////////////////////////////////////
  // PathTracingRequestBus interface implementation

  ////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////
  // AZ::Component interface implementation
  void Init() override;
  void Activate() override;
  void Deactivate() override;
  ////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////
  // AZTickBus interface implementation
  void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
  ////////////////////////////////////////////////////////////////////////
};

} // namespace PathTracing
