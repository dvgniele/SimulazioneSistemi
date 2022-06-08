simple Dispatcher
{
    parameters:
    	volatile int k_limit;
    	volatile int d_limit;
    	volatile bool hasMemory;
    gates:
        input source_in;	
        input in;
        output out;
        output sink_out;
}
