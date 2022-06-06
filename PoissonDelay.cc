#include "PoissonDelay.h"

using namespace std;

Define_Module(PoissonDelay);

int lambda;

void PoissonDelay::initialize()
{
    cout << endl
         << "\t############\t[ " << this->getClassName() << " ]\t############\t" << endl;

    lambda = par("lambda");
    cout << "lambda: " << lambda << endl;
}

void PoissonDelay::handleMessage(cMessage *msg)
{
    cGate *arrivalGate = msg->getArrivalGate();

    //  #####   MESSAGGIO IN ARRIVO DALL'ESTERNO
    if (arrivalGate == gate("src_in"))
    {
        //  inizializzazione parametro: server_id
        auto mpar = new cMsgPar();
        mpar->setDoubleValue(0.0);
        mpar->setName("server_id");
        msg->addPar(mpar);

        //  inizializzazione parametro: is_idle
        mpar = new cMsgPar();
        mpar->setBoolValue(true);
        mpar->setName("is_idle");
        msg->addPar(mpar);

        //  inizializzazione parametro: n_jobs
        mpar = new cMsgPar();
        mpar->setDoubleValue(0.0);
        mpar->setName("n_jobs");
        msg->addPar(mpar);
    }

    // TODO - add service time

    send(msg, "out");
}
