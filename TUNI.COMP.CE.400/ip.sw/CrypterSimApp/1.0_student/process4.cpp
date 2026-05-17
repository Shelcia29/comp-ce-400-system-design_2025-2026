#include "process.hh"

void process4::decrypt_and_output ()
{
    sc_uint<32> encrypted_data; // Data received from P3 via FIFO
    sc_uint<32> decrypted_data; // Decrypted data
    
    while( true )
    {
        // Wait for encrypted data from P3
        wait();
        
        // Read the encrypted data from FIFO
        encrypted_data = fifo.read();
        
        // Decrypt the data using the same key
        decrypted_data = encrypted_data ^ KEY;
        
        // Undo the permutation
        decrypted_data = (decrypted_data << 16) + (sc_uint<16>)(decrypted_data >> 16);
        
        // Output the decrypted data to the test bench
        out_value.write(decrypted_data);

        //How long the fifo communication takes
        wait( P3_P4_DELAY, SC_NS );
        //How long the processing takes
        wait( P4_LATENCY, SC_NS );
        
        // Notify that the output is valid (ready for validation)
        output_valid.notify();
        
        // Synchronize with the next cycle
        wait();
    }
}
