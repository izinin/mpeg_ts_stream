#ifndef MPEGTEST_OUTPUTHANDLER_H
#define MPEGTEST_OUTPUTHANDLER_H

#include "tsduck.h"
#include "tspacketresult.h"

//----------------------------------------------------------------------------
// An event handler for memory output plugin.
// It is invoked by the "memory" output plugin each time TS packets are sent.
//----------------------------------------------------------------------------

class OutputHandler : public ts::PluginEventHandlerInterface
{
public:
    // Constructors.
    OutputHandler() = delete; // prohibit copy constructor C++11
    OutputHandler(ts::Report& report);
    ~OutputHandler();

    // Event handling (from ts::PluginEventHandlerInterface).
    virtual void handlePluginEvent(const ts::PluginEventContext& context) override;
    static void userInterruptHandler(int signal);
private:
    ts::Report& _report;
    static std::vector<TSpacketResult*> resultCounter;
};

#endif
