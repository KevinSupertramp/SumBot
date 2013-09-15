#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>

class ClientSession;

enum Opcodes
{
    MSG_UNKNOWN_OPCODE,

    // Client messages (CMSG)
    CMSG_AUTHENTICATION,
    CMSG_CLIENT_VERSION,

    // Server messages (SMSG)
    SMSG_ACCOUNT_COMMUNITY,
    SMSG_ACCOUNT_GMLEVEL,
    SMSG_ACCOUNT_PSEUDO,
    SMSG_ACCOUNT_SECRET_QUESTION,
    SMSG_HELLO_CONNECTION_SERVER,
    SMSG_REALM_LIST,

    // Client and server messages (MSG)
    MSG_QUEUE_POSITION,

    /* Client messages (CMSG)
    CMSG_CHAR_CREATE,
    CMSG_CHAR_DELETE,
    CMSG_CHAR_LIST,
    CMSG_GAME_CREATE,
    CMSG_GAME_INFORMATIONS,
    CMSG_GIFTS_LIST,
    CMSG_SCREEN_INFO,
    CMSG_SESSION_KEY,
    CMSG_TICKET,

    // Server messages (SMSG)
    SMSG_ACCOUNT_ALREADY_CONNECTED,
    SMSG_ACCOUNT_BAD_CLIENT_VERSION,
    SMSG_ACCOUNT_BANNED,
    SMSG_ACCOUNT_GMLEVEL,
    SMSG_ACCOUNT_LOGIN_ERROR,
    SMSG_ACCOUNT_PSEUDO,
    SMSG_ACCOUNT_REALM_CHAR,
    SMSG_ACCOUNT_SECRET_QUESTION,
    SMSG_CHAR_LIST,
    SMSG_CHAR_CREATE,
    SMSG_CHAR_CREATE_ERROR,
    SMSG_CHAR_DELETE,
    SMSG_CHAR_STATS,
    SMSG_GAME_CREATE,
    SMSG_GIFTS_LIST,
    SMSG_COMMUNITY,
    SMSG_HELLO_CONNECTION_SERVER,
    SMSG_HELLO_GAME_SERVER,
    SMSG_MAP_DATA,
    SMSG_MAP_LOADED,
    SMSG_OBJECT_MOVEMENT,
    SMSG_QUEUE_OUT_OF_BOUNDS,
    SMSG_REALM_INFOS,
    SMSG_REALMS_LIST,
    SMSG_SEARCH_FRIEND,
    SMSG_TICKET_ACCEPTED,
    SMSG_TICKET_REFUSED,

    // Client and server messages (MSG)
    MSG_CHAR_RANDOM_NAME,
    MSG_CHAR_SELECT,
    MSG_QUEUE_POSITION,
    MSG_REGIONAL_VERSION,
    MSG_SERVER_DATE,
    MSG_SERVER_TIME,*/

    NUM_MSG_TYPES
};

struct OpcodeStruct
{
    QString name;
    QString header;
    void (ClientSession::*handler)(QString& packet);
};

extern OpcodeStruct opcodeTable[NUM_MSG_TYPES];

inline QString GetOpcodeName(quint8 opcode)
{
    if(opcode >= NUM_MSG_TYPES)
        return "Unknown opcode";

    return opcodeTable[opcode].name;
}

inline QString GetOpcodeHeader(quint8 opcode)
{
    if(opcode >= NUM_MSG_TYPES)
        return "Unknown opcode";

    return opcodeTable[opcode].header;
}

// tmp
inline OpcodeStruct GetOpcodeByHeader(QString header)
{
    for (quint8 i = 0; i < NUM_MSG_TYPES; ++i)
        if (header == opcodeTable[i].header)
            return opcodeTable[i];

    return opcodeTable[MSG_UNKNOWN_OPCODE];
}

#endif
