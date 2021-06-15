#include "types.h"
#include "gdt.h"
#include "interrupts.h"

void printf(char* str)
{
    static uint16_t* screenMemory = (uint16_t*)0xb8000;

    static uint8_t x = 0, y = 0;

    for(int32_t i = 0; str[i] != '\0'; i++)
    {
        switch (str[i])
        {
            case '\n':
                y++;
                x = 0;
                break;
            
            default:
                screenMemory[80*y+x] = (screenMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            y++;
            x = 0;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                {
                    screenMemory[80*y+x] = (screenMemory[80*y+x] & 0xFF00) | ' ';
                }
            x = 0;
            y = 0;
        }
    }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for (constructor* i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
    
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t /*magicnumber*/)
{
    printf("\n===============================");
    printf("\n========   32 Bit OS   ========");
    printf("\n===============================");

    printf("\n Initializing GDT ");
    GlobalDescriptorTable gdt;
    printf(" - done");
    printf("\n Initializing Interrupt Manager ");
    InterruptManager interrupts(&gdt);
    printf(" - done");
    printf("\n Initiating interrupt request ");
    interrupts.Activate();

    while(1);
}
