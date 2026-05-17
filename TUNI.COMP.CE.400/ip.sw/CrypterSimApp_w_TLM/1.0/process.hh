#include "header.hh"
#include "systemc.h"
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

SC_MODULE (process1)
{
	sc_in_clk	 clock; //Clock input
	sc_in<bool>   reset; //Reset, active high
	//sc_fifo_out<sc_uint<32> > fifo; //Fifo where the values are fed.
	sc_in<sc_uint<32> > in_value; //Value that is to be crypted in the system.

    tlm_utils::simple_initiator_socket<process1> socket; 
	
	void encrypt ();

	SC_CTOR(process1) : socket("socket")
	{
		//Initialize process as a thread, with reset active high
		SC_CTHREAD(encrypt, clock.pos());
		reset_signal_is(reset, false);
	}
}; 

SC_MODULE (process2)
{
	sc_in_clk	 clock; //Clock input
	sc_in<bool>   reset; //Reset, active high
	    // sc_fifo_in<sc_uint<32> > fifo; //Fifo where from the values are obtained.
	value1* memory; //The shared memory
    tlm_utils::simple_target_socket<process2> socket;

	// TLM buffer to hold incoming data
	unsigned int buffer[100];
	int index = 0;
	int values_available = 0;

	void write_value ();
    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);


	SC_CTOR(process2) : socket("socket")
	{
        socket.register_b_transport(this, &process2::b_transport);
		//Initialize process as a thread, with reset active high
		SC_CTHREAD(write_value, clock.pos());
		reset_signal_is(reset, false);
	}
};

SC_MODULE (process3)
{
    sc_in_clk    clock;         // Clock input
    sc_in<bool>  reset;         // Reset, active high
    sc_fifo_out<sc_uint<32>> fifo; // FIFO where the data is forwarded to P4.
    value1* memory;           // Shared memory

    void poll_and_forward ();  // Method for polling the meta-data and forwarding the data

    SC_CTOR(process3)
    {
        // Initialize process as a thread, with reset active high
        SC_CTHREAD(poll_and_forward, clock.pos());
        reset_signal_is(reset, false);
    }
};

SC_MODULE (process4)
{
    sc_in_clk    clock;         // Clock input
    sc_in<bool>  reset;         // Reset, active high
    sc_fifo_in<sc_uint<32>> fifo; // FIFO where data is read from P3.
    sc_out<sc_uint<32>> out_value; // The decrypted value output to test bench

    void decrypt_and_output ();  // Method for decryption and output notification

    SC_CTOR(process4)
    {
        // Initialize process as a thread, with reset active high
        SC_CTHREAD(decrypt_and_output, clock.pos());
        reset_signal_is(reset, false);
    }
};