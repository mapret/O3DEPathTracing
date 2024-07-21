
#include <AzCore/Serialization/SerializeContext.h>
#include "PathTracingEditorSystemComponent.h"

#include <PathTracing/PathTracingTypeIds.h>

namespace PathTracing
{
    AZ_COMPONENT_IMPL(PathTracingEditorSystemComponent, "PathTracingEditorSystemComponent",
        PathTracingEditorSystemComponentTypeId, BaseSystemComponent);

    void PathTracingEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<PathTracingEditorSystemComponent, PathTracingSystemComponent>()
                ->Version(0);
        }
    }

    PathTracingEditorSystemComponent::PathTracingEditorSystemComponent() = default;

    PathTracingEditorSystemComponent::~PathTracingEditorSystemComponent() = default;

    void PathTracingEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("PathTracingEditorService"));
    }

    void PathTracingEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("PathTracingEditorService"));
    }

    void PathTracingEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void PathTracingEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void PathTracingEditorSystemComponent::Activate()
    {
        PathTracingSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void PathTracingEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        PathTracingSystemComponent::Deactivate();
    }

} // namespace PathTracing
