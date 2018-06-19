UID := $(shell id -u)
GID := $(shell id -g)

DOCKER := docker run -v `pwd`:/src -w /src -it birthday-build

all:
	$(DOCKER) make birthday.hex

docker:
	docker build -t birthday-build .

birthday.hex:	birthday.ino
	mkdir -p build
	/usr/local/arduino-1.8.5/arduino --board digistump:avr:digispark-tiny --verify $< --pref build.path=build
	chown -R $(UID):$(GID) build
	mv build/$<.hex $@

clean:
	$(DOCKER) rm -rf *.hex build
