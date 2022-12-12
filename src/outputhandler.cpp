
#include "outputhandler.h"

using namespace ts;
using namespace std;

vector<TSpacketResult*> OutputHandler::resultCounter;

OutputHandler::OutputHandler(Report& report) :
    _report(report)
{
}

OutputHandler::~OutputHandler()
{
    for (auto p : resultCounter) {
        delete p;
    }
    resultCounter.clear();
}

void OutputHandler::userInterruptHandler(int s){
    if(s == SIGINT){
        std::sort(resultCounter.begin(), resultCounter.end(), [](TSpacketResult* a, TSpacketResult* b)
            { return (a->progId < b->progId);});
        for (auto p : resultCounter)
        {
            p->report();
        }
        exit(1); 
    }
}

// This event handler is called each time the memory plugin sends output packets.
void OutputHandler::handlePluginEvent(const PluginEventContext& context)
{
    PluginEventData* data = dynamic_cast<PluginEventData*>(context.pluginData());
    if (data == nullptr) {
        return;
    }
    const TSPacket* packets = reinterpret_cast<const TSPacket*>(data->data());
    const size_t packets_count = data->size() / PKT_SIZE;
    
    vector<TSPacket> v;
    v.assign(packets, packets + packets_count);
    for (TSPacket p : v){
        PID currPid = p.getPID();
        if(currPid == 0 || currPid == 1) {
            // skip PSI tables or Conditional Access Table (CAT)
            continue;
        }

        auto found = std::find_if(resultCounter.begin(), resultCounter.end(),[&currPid](TSpacketResult* x)
            { return x->progId == currPid; });
        TSpacketResult* item = NULL;
        if(found == resultCounter.end()){
            item = new TSpacketResult(currPid, _report);
            resultCounter.push_back(item);
        } else {
            item = found[0];
        }
        if(p.hasPCR()){
            item->incrPcrCounter();
        }
        // ostringstream oss;
        // p.display(oss, TSPacket::DUMP_PES_HEADER);
        // _report.info(u"PES_HEADER %s", {oss.str()});
        //_report.info(u"packet %s", {UString::Dump(&p, PKT_SIZE, UString::COMPACT)});
    }
}
