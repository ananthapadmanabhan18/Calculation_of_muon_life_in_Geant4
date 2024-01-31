#include "action.hh"

actioninitialization::actioninitialization(){}

actioninitialization::~actioninitialization(){}


void actioninitialization::BuildForMaster() const {

    runaction* runact = new runaction();
    SetUserAction(runact);

}



void actioninitialization::Build() const
{
    primarygenerator* generator = new primarygenerator();
    SetUserAction(generator);

    runaction* runact = new runaction();
    SetUserAction(runact);


    eventaction* eventAction = new eventaction(runact);
    SetUserAction(eventAction);

    steppingaction* stepact = new steppingaction(eventAction);
    SetUserAction(stepact);
}