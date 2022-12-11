# mpeg_ts_stream
This is for experiments with mpeg-ts

### installing build tools
```shell
sudo apt-get update
sudo apt-get install build-essential gdb
sudo apt install autoconf
```

## installing ts_duck

### building from source code
```shell
mkdir ts_duck
cd ts_duck/
git clone https://github.com/tsduck/tsduck.git
cd tsduck
./scripts/install-prerequisites.sh
# NOTEST : Do not build unitary tests.
# NODTAPI : No Dektec support, remove dependency to DTAPI.
# NOCURL : No HTTP support, remove dependency to libcurl.
# NOPCSC : No smartcard support, remove dependency to pcsc-lite.
# NOSRT : No SRT (Secure Reliable Transport), remove dependency to libsrt.
# NOTELETEXT : No Teletext support, remove teletext handling code.
make -j10 NOTEST=1 NOCURL=1 NODTAPI=1 NOPCSC=1 NOSRT=1
sudo make NOTEST=1 NOCURL=1 NODTAPI=1 NOPCSC=1 NOSRT=1 install
```
### instaling dev env
```shell
wget https://github.com/tsduck/tsduck/releases/download/v3.32-2983/tsduck_3.32-2983.debian11_amd64.deb
wget https://github.com/tsduck/tsduck/releases/download/v3.32-2983/tsduck-dev_3.32-2983.ubuntu22_amd64.deb
sudo dpkg -i tsduck_3.32-2983.debian11_amd64.deb
sudo dpkg -i tsduck-dev_3.32-2983.ubuntu22_amd64.deb
## to see deb content
dpkg-deb -c tsduck-dev_3.32-2983.ubuntu22_amd64.deb
```

### build

```shell
./autogen.sh
./configure
make
```

### NOTES
* TSDuck uses VERSION typedef this clashes with VERSION macro required by Automake. We need workaroud to not using VERSION in Automake 
* to setup vcode debbuger: `g++ -g -Wall -I/usr/include/tsduck -I/usr/include/PCSC -Ltsduck src/mpegtest.cpp -o test`
* how to find IP multicast adresses in Windows : `netsh interface ip show joins`
* for tsduck config details use `tsconfig --help`

g++  -g -O2  -o mpegtest mpegtest-mpegtest.o mpegtest-outputhandler.o -ltsduck -lpcsclite -lpthread -lrt -ldl -lm -lstdc++
