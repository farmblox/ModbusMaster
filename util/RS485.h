/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_RS485_H
#define MBED_RS485_H

#include "platform/platform.h"

#if DEVICE_SERIAL || defined(DOXYGEN_ONLY)

#include <cstdarg>

#include "drivers/SerialBase.h"
// #include "platform/FileHandle.h"
#include "platform/mbed_toolchain.h"
#include "platform/NonCopyable.h"


namespace mbed {
/** \defgroup drivers-public-api-uart UART
 * \ingroup drivers-public-api
 */

/**
 * \defgroup drivers_UnbufferedSerial UnbufferedSerial class
 * \ingroup drivers-public-api-uart
 * @{
 */

/**
 * Class implementation for unbuffered I/O for an interrupt driven application
 * or one that needs to have more control.
 */
class RS485:
    public SerialBase,
    private NonCopyable<RS485> {
public:
    /**
     * Create a serial port instance connected to the specified transmit and
     * receive pins, with the specified baud rate.
     *
     *  @param tx Transmit pin
     *  @param rx Receive pin
     *  @param baud The baud rate of the serial port (optional, defaults to MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE)
     *
     *  @note
     *    Either tx or rx may be specified as NC if unused
     */
    RS485(
        PinName tx,
        PinName rx,
        int baud = MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE
    );

    /** Create a UnbufferedSerial port, connected to the specified transmit and
     *  receive pins, with a particular baud rate.
     *  @param static_pinmap reference to structure which holds static pinmap
     *  @param baud The baud rate of the serial port (optional, defaults to
     *              MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE)
     */
    RS485(
        const serial_pinmap_t &static_pinmap,
        int baud = MBED_CONF_PLATFORM_DEFAULT_SERIAL_BAUD_RATE
    );

    /** Write the contents of a buffer to a file
     *
     * Blocks until all data is written
     *
     *  @param buffer   The buffer to write from
     *  @param size     The number of bytes to write
     *  @return         The number of bytes written
     */
    ssize_t write_no_irq(const void *buffer, size_t size);

    int putc(int c);

    /** Read the contents of a file into a buffer
     *
     *  Blocks and reads exactly one character
     *
     *  @param buffer   The buffer to read in to
     *  @param size     The number of bytes to read
     *  @return         The number of bytes read
     */
    ssize_t read_no_irq(void *buffer, size_t size);

    int getc();


    using SerialBase::attach;
    using SerialBase::baud;
    using SerialBase::format;
    using SerialBase::readable;
    // using SerialBase::write;
    using SerialBase::writeable;
    using SerialBase::IrqCnt;
    using SerialBase::RxIrq;
    using SerialBase::TxIrq;

#if DEVICE_SERIAL_FC
    // For now use the base enum - but in future we may have extra options
    // such as XON/XOFF or manual GPIO RTSCTS.
    using SerialBase::Flow;
    // In C++11, we wouldn't need to also have using directives for each value
    using SerialBase::Disabled;
    using SerialBase::RTS;
    using SerialBase::CTS;
    using SerialBase::RTSCTS;

    /** Set the flow control type on the serial port
     *
     *  @param type the flow control type (Disabled, RTS, CTS, RTSCTS)
     *  @param flow1 the first flow control pin (RTS for RTS or RTSCTS, CTS for CTS)
     *  @param flow2 the second flow control pin (CTS for RTSCTS)
     */
    void set_flow_control(Flow type, PinName flow1 = NC, PinName flow2 = NC);
#endif // DEVICE_SERIAL_FC
};

} // namespace mbed

#endif // DEVICE_SERIAL || defined(DOXYGEN_ONLY)

#endif // MBED_RS485_H
