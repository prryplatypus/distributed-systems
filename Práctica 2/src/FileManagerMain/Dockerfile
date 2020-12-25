FROM ubuntu:20.04

WORKDIR /application

RUN apt-get update \
    && apt-get install -y software-properties-common

COPY fmmain_server ./
COPY dirprueba ./

EXPOSE 8081

CMD ["./fmmain_server"]