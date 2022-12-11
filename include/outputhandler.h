#include "tsduck.h"

//----------------------------------------------------------------------------
// An event handler for memory output plugin.
// It is invoked by the "memory" output plugin each time TS packets are sent.
//----------------------------------------------------------------------------

class OutputHandler : public ts::PluginEventHandlerInterface
{
public:
    // Constructors.
    OutputHandler() = delete;
    OutputHandler(ts::Report& report);

    // Event handling (from ts::PluginEventHandlerInterface).
    virtual void handlePluginEvent(const ts::PluginEventContext& context) override;

private:
    ts::Report& _report;
};
