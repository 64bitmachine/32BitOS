#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>

namespace thirty2bitOS
{
    namespace drivers
    {
        class KeyboardDriver : public thirty2bitOS::hardwarecommunication::InterruptHandler
        {
            thirty2bitOS::hardwarecommunication::Port8Bit dataport;
            thirty2bitOS::hardwarecommunication::Port8Bit commandport;

            public:
                KeyboardDriver(thirty2bitOS::hardwarecommunication::InterruptManager* manager);
                ~KeyboardDriver();
                virtual thirty2bitOS::common::uint32_t handleInterrupt(thirty2bitOS::common::uint32_t esp);
        };
    }
}

#endif