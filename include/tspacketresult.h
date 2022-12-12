#ifndef MPEGTEST_TSPACKETRESULT_H
#define MPEGTEST_TSPACKETRESULT_H

#include "tsduck.h"

class TSpacketResult
{
private:
    uint64_t pcrCounter;
    uint64_t videoCounter;
    uint64_t packetCounter; // to store amount of packets in beetween of two PCRs in the stream
                            // needed to calculate bitrate:  https://youtu.be/Ng592k1NiRE?t=141
    uint64_t pcrValBegin;
    uint64_t pcrValEnd;
    ts::Report& _report;

    std::vector<double> bitRateMeasurements;

    void calculateBitrate();
    inline void resetPcr(){
        pcrValBegin=pcrValEnd;
        pcrValEnd=0;
    }
public:
    TSpacketResult(ts::PID progId, ts::Report& report);
    ~TSpacketResult();

    const ts::PID progId;

    void bitrateCollectData(bool hasPCR, uint64_t pcrVal);
    void incrVideoCounter();
    void report();
};

#endif
