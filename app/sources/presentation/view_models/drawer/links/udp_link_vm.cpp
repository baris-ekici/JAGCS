#include "udp_link_vm.h"

// Qt
#include <QDebug>

// Internal
#include "communication_service.h"

namespace
{
    const QString separator = ";";
}

using namespace presentation;

UdpLinkVm::UdpLinkVm(QObject* parent):
    SocketLinkVm(parent)
{
    connect(this, &LinkVm::linkChanged, this, &UdpLinkVm::udpLinkChanged);
}

QStringList UdpLinkVm::endpoints() const
{
    QStringList endpoints;

    if (m_description)
    {
        for (const QString& endpoint: m_description->parameter(
                 data_source::LinkDescription::Endpoints).toString().split(::separator))
        {
            if (endpoint.length()) endpoints.append(endpoint);
        }
    }

    return endpoints;
}

bool UdpLinkVm::autoAdd() const
{
    return m_description && m_description->parameter(data_source::LinkDescription::UdpAutoResponse).toBool();
}

void UdpLinkVm::setEndpoints(QStringList endpoints)
{
    if (m_description.isNull()) return;

    endpoints.removeDuplicates();

    m_description->setParameter(data_source::LinkDescription::Endpoints, endpoints.join(::separator));
    m_commService->save(m_description);
}

void UdpLinkVm::setAutoAdd(bool autoAdd)
{
    if (m_description.isNull() ||
        m_description->parameter(data_source::LinkDescription::UdpAutoResponse) == autoAdd) return;

    m_description->setParameter(data_source::LinkDescription::UdpAutoResponse, autoAdd);
    m_commService->save(m_description);
}
