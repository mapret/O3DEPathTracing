#pragma once

#include <Atom/RPI.Public/FeatureProcessor.h>
#include <Atom/RPI.Public/Pass/Pass.h>
#include <Atom/RPI.Public/RenderPipeline.h>

namespace PathTracing
{
class PathTracingFeatureProcessor : public AZ::RPI::FeatureProcessor
{
public:
  AZ_CLASS_ALLOCATOR(PathTracingFeatureProcessor, AZ::SystemAllocator)
  AZ_RTTI(PathTracingFeatureProcessor, "{3FADFA82-7BDA-4AF1-B80E-0FBA0065BC70}", AZ::RPI::FeatureProcessor);

  static void Reflect(AZ::ReflectContext* context);

  // AZ::RPI::FeatureProcessor overrides
  void Activate() override;
  void Deactivate() override;
  void AddRenderPasses(AZ::RPI::RenderPipeline* pipeline) override;
  // void Render(const RenderPacket& packet) override;

  // TODO: Create interface for FP?
  void OnPathTracingComponentAdded();
  void OnPathTracingComponentRemoved();

private:
  void AddPathTracingPasses();
  void RemovePathTracingPasses();

  int m_componentCount{ 0 };
  AZ::RPI::RenderPipeline* m_pipeline{ nullptr };
  AZ::RPI::Ptr<AZ::RPI::Pass> m_pathTracingPass;
};
} // namespace PathTracing
