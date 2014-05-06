#ifndef OPCODES_H
#define OPCODES_H

#include <QtCore>

class ClientSession;

enum Opcodes
{
    MSG_UNKNOWN_OPCODE,

    // Client messages (CMSG)
    CMSG_AUTHENTICATION,
    CMSG_CHAR_CREATE,
    CMSG_CHAR_LIST,
    CMSG_CLIENT_VERSION,
    CMSG_GAME_CREATE,
    CMSG_GAME_INFORMATIONS,
    CMSG_REALM_INFOS,
    CMSG_SERVER_DATE,
    CMSG_SESSION_KEY,

    // Server messages (SMSG)
    SMSG_ACCOUNT_COMMUNITY,
    SMSG_ACCOUNT_GMLEVEL,
    SMSG_ACCOUNT_PSEUDO,
    SMSG_ACCOUNT_SECRET_QUESTION,
    SMSG_AUTHENTICATION_RESULT,
    SMSG_CHAR_CREATE,
    SMSG_CHAR_LIST,
    SMSG_GAME_ACTION_FINISHED,
    SMSG_HELLO_CONNECTION_SERVER,
    SMSG_HELLO_GAME_SERVER,
    SMSG_MAP_LOADED,
    SMSG_OBJECT_MOVEMENT,
    SMSG_REALM_INFOS,
    SMSG_REALM_LIST,

    // Client and server messages (MSG)
    MSG_CHAR_RANDOM_NAME,
    MSG_CHAR_SELECT,
    MSG_GAME_ACTION,
    MSG_QUEUE_POSITION,
    MSG_TICKET,

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
