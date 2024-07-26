#pragma once

#include <RayTracing/RayTracingPass.h>

namespace PathTracing
{
class PathTracingPass : public AZ::Render::RayTracingPass
{
  AZ_RPI_PASS(PathTracingPass);

public:
  AZ_RTTI(PathTracingPass, "{DF80E764-DE31-4B22-B87E-6470E1E74C34}", AZ::Render::RayTracingPass);
  AZ_CLASS_ALLOCATOR(PathTracingPass, AZ::SystemAllocator);

  static AZ::RPI::Ptr<PathTracingPass> Create(const AZ::RPI::PassDescriptor& descriptor);

protected:
  PathTracingPass(const AZ::RPI::PassDescriptor& descriptor);

  // AZ::RPI::Pass overrides
  void BuildInternal() override;
};
} // namespace PathTracing
