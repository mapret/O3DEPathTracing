#include "PathTracingEditorComponent.h"
#include "Clients/PathTracingFeatureProcessor.h"
#include <Atom/RPI.Public/Scene.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/SerializeContext.h>

namespace PathTracing
{
void PathTracingEditorComponent::Reflect(AZ::ReflectContext* reflectContext)
{
  // BaseClass::Reflect(reflectContext);

  if (auto* serializeContext{ azrtti_cast<AZ::SerializeContext*>(reflectContext) })
  {
    serializeContext->Class<PathTracingEditorComponent, BaseClass>()->Version(0);

    if (auto* editContext{ serializeContext->GetEditContext() })
    {
      // clang-format off
      editContext->Class<PathTracingEditorComponent>("Path Tracing", "Controls for path tracing.")
        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
          ->Attribute(AZ::Edit::Attributes::Category, "Graphics/Lighting")
          ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
          ->Attribute(AZ::Edit::Attributes::ViewportIcon, "Icons/Components/Viewport/Component_Placeholder.svg")
          ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Level"))
          ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
      ;
      // clang-format on
    }
  }
}

void PathTracingEditorComponent::Activate()
{
  BaseClass::Activate();

  auto fp{ AZ::RPI::Scene::GetFeatureProcessorForEntity<PathTracingFeatureProcessor>(GetEntityId()) };
  if (fp)
  {
    fp->OnPathTracingComponentAdded();
  }
}

void PathTracingEditorComponent::Deactivate()
{
  auto fp{ AZ::RPI::Scene::GetFeatureProcessorForEntity<PathTracingFeatureProcessor>(GetEntityId()) };
  if (fp)
  {
    fp->OnPathTracingComponentRemoved();
  }

  BaseClass::Deactivate();
}
} // namespace PathTracing
