simple Dispatcher
{
    parameters:
        @signal[busy](type="bool");
        @signal[idle_length](type="int");
        @statistic[busy](title="server busy state";record=vector?,timeavg;interpolationmode=sample-hold);
        @statistic[idle_length](title="idle servers count";record=vector?,timeavg;interpolationmode=sample-hold);
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
