#pragma once

#include <Atom/Feature/RayTracing/RayTracingPass.h>

namespace PathTracing
{
class PathTracingPass : public AZ::Render::RayTracingPass
{
  AZ_RPI_PASS(PathTracingPass);
  using BaseClass = AZ::Render::RayTracingPass;

public:
  AZ_RTTI(PathTracingPass, "{DF80E764-DE31-4B22-B87E-6470E1E74C34}", BaseClass);
  AZ_CLASS_ALLOCATOR(PathTracingPass, AZ::SystemAllocator);

  static AZ::RPI::Ptr<PathTracingPass> Create(const AZ::RPI::PassDescriptor& descriptor);

protected:
  PathTracingPass(const AZ::RPI::PassDescriptor& descriptor);

  // AZ::RPI::Pass overrides
  void BuildInternal() override;
  void FrameBeginInternal(FramePrepareParams params) override;

private:
  unsigned m_frameCount{ 0 };
  AZ::RHI::ShaderInputNameIndex m_configNameIndex{ "m_reflectionMethod" }; // Need to reuse existing SRG member
  AZ::Data::Instance<AZ::RPI::Buffer> m_configBuffer;
  AZ::RHI::Ptr<AZ::RHI::DeviceBufferView> m_configBufferView;
  AZ::Transform m_previousCameraTransform;
  AZ::RPI::Buffer* m_previousMaterialBuffer{ nullptr };
};
} // namespace PathTracing
