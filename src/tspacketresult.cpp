#include "tspacketresult.h"
#include <numeric>
#include <vector>

double average(std::vector<double> const& v);

TSpacketResult::TSpacketResult(ts::PID progId, ts::Report& report):
    progId(progId),
    _report(report),
    pcrCounter(0),
    videoCounter(0),
    packetCounter(0),
    pcrValBegin(0),
    pcrValEnd(0)
{
}

TSpacketResult::~TSpacketResult()
{
}

void TSpacketResult::bitrateCollectData(bool hasPCR, uint64_t pcrVal)
{
    if(!hasPCR || pcrVal == 0){
        packetCounter++;
        return; 
    } else if(pcrValBegin == 0){
        pcrValBegin = pcrVal;
        packetCounter = 0;
        pcrValEnd = 0;
    } else if(pcrValEnd == 0){
        pcrValEnd = pcrVal;
        calculateBitrate();
        resetPcr();
    }
    pcrCounter++;
}

void TSpacketResult::incrVideoCounter()
{
    videoCounter++;
}

void TSpacketResult::report(){
    if(bitRateMeasurements.empty()){
        _report.info(u"\tPID: 0x%X, PCR packets count %d, Bitrate: undefined", {progId, pcrCounter, videoCounter});
        return;
    }
    double bitrate = average(bitRateMeasurements) / 1.e6;
    _report.info(u"\tPID: 0x%X, PCR packets count %d, Video packets count: %d, Bitrate: %10.2f Mbits/second", {progId, pcrCounter, videoCounter, bitrate});
}

void TSpacketResult::calculateBitrate(){
    double delta = pcrValEnd - pcrValBegin;
    if(delta <= 0.) {
        _report.error(u"invalid PCR pair for PID: %d, end=%f , begin=%f, packets in between=%d", {progId, pcrValEnd, pcrValBegin, packetCounter});
    }
    double deltaTime = delta / 90000.;
    double deltaBits = packetCounter * 188 * 8;
    double bitrate =  deltaBits / deltaTime;
    bitRateMeasurements.push_back(bitrate);
}


double average(std::vector<double> const& v){
    if(v.empty()){
        return 0;
    }

    auto count = v.size();
    double result = 0;
    for (double el : v)
    {
        result += el;
    }
    return result / count;
}
