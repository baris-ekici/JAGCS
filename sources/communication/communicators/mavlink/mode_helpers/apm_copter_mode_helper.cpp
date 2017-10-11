#include "apm_copter_mode_helper.h"

// Qt
#include <QMap>

namespace
{
    QMap<quint32, domain::Mode> modeMap =
    {
        { 0, domain::Mode::Stabilize },
        { 1, domain::Mode::Acro },
        { 2, domain::Mode::CtrlByAltitude },
        { 3, domain::Mode::Mission },
        { 4, domain::Mode::Guided },
        { 5, domain::Mode::Loiter },
        { 6, domain::Mode::Return },
        { 7, domain::Mode::Circle },
        { 9, domain::Mode::Landing },
        { 15, domain::Mode::Autotune },
        { 16, domain::Mode::HoldPosition },
        { 18, domain::Mode::Throw },
        { 19, domain::Mode::Avoid }
    };
}

using namespace comm;

ApmCopterModeHelper::ApmCopterModeHelper():
    IModeHelper()
{}

quint32 ApmCopterModeHelper::modeToCustomMode(domain::Mode mode)
{
    return ::modeMap.key(mode, 0);
}

domain::Mode ApmCopterModeHelper::customModeToMode(quint32 mode)
{
    return ::modeMap.value(mode, domain::Mode::None);
}