#include "ServerList.h"
#include "cstring"

using std::to_string;

Define_Module(ServerList);

void ServerList::initialize()
{
    // TODO - Generated method body
}

void ServerList::handleMessage(cMessage *msg)
{
    auto name = "server_id";


    //cMessage *nmsg = new cMessage("blblblbl");

    /*
    for(int i = 0; i < mpars.size(); i++)
    {
        //  TODO controllare tipo del par
    }
    */


   auto mpar = msg->par(name);
   auto number = mpar.doubleValue();

   //std::string tmp = std::to_string(number);
   //char const *num_char = tmp.c_str();

   auto blblbl = Number_to_Char(number);


    cMessage *nmsg = new cMessage(blblbl);

    send(nmsg, "out");
}

const char* ServerList::Number_to_Char(int num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

const char* ServerList::Number_to_Char(float num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

const char* ServerList::Number_to_Char(double num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}
