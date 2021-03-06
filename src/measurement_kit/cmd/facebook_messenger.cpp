// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

#include "../cmdline.hpp"

namespace facebook_messenger {

#define USAGE                                                 \
    "usage: measurement_kit [options] facebook_messenger\n"   \

int main(std::list<Callback<BaseTest &>> &initializers, int argc, char **argv) {
    mk::nettests::FacebookMessengerTest test;
    int ch;
    while ((ch = getopt(argc, argv, "B:f:")) != -1) {
        switch (ch) {
        default:
            fprintf(stderr, "%s\n", USAGE);
            exit(1);
        }
    }
    argc -= optind, argv += optind;
    if (argc != 0) {
        fprintf(stderr, "%s\n", USAGE);
        exit(1);
        /* NOTREACHED */
    }

    common_init(initializers, test).run();
    return 0;
}

} // namespace facebook_messenger
