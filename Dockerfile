FROM debian:11

MAINTAINER Солопов Никита гр. 728-1

COPY ./lab3.cpp .

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install build-essential -y
RUN apt-get install gcc-multilib -y
RUN apt-get install gdb -y
