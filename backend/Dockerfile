FROM ubuntu:22.04

WORKDIR /app

RUN sed -i 's@http://archive.ubuntu.com@http://mirrors.aliyun.com@g' /etc/apt/sources.list && \
    sed -i 's@http://security.ubuntu.com@http://mirrors.aliyun.com@g' /etc/apt/sources.list && \
    apt-get update && \
    apt-get install -y --no-install-recommends build-essential g++ libgtest-dev cmake && \
    rm -rf /var/lib/apt/lists/*

RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp lib/*.a /usr/lib

COPY main.cpp .
COPY lcs_algorithms.h .
COPY string_utils.h .
COPY tests/ ./tests/

RUN g++ -o app main.cpp -std=c++11 -O2

RUN g++ -o tests/lcs_test tests/lcs_test.cpp -std=c++17 -O2 -lgtest -lpthread

CMD ["./app"]
