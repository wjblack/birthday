FROM ubuntu

RUN apt-get update && \
    apt-get upgrade -y && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    curl \
    wget \
    git \
    python \
    python-pip \
    picocom \
    gcc-avr \
    xz-utils \
    avr-libc && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    find /var/lib/apt -name *.deb -exec rm \{\} \;

VOLUME /src
WORKDIR /src

RUN /bin/bash -c 'curl https://downloads.arduino.cc/arduino-1.8.5-linux64.tar.xz | tar -C /usr/local -Jxv'
RUN /usr/local/arduino-1.8.5/arduino --pref boardsmanager.additional.urls=http://digistump.com/package_digistump_index.json --save-prefs
RUN /usr/local/arduino-1.8.5/arduino --install-boards digistump:avr
