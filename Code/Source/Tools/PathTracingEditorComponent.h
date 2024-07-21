#pragma once

#include <AzToolsFramework/ToolsComponents/EditorComponentBase.h>

namespace PathTracing
{
class PathTracingEditorComponent : public AzToolsFramework::Components::EditorComponentBase
{
public:
  using BaseClass = AzToolsFramework::Components::EditorComponentBase;
  AZ_EDITOR_COMPONENT(PathTracingEditorComponent, "{CAA6FFC9-BCF7-44CC-8D22-7E9082148D2B}", BaseClass);

  static void Reflect(AZ::ReflectContext* reflectContext);

  // AZ::Component overrides
  void Activate() override;
  void Deactivate() override;
};
} // namespace PathTracing
