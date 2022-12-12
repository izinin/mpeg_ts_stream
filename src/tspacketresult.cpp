#include "tspacketresult.h"

TSpacketResult::TSpacketResult(ts::PID progId, ts::Report& report):
    progId(progId),
    _report(report),
    pcrCounter(0),
    videoCounter(0)
{
}

TSpacketResult::~TSpacketResult()
{
}

void TSpacketResult::incrPcrCounter()
{
    pcrCounter++;
}

void TSpacketResult::incrVideoCounter()
{
    videoCounter++;
}

void TSpacketResult::report(){
    _report.info(u"\tPID: %d, PCR packets count %d, Video packets count: %d", {progId, pcrCounter, videoCounter});
}