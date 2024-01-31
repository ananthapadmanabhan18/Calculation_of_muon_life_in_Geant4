#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"
#include "event.hh"
#include "stepping.hh"

class actioninitialization : public G4VUserActionInitialization
{
    public:
    actioninitialization();
    ~actioninitialization();
    virtual void Build() const;
    virtual void BuildForMaster() const;
};


#endif