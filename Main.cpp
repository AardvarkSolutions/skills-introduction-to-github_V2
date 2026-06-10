// CircularBuffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdint>
#include "xparameters.h"
#include "CircularErrorBuffer.h"
#include "DDR3RamStorage.h"

static void delay_seconds_approx(uint32_t seconds)
{
    const uint64_t iterations = (static_cast<uint64_t>(XPAR_CPU_CORE_CLOCK_FREQ_HZ) * seconds) / 8U;

    for (volatile uint64_t i = 0; i < iterations; ++i) {
        asm volatile("nop");
    }
}

int main()
{
    std::cout << "Hello World!\n";
    DDR3RamStorage m_DDR3RamStorage(DDR3_STORAGE_BASE_ADDRESS, 100U);
    CircularErrorBuffer myCircularErrorBuffer(m_DDR3RamStorage,100U) ;


    while (1)
    {
        myCircularErrorBuffer.logError(ErrorCode::ERR_FREQ_LOCK);

        //sleep(3);

        myCircularErrorBuffer.logError(ErrorCode::ERR_HW_FAIL);


    

        myCircularErrorBuffer.logError(ErrorCode::ERR_TIMEOUT);
        //delay_seconds_approx(3);


    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
