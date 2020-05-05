/*
 * Title: ReadDigitalInputRiseFall
 *
 * Objective:
 *    This example demonstrates how to read the transition state (risen or
 *    fallen since last checked) of a ClearCore digital input.
 *
 * Description:
 *    This example repeatedly reads the transition state of a defined digital
 *    input. Information on how the input state has transitioned is printed
 *    to the USB serial port every 2 seconds.
 *
 * Requirements:
 * ** An input device, such as a switch or sensor, connected to IO-0.
 *
 * Links:
 * ** web link to doxygen (all Examples)
 * ** web link to ClearCore Manual (all Examples)  <<FUTURE links to Getting started webpage/ ClearCore videos>>
 *
 * Last Modified: 1/21/2020
 * Copyright (c) 2020 Teknic Inc. This work is free to use, copy and distribute under the terms of
 * the standard MIT permissive software license which can be found at https://opensource.org/licenses/MIT
 */

#include "ClearCore.h"

// Specify which input connector to use.
// ConnectorIO0 through ConnectorA12 all have digital input capability.
#define InputConnector ConnectorIO0

// Declares two boolean variables used to hold information on whether the input
// has risen or fallen
bool risen, fallen;

// Select the baud rate to match the target serial device
#define baudRate 9600

// Specify which serial to use: ConnectorUsb, ConnectorCOM0, or ConnectorCOM1.
#define SerialPort ConnectorUsb

void setup() {
    // Set up serial communication at a baud rate of 9600 bps then wait up to
    // 5 seconds for a port to open.
    // Serial communication is not required for this example to run, however the
    // example will appear to do nothing without serial output.
    SerialPort.Mode(Connector::USB_CDC);
    SerialPort.Speed(baudRate);
    uint32_t timeout = 5000;
    uint32_t startTime = Milliseconds();
    SerialPort.PortOpen();
    while (!SerialPort && Milliseconds() - startTime < timeout) {
        continue;
    }
}

void loop() {
    // Check whether the digital input has risen, fallen, or is unchanged
    // since the last time we checked.
    risen = InputConnector.InputRisen();
    fallen = InputConnector.InputFallen();

    SerialPort.Send("State: ");

    if (risen && fallen) {
        SerialPort.SendLine("RISEN and FALLEN");
    }
    else if (risen) {
        SerialPort.SendLine("RISEN");
    }
    else if (fallen) {
        SerialPort.SendLine("FALLEN");
    }
    else {
        SerialPort.SendLine("NO CHANGE");
    }

    // Wait a couple seconds then repeat...
    Delay_ms(2000);
}