// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef MEASUREMENT_KIT_NEUBOT_DASH_HPP
#define MEASUREMENT_KIT_NEUBOT_DASH_HPP

#include <measurement_kit/report.hpp>

namespace mk {
namespace neubot {
namespace dash {

MK_DEFINE_ERR(
        MK_ERR_NEUBOT(0), MiddleboxDetectedError, "middlebox_detected_error")

void run(
        std::string measurement_server_hostname,
        std::string auth_token,
        std::string real_address,
        SharedPtr<report::Entry> entry,
        Settings settings,
        SharedPtr<Reactor> reactor,
        SharedPtr<Logger> logger,
        Callback<Error> callback
);

void negotiate(
        SharedPtr<report::Entry> entry,
        Settings settings,
        SharedPtr<Reactor> reactor,
        SharedPtr<Logger> logger,
        Callback<Error> callback
);

} // namespace dash
} // namespace neubot
} // namespace mk
#endif
