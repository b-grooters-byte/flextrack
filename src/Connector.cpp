#include "Connector.h"

namespace ByteTrail
{


Connector::Connector()
{
    //ctor
}

Connector::~Connector()
{
    //dtor
}


bool Connector::IsConnected() const
{
    return _connected_to != nullptr;
}

void Connector::Connect(std::shared_ptr<Connector> to)
{
    if( _connected_to == nullptr && to != nullptr)
    {
        _connected_to = to;
    }
}

void Connector::Disconnect()
{
    _connected_to = nullptr;
}

double Connector::GetAngle() const
{
    return _angle;
}

}
