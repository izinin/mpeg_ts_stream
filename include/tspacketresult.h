#ifndef MPEGTEST_TSPACKETRESULT_H
#define MPEGTEST_TSPACKETRESULT_H

#include "tsduck.h"

class TSpacketResult
{
private:
    long pcrCounter;
    long videoCounter;
    ts::Report& _report;
public:
    TSpacketResult(ts::PID progId, ts::Report& report);
    ~TSpacketResult();

    const ts::PID progId;

    inline long getPCRCounter(){ return pcrCounter;} 
    inline long getVideoCounter(){ return videoCounter;}
    void incrPcrCounter();
    void incrVideoCounter();
    void report();
};

#endif
