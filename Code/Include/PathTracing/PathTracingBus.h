#pragma once

#include <PathTracing/PathTracingTypeIds.h>
#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace PathTracing
{
class PathTracingRequests
{
public:
  AZ_RTTI(PathTracingRequests, PathTracingRequestsTypeId);
  virtual ~PathTracingRequests() = default;
  // Put your public methods here
};

class PathTracingBusTraits : public AZ::EBusTraits
{
public:
  //////////////////////////////////////////////////////////////////////////
  // EBusTraits overrides
  static constexpr AZ::EBusHandlerPolicy HandlerPolicy{ AZ::EBusHandlerPolicy::Single };
  static constexpr AZ::EBusAddressPolicy AddressPolicy{ AZ::EBusAddressPolicy::Single };
  //////////////////////////////////////////////////////////////////////////
};

using PathTracingRequestBus = AZ::EBus<PathTracingRequests, PathTracingBusTraits>;
using PathTracingInterface = AZ::Interface<PathTracingRequests>;

} // namespace PathTracing
