FROM ubuntu:20.04

WORKDIR /application

RUN apt-get update \
    && apt-get install -y software-properties-common

COPY mmmain_server ./

EXPOSE 8081

CMD ["./mmmain_server"]