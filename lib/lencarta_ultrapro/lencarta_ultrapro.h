/**
 * @file lencarta_ultrapro.h
 *
 * Class declaration for lencarta_ultrapro
 */

#ifndef __LENCARTA_ULTRAPRO_H__
#define __LENCARTA_ULTRAPRO_H__

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

/**
 * Enum for the state of the modelling lamp.
 */
typedef enum {
	LENC_LAMP_OFF = 0,		/**<Sets the lamp OFF.*/
	LENC_LAMP_DIM,			/**<Sets the lamp to dim.*/
	LENC_LAMP_ON,			/**<Sets the lamp ON at full power.*/
	LENC_LAMP_POW_ON		/**<Sets the lamp ON with the corresponding power.*/
} lencarta_lamp_state;

/**
 * Library to control Lencarta UltraPro Studio Lighting
 */
class lencarta_ultrapro
{
private:
	RF24 radio; /**< The radio used (nRF24L01+).  */
	const uint64_t baseAddress = 0x5544332200LL; /**< The base address used for all UltraPro strobes. Only the last byte is modified. */
	const uint8_t baseChannel = 0x23; /**< The base channel used to address the strobes (corresponds to group 0). */



public:
	/**
	 * @name Public Interface
	 *
	 * Methods used to control the strobes
	 */
	/**@{*/

	/**
	 * Constructor
	 *
	 * Creates a new instance. Should be done before using any methods. Takes
	 * the two control pins used on the nRF24L01+
	 *
	 * @param cePin The pin connected to Chip Enable on the nRF24L01+
	 * @param csPin The pin connected to Chip Select on the nRF24L01+
	 */
	lencarta_ultrapro(uint8_t cePin, uint8_t csPin) : radio(cePin, csPin) {}

	/**
	 * Begin operation of the radio
	 *
	 * Should be called in setup()
	 */
	void begin(void);

	/**
	 * Fire a single strobe. Takes an address in uint8_t array [id,group]
	 *
	 * @param *address Array containing [id, group] for target flash
	 * @return True if the strobe acknowledged the packet.
	 */
	bool fireFlash(uint8_t * address);

	/**
	 * Fire a single strobe. Takes an id and group
	 *
	 * @param id The id of the strobe. Between 0-9.
	 * @param group The group of the strobe. Between 0-9.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool fireFlash(uint8_t id, uint8_t group);

	/**
	 * Set the power of the flash. Flash heads show power as a number between
	 * 1.0 and 6.0. This is translated to between 0 and 49 here. addresses the
	 * flash head using the id and group.
	 *
	 * @param id The id of the strobe. Between 0-9.
	 * @param group The group of the strobe. Between 0-9.
	 * @param power Power setting. Between 0 and 49.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool flashPower(uint8_t id, uint8_t group, uint8_t power);

	/**
	 * Set the power of the flash. Flash heads show power as a number between
	 * 1.0 and 6.0. This is translated to between 0 and 49 here. Addresses the
	 * strobe using an array of [id, group].
	 *
	 * @param id The id of the strobe. Between 0-9.
	 * @param group The group of the strobe. Between 0-9.
	 * @param power Power setting. Between 0 and 49.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool flashPower(uint8_t * address, uint8_t power);

	/**
	 * Sets optical slave mode on the flash head. Addressed using the id and
	 * group of the head.
	 *
	 * @param id The id of the strobe. Between 0-9.
	 * @param group The group of the strobe. Between 0-9.
	 * @param state True for slave mode, false for non-slave mode.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool slaveMode(uint8_t id, uint8_t group, bool state);

	/**
	 * Sets optical slave mode on the flash head. Addressed an array of [id,
	 * group]
	 *
	 * @param address An array containing address and id of the strobe.
	 * @param state True for slave mode, false for non-slave mode.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool slaveMode(uint8_t * address, bool state);

	/**
	 * Turns the modelling lamp of or off. Addresses using id and group.
	 *
	 * @param id The id of the strobe. Between 0-9.
	 * @param group The group of the strobe. Between 0-9.
	 * @param state The state of the lamp. @see lencarta_lamp_state.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool lamp(uint8_t id, uint8_t group, lencarta_lamp_state state);

	/**
	 * Turns the modelling lamp of or off. Addresses using array of [id, group].
	 *
	 * @param address An array of [id,group] for the target strobe.
	 * @param state The state of the lamp. @see lencarta_lamp_state.
	 * @return True if the strobe acknowledged the packet.
	 * */
	bool lamp(uint8_t * address, lencarta_lamp_state state);

	/**
	 * Sets the power of the modelling lamp. Addresses using id and group.
	 *
	 * @param id The id of the strobe. Between 0-9.
	 * @param group The group of the strobe. Between 0-9.
	 * @param power The power of the modelling lamp. 0-49 corresponds to 1.0 to
	 * 6.0 on the strobe's power setting.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool lampPower(uint8_t id, uint8_t group, uint8_t power);
	/**
	 * Sets the power of the modelling lamp. Addresses using array of [id, group].
	 *
	 * @param address An array of [id,group] for the target strobe.
	 * @param power The power of the modelling lamp. 0-49 corresponds to 1.0 to
	 * 6.0 on the strobe's power setting.
	 * @return True if the strobe acknowledged the packet.
	 * */
	bool lampPower(uint8_t * address, uint8_t power);

	/**
	 * Turns beeping on/off on the flash head. Addressed using id and group.
	 *
	 * @param id The id of the strobe. Between 0-9.
	 * @param group The group of the strobe. Between 0-9.
	 * @param state True for beeping on, false for beeping off.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool sound(uint8_t id, uint8_t group, bool state);

	/**
	 * Turns beeping on/off on the flash head. Addressed using id and group.
	 *
	 * @param address Array containing [id, group].
	 * @param state True for beeping on, false for beeping off.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool sound(uint8_t * address, bool state);

	/**
	 * Uses a different channel to test whether the strobe is responding. This
	 * will only work if the strobe is in test mode. This is acheived by
	 * pressing minus with TEST selected on the strobe. Addressed using id and
	 * group.
	 *
	 * @param id The id of the strobe. Between 0-9.
	 * @param group The group of the strobe. Between 0-9.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool test(uint8_t id, uint8_t group);

	/**
	 * Uses a different channel to test whether the strobe is responding. This
	 * will only work if the strobe is in test mode. This is acheived by
	 * pressing minus with TEST selected on the strobe. Addressed using an
	 * array of [id, group]
	 *
	 * @param address An array containing the [id, group].
	 * @return True if the strobe acknowledged the packet.
	 */
	bool test(uint8_t * address);

	/**@}*/
private:
	/**@{*/
	/**
	 * Used to send a packet to the target strobe. This will set the correct
	 * channel and open a pipe to write to the specified address. The payload
	 * should consist of a 10 byte array. If the array is longer or shorter
	 * than 10 bytes, behaviour is undefined.
	 *
	 * @param id The id of the target strobe.
	 * @param group The group of the target strobe.
	 * @param payload An array, 10 bytes in length, containing the desired
	 * payload.
	 * @return True if the strobe acknowledged the packet.
	 */
	bool sendPacket(uint8_t id, uint8_t group, uint8_t * payload);
	/**@}*/
};


#endif
