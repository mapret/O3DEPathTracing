
#pragma once

namespace PathTracing
{
    // System Component TypeIds
    inline constexpr const char* PathTracingSystemComponentTypeId = "{13F0B14B-5F0D-4DAE-8FBD-63A8BA0FB374}";
    inline constexpr const char* PathTracingEditorSystemComponentTypeId = "{2D0E9833-6F9C-4CF3-9B04-32C7EF6AECDD}";

    // Module derived classes TypeIds
    inline constexpr const char* PathTracingModuleInterfaceTypeId = "{29D07FD8-924B-4B30-A414-0A25C7DA11C4}";
    inline constexpr const char* PathTracingModuleTypeId = "{D0A319E2-97AC-4AE1-8C32-BCFA4F3D1C68}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* PathTracingEditorModuleTypeId = PathTracingModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* PathTracingRequestsTypeId = "{D6F9879D-CC57-47ED-A7A8-8DD0C3A782AB}";
} // namespace PathTracing
