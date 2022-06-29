simple PoissonDelay
{
    parameters:
        @signal[busy](type="bool");
        @statistic[busy](title="server busy state";record=vector?,timeavg;interpolationmode=sample-hold);
        volatile double lambda;
    gates:
        input in;
        //input ext_in;
        output out;
}
