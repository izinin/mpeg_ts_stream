#!/bin/bash
# replay as udp stream (-P regulate)
tsp -I file --infinite mux1rai.ts -P pes -O ip 127.0.0.1:4904
# analyse
tsanalyze mux1rai.ts
