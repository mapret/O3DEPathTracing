#include "PathTracingPass.h"

#include <Atom/RPI.Public/Image/AttachmentImagePool.h>
#include <Atom/RPI.Public/Image/ImageSystemInterface.h>

namespace PathTracing
{
AZ::RPI::Ptr<PathTracingPass> PathTracingPass::Create(const AZ::RPI::PassDescriptor& descriptor)
{
  return aznew PathTracingPass{ descriptor };
}

PathTracingPass::PathTracingPass(const AZ::RPI::PassDescriptor& descriptor)
  : AZ::Render::RayTracingPass{ descriptor }
{
}

void PathTracingPass::BuildInternal()
{
  const auto& outputBinding{ GetInputOutputBinding(0) }; // "ColorInputOutput" attachment
  const auto& outputAttachment{ outputBinding.GetAttachment() };
  AZ_Assert(outputAttachment, "PathTracing Gem - PathTracingPass has no inout attachment");

  const auto& imageDescriptor{ outputAttachment->m_descriptor.m_image };
  auto imagePool{ AZ::RPI::ImageSystemInterface::Get()->GetSystemAttachmentPool() };

  AZ::RPI::CreateAttachmentImageRequest createRequest;
  createRequest.m_imageName = AZ::Name{ "Accumulation image" };
  createRequest.m_isUniqueName = false;
  createRequest.m_imagePool = imagePool.get();
  createRequest.m_imageDescriptor = AZ::RHI::ImageDescriptor::Create2D(AZ::RHI::ImageBindFlags::ShaderReadWrite,
                                                                       imageDescriptor.m_size.m_width,
                                                                       imageDescriptor.m_size.m_height,
                                                                       AZ::RHI::Format::R16G16B16A16_FLOAT);
  auto accumulationImage{ AZ::RPI::AttachmentImage::Create(createRequest) };
  AttachImageToSlot(AZ::Name{ "AccumulationImage" }, accumulationImage);
}
} // namespace PathTracing
