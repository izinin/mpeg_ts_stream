#include <iostream>
#include <vector>
#include <string>
#include <functional>

#include "tsduck.h"
#include "outputhandler.h"

using namespace std;

void* startTestStream(void *ptr){
    FILE *pipe = popen("tsp -I file ${STREAM_PATH}/mux1rai.ts  -P regulate -O ip 224.0.0.251:45000", "r");
    if(pipe != NULL){
        pclose(pipe);
    }
    return NULL;
}

// Enforce COM and network init on Windows, transparent elsewhere.
TS_MAIN(TSApp);

int TSApp(int argc, char* argv[])
{
    struct sigaction sigIntHandler;

#ifdef USELOCALSTREAM    
    pthread_t thread;
    int ret = pthread_create( &thread, NULL, startTestStream, NULL);
    pthread_join( thread, NULL);
#endif
    // Use an asynchronous logger to report errors, logs, debug, etc.
    ts::AsyncReport report;
    OutputHandler output(report);

    __sighandler_t handler = &OutputHandler::userInterruptHandler;
    sigIntHandler.sa_handler = handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    ts::TSProcessor tsproc(report);
    tsproc.registerEventHandler(&output, ts::PluginType::OUTPUT);

    // Build tsp options. Accept most default values, except a few ones.
    ts::TSProcessorArgs opt;
    opt.app_name = u"mpegtest";  // for error messages only.

    // Input plugin. Here, read an IP multicast stream. 
    // HowTo find IP multicast adresses on Windows 10 machine: 
    // CMD > netsh interface ip show joins
    opt.input = {u"ip", {u"224.0.0.251:45000"}};

    opt.plugins = {
        {u"pes", {u"-v"}},
    };

    // Memory (output) plugin sends TS packets to the calling application using memory buffers. 
    // This is only way to make hook in the processing pipeline
    opt.output = {u"memory", {}};

    // Start the TS processing.
    if (!tsproc.start(opt)) {
        return EXIT_FAILURE;
    }

    report.info(u"\t\t.. running please ctrl+c to stop and see the report", {});

    // And wait for TS processing termination.
    tsproc.waitForTermination();
    return EXIT_SUCCESS;
}
