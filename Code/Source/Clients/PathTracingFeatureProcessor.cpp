#include "PathTracingFeatureProcessor.h"
#include <AzCore/Serialization/SerializeContext.h>

namespace PathTracing
{
void PathTracingFeatureProcessor::Reflect(AZ::ReflectContext* context)
{
  if (auto* serializeContext{ azrtti_cast<AZ::SerializeContext*>(context) })
  {
    serializeContext->Class<PathTracingFeatureProcessor, AZ::RPI::FeatureProcessor>()->Version(0);
  }
}

void PathTracingFeatureProcessor::Activate()
{
  FeatureProcessor::Activate();
  EnableSceneNotification();
}

void PathTracingFeatureProcessor::Deactivate()
{
  DisableSceneNotification();
  FeatureProcessor::Deactivate();
}

void PathTracingFeatureProcessor::AddRenderPasses(AZ::RPI::RenderPipeline* pipeline)
{
  m_pipeline = pipeline;
}

// void PathTracingFeatureProcessor::Render(const RenderPacket& packet) {}

void PathTracingFeatureProcessor::OnPathTracingComponentAdded()
{
  if (m_componentCount == 0)
  {
    AddPathTracingPasses();
  }
  m_componentCount++;
}

void PathTracingFeatureProcessor::OnPathTracingComponentRemoved()
{
  m_componentCount--;
  if (m_componentCount == 0)
  {
    RemovePathTracingPasses();
  }
}

void PathTracingFeatureProcessor::AddPathTracingPasses()
{
  // TODO: Disable all not needed passes

  m_pathTracingPass = AZ::RPI::PassSystemInterface::Get()->CreatePassFromTemplate(AZ::Name{ "PathTracingPassTemplate" },
                                                                                  AZ::Name{ "PathTracingPass" });
  AZ_Assert(m_pathTracingPass, "PathTracing Gem - cannot create PathTracing pass.");

  m_pipeline->AddPassAfter(m_pathTracingPass, AZ::Name{ "AuxGeomPass" });
}

void PathTracingFeatureProcessor::RemovePathTracingPasses()
{
  if (m_pathTracingPass)
  {
    m_pathTracingPass->QueueForRemoval();
    m_pathTracingPass.reset();
  }

  // TODO: Enable all disabled passes from AddPathTracingPasses
}
} // namespace PathTracing
