
#ifndef __PORT_H
#define __PORT_H

#include <common/types.h>

namespace thirty2bitOS
{
    namespace hardwarecommunication
    {
        class Port
        {
            protected:
                thirty2bitOS::common::int16_t portnumber;
                Port(thirty2bitOS::common::uint16_t portnumber);
                ~Port();
        };
        
        class Port8Bit : public Port
        {
            public:
                Port8Bit(thirty2bitOS::common::uint16_t portnumber);
                ~Port8Bit();
                virtual void Write(thirty2bitOS::common::uint8_t data);
                virtual thirty2bitOS::common::uint8_t Read();
        };

        class Port8BitSlow : public Port8Bit
        {
            public:
                Port8BitSlow(thirty2bitOS::common::uint16_t portnumber);
                ~Port8BitSlow();
                virtual void Write(thirty2bitOS::common::uint8_t data);
        };

        class Port16Bit : public Port
        {
            public:
                Port16Bit(thirty2bitOS::common::uint16_t portnumber);
                ~Port16Bit();
                virtual void Write(thirty2bitOS::common::uint16_t data);
                virtual thirty2bitOS::common::uint16_t Read();
        };

        class Port32Bit : public Port
        {
            public:
                Port32Bit(thirty2bitOS::common::uint16_t portnumber);
                ~Port32Bit();
                virtual void Write(thirty2bitOS::common::uint32_t data);
                virtual thirty2bitOS::common::uint32_t Read();
        };
    }
}

#endif