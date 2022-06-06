simple Dispatcher
{
    parameters:
    	volatile int n_servers;
    	volatile int k_limit;
    	volatile bool hasMemory = false;
    gates:
        input source_in;	
        input in;
        output out;
        output sink_out;
}
