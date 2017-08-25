FROM ubuntu:16.04

RUN apt-get update && apt-get -y upgrade && apt-get -y install libssl-dev cmake build-essential libhwloc-dev

COPY src /app
RUN cd /app && cmake -DMICROHTTPD_ENABLE=OFF . && make install

ENV PATH /app/bin:$PATH
WORKDIR /app/bin
ENTRYPOINT ["xmr-stak-cpu"]
