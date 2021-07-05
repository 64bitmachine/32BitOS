
#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <gdt.h>

namespace thirty2bitOS
{
    namespace hardwarecommunication
    {
        class InterruptManager;

        class InterruptHandler
        {
            protected:
                thirty2bitOS::common::uint8_t interruptNumber;
                InterruptManager* interruptManager;
                InterruptHandler(InterruptManager* interruptManager, thirty2bitOS::common::uint8_t interruptNumber);
                ~InterruptHandler();
            
            public:
                virtual thirty2bitOS::common::uint32_t handleInterrupt(thirty2bitOS::common::uint32_t esp);
        };


        class InterruptManager
        {

            friend class InterruptHandler;

            protected:

                static InterruptManager* ActiveInterruptManager;
                InterruptHandler* handlers[256];


                struct GateDescriptor
                {
                    thirty2bitOS::common::uint16_t handlerAddressLowBits;
                    thirty2bitOS::common::uint16_t gdt_codeSegmentSelector;
                    thirty2bitOS::common::uint8_t reserved;
                    thirty2bitOS::common::uint8_t access;
                    thirty2bitOS::common::uint16_t handlerAddressHighBits;

                } __attribute__((packed));

                static GateDescriptor interruptDescriptorTable[256];

                struct InterruptDescriptorTablePointer
                {
                    thirty2bitOS::common::uint16_t size;
                    thirty2bitOS::common::uint32_t base;
                } __attribute__((packed));

                static void SetInterruptDescriptorTableEntry(
                    thirty2bitOS::common::uint8_t interruptNumber,
                    thirty2bitOS::common::uint16_t codeSegmentSelectorOffset,
                    void (*handler)(),
                    thirty2bitOS::common::uint8_t DescriptorPrivilegeLevel,
                    thirty2bitOS::common::uint8_t DescriptorType
                );

                Port8BitSlow picMasterCommand;
                Port8BitSlow picMasterData;
                Port8BitSlow picSlaveCommand;
                Port8BitSlow picSlaveData;

            public:

                InterruptManager(GlobalDescriptorTable* gdt);
                ~InterruptManager();

                void Activate();
                void Deactivate();

                static thirty2bitOS::common::uint32_t HandleInterrupt(thirty2bitOS::common::uint8_t interruptNumber, thirty2bitOS::common::uint32_t esp);
                thirty2bitOS::common::uint32_t DoHandleInterrupt(thirty2bitOS::common::uint8_t interruptNumber, thirty2bitOS::common::uint32_t esp);

                static void IgnoreInterruptRequest();
                static void HandleInterruptRequest0x00();
                static void HandleInterruptRequest0x01();

        };
    }
}

#endif
