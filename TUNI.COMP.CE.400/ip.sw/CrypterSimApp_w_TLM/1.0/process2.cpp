#include "process.hh"

void process2::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
	unsigned char* ptr = trans.get_data_ptr();
	unsigned int data;

	memcpy(&data, ptr, sizeof(data));

	if (values_available < 100) {
		values[index + values_available] = data;
		values_available++;
	} else {
		SC_REPORT_ERROR("process2", "Buffer overflow in b_transport!");
	}

	wait(delay);
}

void process2::write_value ()
{
	//sc_uint<32> in_value; //Value from the fifo
	//sc_uint<32> write_enable; //Becomes zero, when we may write.
	
	while( true )
	{
		while (values_available == 0) {
			wait();
		}
		
		//Read a value from fifo.
		//NOTICE: blocking operation, so it may take more than one cycle!
		//in_value = fifo.read();
		//How long the fifo communication takes
		//wait( P1_P2_DELAY, SC_NS );
		
		// Wait until memory is free
		sc_uint<32> write_enable;

		//Wait until we get write enable
		//NOTICE: accessing shared memory WILL take clock cycles!
		do {
			wait();
			write_enable = memory->read( ENABLE_INDEX );
		} while ( write_enable == 1 );

		// Write from buffer
		unsigned int value = values[index++];
		values_available--;

		//Write value, set read enable
		memory->write( in_value, VALUE_INDEX );
		memory->write( 1, ENABLE_INDEX );
	}
}
