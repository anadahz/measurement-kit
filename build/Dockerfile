FROM multiarch/debian-debootstrap:armel-jessie
RUN apt update
RUN apt-get install -qqy libssl-dev dh-autoreconf libevent-dev llvm clang git wget gzip libgeoip-dev
RUN git clone https://github.com/measurement-kit/measurement-kit
WORKDIR measurement-kit
RUN ./autogen.sh &&\
    ./configure &&\
    make &&\
    make install &&\
    /sbin/ldconfig
RUN make check
