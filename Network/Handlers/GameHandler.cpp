#include "ClientSession.h"

void ClientSession::HandleGameAction(QString& /*packet*/)
{

}

void ClientSession::HandleGameActionFinished(QString& /*packet*/)
{
    RandomMove();
}
