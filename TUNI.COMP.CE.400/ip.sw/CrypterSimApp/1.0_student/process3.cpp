#include "process.hh"

void process3::poll_and_forward ()
{
    sc_uint<32> data_from_memory; // Data read from memory (shared)
    
    while( true )
    {
        // Wait for the signal that indicates data is available in memory (meta-data)
        wait();
        
        // Poll for meta data: Check if data has been written to memory
        while (memory->read(ENABLE_INDEX) == 0) 
        {
            wait();
        }

        // Read the encrypted value from memory
        data_from_memory = memory->read(VALUE_INDEX);

        //How long the fifo communication takes
        wait( P3_P4_DELAY, SC_NS );
        
        // Forward the data to P4 via FIFO
        fifo.write(data_from_memory);
        
        // Reset the meta-data (clear the enable flag)
        memory->write(0, ENABLE_INDEX);

        // Synchronize with the next cycle
        wait();
    }
}

