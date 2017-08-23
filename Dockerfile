FROM ubuntu:16.04

RUN apt-get update && apt-get -y upgrade && apt-get -y install libssl-dev cmake build-essential libhwloc-dev

COPY src /opt/xmon
RUN cd /opt/xmon && cmake -DMICROHTTPD_ENABLE=OFF -DCMAKE_LINK_STATIC=ON . && make install

WORKDIR /opt/xmon/bin
ENTRYPOINT ["/opt/xmon/bin/xmr-stak-cpu"]
