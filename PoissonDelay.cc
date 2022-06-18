#include "PoissonDelay.h"

using namespace std;

Define_Module(PoissonDelay);

int lambda;

void PoissonDelay::initialize()
{
    cout << endl
         << "\t############\t[ " << this->getClassName() << " ]\t############\t" << endl;

    currentlyStored = 0;
    WATCH(currentlyStored);

    lambda = par("lambda");
    cout << "lambda: " << lambda << endl;
}

void PoissonDelay::handleMessage(cMessage *msg)
{
    //  msg to job conversion
    queueing::Job *job = check_and_cast<queueing::Job *>(msg);

    //  checks if the job has already been delayed
    if (!job->isSelfMessage())
    {
        currentlyStored++;

        //  a delay is generated for the current message
        double delay = poissonTime();
        scheduleAt(simTime() + delay, job);
    }
    else
    {
        //  sets the delay of the job
        job->setDelayCount(job->getDelayCount() + 1);
        simtime_t d = simTime() - job->getSendingTime();
        job->setTotalDelayTime(job->getTotalDelayTime() + d);

        currentlyStored--;

        //  the job is sent to the next node
        send(job, "out");
    }
}

int PoissonDelay::poissonTime()
{
    return poisson(lambda);
}
