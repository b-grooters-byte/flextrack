#ifndef BYTETRAIL_CONNECTOR_H
#define BYTETRAIL_CONNECTOR_H

#include <memory>
#include "Geometry.h"

namespace ByteTrail
{


class Connector
{
    public:
        Connector();
        virtual ~Connector();

        bool IsConnected() const;
        void Connect(std::shared_ptr<Connector> to);
        void Disconnect();
        double GetAngle() const;

    protected:
    private:
        Point _location;
        double _angle;

        std::shared_ptr<Connector> _connected_to;
};

}

#endif // BYTETRAILCONNECTOR_H
