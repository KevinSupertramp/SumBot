#include "Opcodes.h"
#include "Client/ClientSession.h"

OpcodeStruct opcodeTable[NUM_MSG_TYPES] =
{
    { "MSG_UNKNOWN_OPCODE",                         "",         &ClientSession::HandleNULL },

    // Client messages (CMSG)
    { "CMSG_AUTHENTICATION",                        "",         &ClientSession::HandleClientSide },
    { "CMSG_CHAR_CREATE",                           "AA",       &ClientSession::HandleCharList },
    { "CMSG_CHAR_LIST",                             "AL",       &ClientSession::HandleClientSide },
    { "CMSG_CLIENT_VERSION",                        "",         &ClientSession::HandleClientSide },
    { "CMSG_GAME_CREATE",                           "GC1",      &ClientSession::HandleClientSide },
    { "CMSG_GAME_INFORMATIONS",                     "GI",       &ClientSession::HandleClientSide },
    { "CMSG_REALM_INFOS",                           "AX",       &ClientSession::HandleClientSide },
    { "CMSG_SERVER_DATE",                           "BD",       &ClientSession::HandleClientSide },
    { "CMSG_SESSION_KEY",                           "Ai",       &ClientSession::HandleClientSide },

    // Server messages (SMSG)
    { "SMSG_ACCOUNT_COMMUNITY",                     "Ac",       &ClientSession::HandleNULL },
    { "SMSG_ACCOUNT_GMLEVEL",                       "alK",      &ClientSession::HandleNULL },
    { "SMSG_ACCOUNT_PSEUDO",                        "Ad",       &ClientSession::HandleAccountPseudo },
    { "SMSG_ACCOUNT_SECRET_QUESTION",               "AQ",       &ClientSession::HandleNULL },
    { "SMSG_AUTHENTICATION_RESULT",                 "Al",       &ClientSession::HandleAuthenticationResult },
    { "SMSG_CHAR_CREATE",                           "AA|",      &ClientSession::HandleCharCreate },
    { "SMSG_CHAR_LIST",                             "AL|",      &ClientSession::HandleCharList, },
    { "SMSG_HELLO_CONNECTION_SERVER",               "HC",       &ClientSession::HandleHelloConnectionServer },
    { "SMSG_HELLO_GAME_SERVER",                     "HG",       &ClientSession::HandleHelloGameServer },
    { "SMSG_REALM_INFOS",                           "AYK",      &ClientSession::HandleRealmInfos },
    { "SMSG_REALM_LIST",                            "AH",       &ClientSession::HandleRealmList, },

    // Client and server messages (MSG)
    { "MSG_CHAR_RANDOM_NAME",                       "AP",       &ClientSession::HandleCharRandomPseudo },
    { "MSG_CHAR_SELECT",                            "AS",       &ClientSession::HandleCharSelect },
    { "MSG_QUEUE_POSITION",                         "Af",       &ClientSession::HandleQueuePosition },
    { "MSG_TICKET",                                 "AT",       &ClientSession::HandleTicketResponse },
};
