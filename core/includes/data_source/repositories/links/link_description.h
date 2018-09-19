#ifndef LINK_DESCRIPTION_H
#define LINK_DESCRIPTION_H

// Qt
#include <QVariant>
#include <QMap>

// Internal
#include "link_traits.h"

namespace data_source
{
    class LinkDescription: public QObject
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(Type type READ type WRITE setType)
        Q_PROPERTY(QString protocol READ protocol WRITE setProtocol)
        Q_PROPERTY(QString parameters READ parameters WRITE setParameters)
        Q_PROPERTY(bool autoConnect READ isAutoConnect WRITE setAutoConnect)

    public:
        enum Type: quint8
        {
            UnknownType = 0,
            Serial,
            Udp,
            Tcp,
            Bluetooth
        };

        enum Parameter
        {
            UnknownParameter = 0,

            Device,
            BaudRate,
            Address,
            Port,
            Endpoints,
            UdpAutoResponse
        };

        QString name() const;
        void setName(const QString& name);

        Type type() const;
        void setType(Type type);

        QString protocol() const;
        void setProtocol(const QString& protocol);

        QString parameters() const;
        void setParameters(const QString& parameters);
        QVariant parameter(Parameter key, const QVariant& parameter = QVariant()) const;
        void setParameter(Parameter key, const QVariant& parameter);
        void clearParameters();
        void clearSuperfluousParameters();

        bool isAutoConnect() const;
        void setAutoConnect(bool autoConnect);

        bool isConnected() const;
        void setConnected(bool isConnected);

//    signals:
//        void linkSent(int descriptionId);
//        void linkRecv(int descriptionId);

    private:
        QString m_name;
        Type m_type = UnknownType;
        QString m_protocol;
        QMap<Parameter, QVariant> m_parameters;
        bool m_autoConnect = true;

        bool m_connected = false;

        Q_ENUM(Type)
        Q_ENUM(Parameter)
    };
}

#endif // LINK_DESCRIPTION_H
