#include "PathTracingPass.h"
#include <Atom/Feature/RayTracing/RayTracingFeatureProcessorInterface.h>
#include <Atom/RPI.Public/Image/AttachmentImagePool.h>
#include <Atom/RPI.Public/Image/ImageSystemInterface.h>
#include <Atom/RPI.Public/Scene.h>
#include <AzFramework/Components/CameraBus.h>

namespace PathTracing
{
using uint = AZ::u32;
#include "../../Assets/Shaders/PathTracingConfig.azsli"

AZ::RPI::Ptr<PathTracingPass> PathTracingPass::Create(const AZ::RPI::PassDescriptor& descriptor)
{
  return aznew PathTracingPass{ descriptor };
}

PathTracingPass::PathTracingPass(const AZ::RPI::PassDescriptor& descriptor)
  : BaseClass{ descriptor }
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

  AZ::RPI::CommonBufferDescriptor bufferDescriptor;
  bufferDescriptor.m_poolType = AZ::RPI::CommonBufferPoolType::ReadOnly;
  bufferDescriptor.m_bufferName = "PathTracing config buffer";
  bufferDescriptor.m_byteCount = sizeof(PathTracingConfig);
  bufferDescriptor.m_elementSize = sizeof(PathTracingConfig);
  m_configBuffer = AZ::RPI::BufferSystemInterface::Get()->CreateBufferFromCommonPool(bufferDescriptor);
  m_configBufferView = m_configBuffer->GetRHIBuffer()
                         ->GetDeviceBuffer(AZ::RHI::MultiDevice::DefaultDeviceIndex)
                         ->GetBufferView(m_configBuffer->GetBufferViewDescriptor());

  BaseClass::BuildInternal();
}

void PathTracingPass::FrameBeginInternal(FramePrepareParams params)
{
  AZ::Transform cameraTransform;
  Camera::ActiveCameraRequestBus::BroadcastResult(cameraTransform,
                                                  &Camera::ActiveCameraRequestBus::Events::GetActiveCameraTransform);
  bool cameraMoved{ !cameraTransform.IsClose(m_previousCameraTransform) };
  if (cameraMoved)
  {
    m_previousCameraTransform = cameraTransform;
  }

  auto* rayTracingFeatureProcessor{
    GetScene()->GetFeatureProcessor<AZ::Render::RayTracingFeatureProcessorInterface>()
  };
  bool materialChanged{ rayTracingFeatureProcessor &&
                        rayTracingFeatureProcessor->GetMaterialInfoGpuBuffer().get() != m_previousMaterialBuffer };
  if (materialChanged)
  {
    m_previousMaterialBuffer = rayTracingFeatureProcessor->GetMaterialInfoGpuBuffer().get();
  }

  GetShaderResourceGroup()->SetConstant(m_configNameIndex, m_configBufferView->GetBindlessReadIndex());

  PathTracingConfig config;
  config.m_frameCount = m_frameCount++;
  config.m_clearRequest = cameraMoved || materialChanged;
  m_configBuffer->UpdateData(&config, sizeof(PathTracingConfig), 0);

  BaseClass::FrameBeginInternal(params);
}
} // namespace PathTracing
