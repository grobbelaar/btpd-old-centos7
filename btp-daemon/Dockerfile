FROM centos:7 AS builder

RUN yum install -y \
  wget \
  gcc-c++ \
  snappy snappy-devel \
  zlib zlib-devel \
  bzip2 bzip2-devel \
  lz4-devel \
  libasan \
  gflags \
  boost boost-devel boost-system boost-datetime \
  jemalloc jemalloc-devel \
  libzstd libzstd-devel \
  librt librt-devel \
  make \
  cmake \
  git \
  which

WORKDIR /usr/src/btpd
ADD btpd .
RUN ls -la /usr/src/btpd

RUN cd build && cmake .. && make -j`nproc`
RUN mkdir -p /storage/btp && mkdir -p /logs

RUN find /usr/src/btpd/build/Release/btpd -exec ldd {} \; | grep so | sed -e '/^[^\t]/ d' | sed -e 's/\t//' | sed -e 's/.*=..//' | sed -e 's/ (0.*)//' | sort |uniq
RUN ls /usr/src/btpd/facebook-rocksdb/librocksdb.so.* /lib64/libboost_*.so.* /lib64/libsnappy.so.*

FROM centos:7

RUN yum -y install boost boost-system boost-datetime snappy && yum clean all

WORKDIR /btpd
COPY config /btpd
COPY --from=builder /usr/src/btpd/build/Release /btpd
COPY --from=builder /usr/src/btpd/facebook-rocksdb/librocksdb.so.* /btpd/lib/

ENV LD_LIBRARY_PATH=/btpd/lib

EXPOSE 37000 37001 37002 37003 37004 38001 38001/udp
ENTRYPOINT ["/btpd/btpd", "2>&1"]


