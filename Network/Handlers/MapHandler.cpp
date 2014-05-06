#include "ClientSession.h"

void ClientSession::HandleMapLoaded(QString& /*packet*/)
{
    // make character moving randomly on map
    RandomMove();
}
