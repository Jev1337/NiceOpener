// 01_send.ino

// Simple example of sending codes with a Radio Frequencies device.
// Sends code 4 times every 5 seconds.

/*
  Copyright 2021 Sébastien Millet

  `RF433send' is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  `RF433send' is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this program. If not, see
  <https://www.gnu.org/licenses>.
*/

// Schematic:
//   RF433 TRANSMITTER data pin plugged on Arduino D4

#include "RF433send.h"

#define PIN_RFOUT 2

RfSend *tx_whatever;


void setup() {
    pinMode(PIN_RFOUT, OUTPUT);

    Serial.begin(115200);

        // rfsend_builder performs some asserts that, it failed, write details
        // to Serial and then block execution.
        // If construction is done before setup() execution (as is the case with
        // global variables), no output is done and we loose interesting debug
        // information.
        // Therefore I prefer this style over using a global radio object.

    tx_whatever = rfsend_builder(
        RfSendEncoding::TRIBIT,
        PIN_RFOUT,
        RFSEND_DEFAULT_CONVENTION,  // Do we want to invert 0 and 1 bits? No.
        1,       // Number of sendings
        nullptr, // No callback to keep/stop sending (if you want to send
                 // SO LONG AS a button is pressed, the function reading the
                 // button state is to be put here).
        18856, // initseq
        1436, // lo_prefix
        1532, // hi_prefix
        0, // first_lo_ign
        496, // lo_short
        980, // lo_long
        0, // hi_short (0 => take lo_short)
        0, // hi_long  (0 => take lo_long)
        1448, // lo_last
        18856, // sep
        52  // nb_bits
    );
    Serial.println("Init");
    delay(10000);
    
    int i;
    byte data1[] = { 0x1 , 0xf6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data2[] = { 0x1 , 0xc6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data3[] = { 0x1 , 0xd6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data4[] = { 0x1 , 0xa6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data5[] = { 0x1 , 0xb6 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    byte data6[] = { 0x1 , 0x86 , 0x60 , 0xba , 0x62 , 0xb , 0x4c };
    for (i=0; i<10; i++){
      Serial.println("Sending Pairing Codes...");
      tx_whatever->send(sizeof(data1), data1);
      tx_whatever->send(sizeof(data2), data2);
      tx_whatever->send(sizeof(data3), data3);
      tx_whatever->send(sizeof(data4), data4);
      tx_whatever->send(sizeof(data5), data5);
      tx_whatever->send(sizeof(data6), data6);
    }

    Serial.println("Pairing Mode Complete, Please Send 3x from old remote!");
    Serial.println("Waiting 7 seconds before repairing");
    delay(1000);
    Serial.println("Waiting 6 seconds before repairing");
    delay(1000);
    Serial.println("Waiting 5 seconds before repairing");
    delay(1000);
    Serial.println("Waiting 4 seconds before repairing");
    delay(1000);
    Serial.println("Waiting 3 seconds before repairing");
    delay(1000);
    Serial.println("Waiting 2 seconds before repairing");
    delay(1000);
    Serial.println("Waiting 1 seconds before repairing");
    delay(1000);
    byte data01[] = { 0x1 , 0xf9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data02[] = { 0x1 , 0xc9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data03[] = { 0x1 , 0xd9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data04[] = { 0x1 , 0xa9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data05[] = { 0x1 , 0xb9 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    byte data06[] = { 0x1 , 0x89 , 0x73 , 0x54 , 0x5d , 0x34 , 0x73 };
    for (i=0; i<4; i++){
      Serial.println("Sending Pairing Codes...");
      tx_whatever->send(sizeof(data01), data01);
      tx_whatever->send(sizeof(data02), data02);
      tx_whatever->send(sizeof(data03), data03);
      tx_whatever->send(sizeof(data04), data04);
      tx_whatever->send(sizeof(data05), data05);
      tx_whatever->send(sizeof(data06), data06);
    }
    Serial.println("Pairing Mode Completed.");
    Serial.println("Waiting 5 seconds before testing");
    delay(1000);
    Serial.println("Waiting 4 seconds before testing");
    delay(1000);
    Serial.println("Waiting 3 seconds before testing");
    delay(1000);
    Serial.println("Waiting 2 seconds before testing");
    delay(1000);
    Serial.println("Waiting 1 seconds before testing");
    delay(1000);
    byte data001[] = { 0x1 , 0xf7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data002[] = { 0x1 , 0xc7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data003[] = { 0x1 , 0xd7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data004[] = { 0x1 , 0xa7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data005[] = { 0x1 , 0xb7 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };
    byte data006[] = { 0x1 , 0x87 , 0x71 , 0xdd , 0x53 , 0x3a , 0x7d };

    Serial.println("Tx Test...");
    tx_whatever->send(sizeof(data001), data001);
    tx_whatever->send(sizeof(data002), data002);
    tx_whatever->send(sizeof(data003), data003);
    tx_whatever->send(sizeof(data004), data004);
    tx_whatever->send(sizeof(data005), data005);
    tx_whatever->send(sizeof(data006), data006);
    Serial.println("End of pairing");

}


void loop() {


}

// vim: ts=4:sw=4:tw=80:et
