FROM ubuntu:20.04

WORKDIR /application

RUN apt-get update \
    && apt-get install -y software-properties-common

COPY server /application

EXPOSE 80

CMD ["./server"]
