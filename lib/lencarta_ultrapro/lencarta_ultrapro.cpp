#include "lencarta_ultrapro.h"


void lencarta_ultrapro::begin(void) {
	radio.begin();
	radio.setDataRate(RF24_250KBPS);
	radio.setChannel(0x23);
	radio.setAutoAck(true);
	radio.setPayloadSize(10);
	radio.openReadingPipe(0,baseAddress);

}

bool lencarta_ultrapro::fireFlash(uint8_t * address) {
	return fireFlash(address[0], address[1]);
}

bool lencarta_ultrapro::fireFlash(uint8_t id, uint8_t group) {
	uint8_t payload[10];
	payload[0] = 0x01;
	return sendPacket(id, group, payload);
}

bool lencarta_ultrapro::sendPacket(uint8_t id, uint8_t group, uint8_t * payload) {

	bool ack = false;
	radio.setChannel(baseChannel + group);
	radio.stopListening();
	radio.openWritingPipe(baseAddress + id);
	ack = radio.write(payload, 10);
	radio.startListening();
	return ack;
}

bool lencarta_ultrapro::flashPower(uint8_t * address, uint8_t power) {
	return flashPower(address[0], address[1], power);
}

bool lencarta_ultrapro::flashPower(uint8_t id, uint8_t group, uint8_t power) {
	uint8_t payload[10];
	payload[0] = 0x06;
	payload[1] = power;
	return sendPacket(id, group, payload);
}

bool lencarta_ultrapro::slaveMode(uint8_t * address, bool state) {
	return slaveMode(address[0], address[1], state);
}

bool lencarta_ultrapro::slaveMode(uint8_t id, uint8_t group, bool state) {
	uint8_t payload[10];
	payload[0] = 0x0a;
	payload[1] = state;
	return sendPacket(id, group, payload);
}


bool lencarta_ultrapro::lamp(uint8_t * address, lencarta_lamp_state state) {
	return lamp(address[0], address[1], state);
}

bool lencarta_ultrapro::lamp(uint8_t id, uint8_t group, lencarta_lamp_state state) {
	uint8_t payload[10];
	payload[1] = state;
	payload[0] = 0x07;
	return sendPacket(id, group, payload);
}

bool lencarta_ultrapro::lampPower(uint8_t * address, uint8_t power) {
	return lamp(address[0], address[1], power);
}

bool lencarta_ultrapro::lampPower(uint8_t id, uint8_t group, uint8_t power) {

	uint8_t payload[10];
	payload[1] = power;
	payload[0] = 0x08;
	return sendPacket(id, group, payload);
}

bool lencarta_ultrapro::sound(uint8_t * address, bool state) {
	return sound(address[0], address[1], state);
}


bool lencarta_ultrapro::sound(uint8_t id, uint8_t group, bool state) {
	uint8_t payload[10];
	payload[1] = state;
	payload[0] = 0x09;
	return sendPacket(id, group, payload);
}


bool lencarta_ultrapro::test(uint8_t * address) {
	return test(address[0], address[1]);
}

bool lencarta_ultrapro::test(uint8_t id, uint8_t group) {
	uint8_t payload[10];
	bool ack = false;

	payload[0] = 0x55;
	payload[1] = 0xaa;
	//Special sync channel
	radio.setChannel(baseChannel + group + 2);
	radio.stopListening();
	radio.openWritingPipe(baseAddress + id);
	ack = radio.write(payload, 10);
	radio.startListening();
	return ack;
}



