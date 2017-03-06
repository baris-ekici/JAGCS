#include "mavlink_communicator_factory.h"

// Internal
#include "mavlink_communicator.h"

#include "heartbeat_handler.h"
#include "ping_handler.h"
#include "attitude_handler.h"
#include "position_handler.h"
#include "gps_handler.h"
#include "system_status_handler.h"
#include "vfr_hud_handler.h"
#include "command_handler.h"
#include "home_position_handler.h"
#include "manual_handler.h"
#include "mission_handler.h"

#include "settings.h"
#include "settings_provider.h"
#include "udp_link.h"

using namespace domain;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory(
        VehicleService* vehicleService,
        MissionService* missionService):
    IMavLinkCommunicatorFactory(vehicleService, missionService)
{}

MavLinkCommunicator* MavLinkCommunicatorFactory::create()
{
    auto communicator = new MavLinkCommunicator();

    new HeartbeatHandler(m_vehicleService, communicator);
    new PingHandler(communicator);
    new AttitudeHandler(m_vehicleService, communicator);
    new PositionHandler(m_vehicleService, communicator);
    new GpsHandler(m_vehicleService, communicator);
    new SystemStatusHandler(m_vehicleService, communicator);
    new VfrHudHandler(m_vehicleService, communicator);
    new CommandHandler(m_vehicleService, communicator);
    new HomePositionHandler(m_vehicleService, communicator);
    new ManualHandler(m_vehicleService, communicator);
    new MissionHandler(m_missionService, communicator);
    // TODO: NAV_CONTROLLER_OUTPUT

    UdpLink* defaultUdpLink = new UdpLink(SettingsProvider::value(
                                              connection_settings::port).toInt(),
                                          communicator);
    communicator->addLink(defaultUdpLink);
    defaultUdpLink->up();

    return communicator;
}
