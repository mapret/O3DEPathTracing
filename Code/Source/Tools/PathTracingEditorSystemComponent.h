#pragma once

#include "Clients/PathTracingSystemComponent.h"
#include <AzToolsFramework/API/ToolsApplicationAPI.h>

namespace PathTracing
{
/// System component for PathTracing editor
class PathTracingEditorSystemComponent
  : public PathTracingSystemComponent
  , protected AzToolsFramework::EditorEvents::Bus::Handler
{
  using BaseSystemComponent = PathTracingSystemComponent;

public:
  AZ_COMPONENT_DECL(PathTracingEditorSystemComponent);

  static void Reflect(AZ::ReflectContext* context);

  PathTracingEditorSystemComponent();
  ~PathTracingEditorSystemComponent();

private:
  static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
  static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
  static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
  static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

  // AZ::Component
  void Activate() override;
  void Deactivate() override;
};
} // namespace PathTracing
