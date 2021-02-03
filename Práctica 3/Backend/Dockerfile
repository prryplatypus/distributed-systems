FROM ubuntu:20.04

WORKDIR /application

COPY ./src /application

RUN apt-get update \
    && DEBIAN_FRONTEND="noninteractive" TZ="Europe/Madrid" apt-get install -y \
        software-properties-common \
        python3 \
        python3-dev \
        python3-pip \
        make \
        gcc \
        musl-dev \
        g++ \
    && pip3 install --upgrade pip \
    && pip3 install -r /application/requirements.txt \
    && cp /application/config.py.example /application/config.py

EXPOSE 8080

CMD ["python3", "/application/app.py"]