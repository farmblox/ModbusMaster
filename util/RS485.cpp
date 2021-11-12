/* mbed Microcontroller Library
 * Copyright (c) 2006-2019 ARM Limited
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

#include "RS485.h"

#if DEVICE_SERIAL

#include "platform/mbed_critical.h"

namespace mbed {

RS485::RS485(
    PinName tx,
    PinName rx,
    int baud
) : SerialBase(tx, rx, baud)
{
    // No lock needed in the constructor
}

RS485::RS485(
    const serial_pinmap_t &static_pinmap, int baud
) : SerialBase(static_pinmap, baud)
{
    // No lock needed in the constructor
}

ssize_t RS485::write_no_irq(const void *buffer, size_t size)
{
    const unsigned char *buf = static_cast<const unsigned char *>(buffer);

    if (size == 0) {
        return 0;
    }

    bool lock_api = !core_util_in_critical_section();

    if (lock_api) {
        lock();
    }

    for (size_t i = 0; i < size; i++) {
        _base_putc(buf[i]);
    }

    if (lock_api) {
        unlock();
    }

    return size;
}

int RS485::putc(int c)
{
    return _base_putc(c);
}

ssize_t RS485::read_no_irq(void *buffer, size_t size)
{
    unsigned char *buf = static_cast<unsigned char *>(buffer);

    if (size == 0) {
        return 0;
    }

    lock();

    buf[0] = _base_getc();

    unlock();

    return 1;
}

int RS485::getc()
{
    return _base_getc();
}


#if DEVICE_SERIAL_FC
void RS485::set_flow_control(Flow type, PinName flow1, PinName flow2)
{
    lock();
    SerialBase::set_flow_control(type, flow1, flow2);
    unlock();
}
#endif // DEVICE_SERIAL_FC

} // namespace mbed

#endif // #if DEVICE_SERIAL
