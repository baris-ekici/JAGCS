#include "vehicle_dashboard_factory.h"

// Qt
#include <QVariant>

// Internal
#include "domain_entry.h"
#include "telemetry_service.h"
#include "telemetry.h"

#include "vehicle.h"

#include "dashboard_presenter.h"
#include "status_presenter.h"
#include "ahrs_presenter.h"
#include "satellite_presenter.h"
#include "barometric_presenter.h"
#include "pitot_presenter.h"
#include "power_system_presenter.h"
#include "compass_presenter.h"
#include "navigator_presenter.h"
#include "battery_presenter.h"
#include "home_presenter.h"
#include "wind_presenter.h"
#include "common_command_presenter.h"
#include "mission_command_presenter.h"
#include "mission_status_presenter.h"

using namespace presentation;

VehicleDashboardFactory::VehicleDashboardFactory(domain::DomainEntry* entry,
                                                 const db::VehiclePtr& vehicle):
    IDashboardFactory(),
    m_entry(entry),
    m_vehicle(vehicle)
{}

DashboardPresenter* VehicleDashboardFactory::create()
{
    domain::Telemetry* node = m_entry->telemetryService()->vehicleNode(m_vehicle->id());
    if (!node) return nullptr;

    // TODO: vehicle type
    DashboardPresenter* dashboard = new DashboardPresenter();

    dashboard->addInstrument("satellite", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));

    dashboard->addInstrument("fd", new StatusPresenter(
                                  node->childNode(domain::Telemetry::Status), dashboard));
    dashboard->addInstrument("fd", new AhrsPresenter(
                                 node->childNode(domain::Telemetry::Ahrs), dashboard));
    dashboard->addInstrument("fd", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));
    dashboard->addInstrument("fd", new BarometricPresenter(
                                 node->childNode(domain::Telemetry::Barometric), dashboard));
    dashboard->addInstrument("fd", new PitotPresenter(
                                 node->childNode(domain::Telemetry::Pitot), dashboard));
    dashboard->addInstrument("fd", new PowerSystemPresenter(
                                 node->childNode(domain::Telemetry::PowerSystem), dashboard));

    dashboard->addInstrument("nav", new StatusPresenter(
                                 node->childNode(domain::Telemetry::Status), dashboard));
    dashboard->addInstrument("nav", new CompassPresenter(
                                 node->childNode(domain::Telemetry::Compass), dashboard));
    dashboard->addInstrument("nav", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));
    dashboard->addInstrument("nav", new NavigatorPresenter(
                                 node->childNode(domain::Telemetry::Navigator), dashboard));
    dashboard->addInstrument("nav", new HomePresenter(
                                 node->childNode(domain::Telemetry::Position),
                                 node->childNode(domain::Telemetry::HomePosition), dashboard));
    dashboard->addInstrument("nav", new WindPresenter(
                                 node->childNode(domain::Telemetry::Wind), dashboard));

    dashboard->addInstrument("status", new StatusPresenter(
                                 node->childNode(domain::Telemetry::Status), dashboard));
    dashboard->addInstrument("status", new BatteryPresenter(
                                 node->childNode(domain::Telemetry::Battery), dashboard));
    dashboard->addInstrument("status", new CommonCommandPresenter(
                                 m_entry->commandService(), m_vehicle->id(), dashboard));

    dashboard->addInstrument("mission", new NavigatorPresenter(
                                 node->childNode(domain::Telemetry::Navigator), dashboard));
    dashboard->addInstrument("mission", new MissionCommandPresenter(
                                 m_entry->commandService(), m_vehicle->id(), dashboard));
    dashboard->addInstrument("mission", new MissionStatusPresenter(
                                 m_entry->dbFacade(), m_vehicle->id(), dashboard));

    return dashboard;
}
