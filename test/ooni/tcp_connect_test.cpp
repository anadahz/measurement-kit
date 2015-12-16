// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#define CATCH_CONFIG_MAIN
#include "src/ext/Catch/single_include/catch.hpp"

#include <chrono>
#include <iostream>
#include <list>
#include <measurement_kit/ooni.hpp>
#include <string>
#include <thread>

using namespace mk;

TEST_CASE("Synchronous tcp-connect test") {
    Var<std::list<std::string>> logs(new std::list<std::string>);
    ooni::TcpConnectTest()
        .set_port("80")
        .set_input_file_path("test/fixtures/hosts.txt")
        .on_log([=](const char *s) { logs->push_back(s); })
        .run();
    for (auto &s : *logs) std::cout << s << "\n";
}

TEST_CASE("Asynchronous tcp-connect test") {
    Var<std::list<std::string>> logs(new std::list<std::string>);
    bool done = false;
    ooni::TcpConnectTest()
        .set_port("80")
        .set_input_file_path("test/fixtures/hosts.txt")
        .on_log([=](const char *s) { logs->push_back(s); })
        .run([&done]() { done = true; });
    do {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } while (!done);
    for (auto &s : *logs) std::cout << s << "\n";
}

TEST_CASE("Make sure that set_output_path() works") {
    auto instance = ooni::TcpConnectTest()
        .set_output_file_path("foo.txt")
        .create_test_();
    REQUIRE(instance->get_report_filename() == "foo.txt");
}

TEST_CASE("Make sure that default get_output_path() is nonempty") {
    auto instance = ooni::TcpConnectTest()
        .create_test_();
    REQUIRE(instance->get_report_filename() != "");
}
