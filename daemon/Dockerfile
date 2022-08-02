FROM centos:7

RUN yum install -y \
  wget \
  gcc-c++ \
  snappy snappy-devel \
  zlib zlib-devel \
  bzip2 bzip2-devel \
  lz4-devel \
  libasan \
  gflags \
  boost-devel \
  make \
  cmake \
  git \
  which

WORKDIR /btpd
ADD btpd .
RUN git clone https://github.com/facebook/rocksdb.git facebook-rocksdb
ADD config config
RUN cd build && make -j`nproc`
RUN mkdir -p /storage/btp && mkdir -p /logs

EXPOSE 37000 37001 37002 37003 37004 38001 38001/udp
ENTRYPOINT ["/btpd/build/Release/btpd", "-C", "/btpd/config/btpd.conf", "2>&1"]

