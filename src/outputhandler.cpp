
#include "outputhandler.h"

// Constructor.
OutputHandler::OutputHandler(ts::Report& report) :
    _report(report)
{
}

// This event handler is called each time the memory plugin sends output packets.
void OutputHandler::handlePluginEvent(const ts::PluginEventContext& context)
{
    ts::PluginEventData* data = dynamic_cast<ts::PluginEventData*>(context.pluginData());
    if (data != nullptr) {
        const ts::TSPacket* packets = reinterpret_cast<const ts::TSPacket*>(data->data());
        const size_t packets_count = data->size() / ts::PKT_SIZE;
        _report.info(u"received %d output packets", {packets_count});
        for (size_t i = 0; i < packets_count; ++i) {
            _report.info(u"packet #%d: %s", {i, ts::UString::Dump(packets + i, ts::PKT_SIZE, ts::UString::COMPACT)});
        }
    }
}
