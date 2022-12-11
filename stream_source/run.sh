#!/bin/bash

cd stream_source
# -P regulate plugin to ensure that the data are not sent faster than the playout speed.
tsp -v -I file --infinite mux1rai.ts  -P regulate -O ip 224.0.0.251:45000
# analyse
# tsanalyze mux1rai.ts
