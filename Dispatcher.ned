simple Dispatcher
{
    parameters:
        volatile int k_limit;
    	volatile int d_limit;
    	volatile bool hasMemory;

        volatile double serviceTime @unit(s);
    gates:
        input source_in;	
        input ext_in;
        output out;
        output sink_out;
}
