#ifndef WORLDPACKET_H
#define WORLDPACKET_H

#include <QtCore>
#include <QTextStream>
#include "Opcodes/Opcodes.h"

class WorldPacket
{
public:
    WorldPacket(quint8 opcode) : m_opcode(opcode), m_stream(&m_buffer)
    {
        *this << GetOpcodeHeader(m_opcode);
    }

    qint8 GetOpcode() const
    {
        return m_opcode;
    }

    const QString& GetPacket() const
    {
        return m_buffer;
    }

    template<class T>
    WorldPacket& operator<<(const T& value)
    {
        m_stream << value;
        return *this;
    }

private:
    quint8 m_opcode;
    QString m_buffer;
    QTextStream m_stream;
};

#endif
