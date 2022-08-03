FROM centos7-for-btpd:latest

WORKDIR /btpd
ADD btpd .
ADD config config

RUN ls -la

#RUN cd build && make -j`nproc`
#RUN mkdir -p /storage/btp && mkdir -p /logs

#EXPOSE 37000 37001 37002 37003 37004 38001 38001/udp
#ENTRYPOINT ["/btpd/build/Release/btpd", "-C", "/btpd/config/btpd.conf", "2>&1"]

