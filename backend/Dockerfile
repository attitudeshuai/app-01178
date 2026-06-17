# 使用 Ubuntu 作为基础镜像
FROM ubuntu:22.04

# 设置工作目录
WORKDIR /app

# 配置阿里云镜像源加速
RUN sed -i 's@http://archive.ubuntu.com@http://mirrors.aliyun.com@g' /etc/apt/sources.list && \
    sed -i 's@http://security.ubuntu.com@http://mirrors.aliyun.com@g' /etc/apt/sources.list && \
    apt-get update && \
    apt-get install -y --no-install-recommends build-essential g++ && \
    rm -rf /var/lib/apt/lists/*


# 复制源代码到容器
COPY main.cpp lcs.h ./

# 编译 C++ 源代码
RUN g++ -o app main.cpp -std=c++11 -O2

# 设置启动命令
CMD ["./app"]
