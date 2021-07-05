
#ifndef __GDT_H
#define __GDT_H

#include <common/types.h>

namespace thirty2bitOS
{
    class GlobalDescriptorTable
    {
        public:
            class SegmentDescriptor
            {
                private:
                    thirty2bitOS::common::uint16_t limit_lo;
                    thirty2bitOS::common::uint16_t base_lo;
                    thirty2bitOS::common::uint8_t base_hi;
                    thirty2bitOS::common::uint8_t type;
                    thirty2bitOS::common::uint8_t flags_limit_hi;
                    thirty2bitOS::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(thirty2bitOS::common::uint32_t base, thirty2bitOS::common::uint32_t limit, thirty2bitOS::common::uint8_t type);
                    thirty2bitOS::common::uint32_t Base();
                    thirty2bitOS::common::uint32_t Limit();
            } __attribute__((packed));  // making byte perfect
            
        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            thirty2bitOS::common::uint16_t CodeSegmentSelector();
            thirty2bitOS::common::uint16_t DataSegmentSelector();
    };   
}

#endif
