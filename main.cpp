#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

struct Preference {
    uint32_t telemetryInterval;
    uint32_t reportInterval;
    uint8_t telemetryRetryCount;
    uint8_t reportRetryCount;
    uint8_t maxWiFiRetryCount;

    json toJSONObject() {
        json j;
        j["telemetryInterval"] = telemetryInterval;
        j["reportInterval"] = reportInterval;
        j["telemetryRetryCount"] = telemetryRetryCount;
        j["reportRetryCount"] = reportRetryCount;
        j["maxWiFiRetryCount"] = maxWiFiRetryCount;

        return j;
    }

    void fromJSON(const std::string& jsonString) {
        json j = json::parse(jsonString);

        // will throw exceptions if an element is not found.
        telemetryInterval = j["telemetryInterval"];
        reportInterval = j["reportInterval"];
        telemetryRetryCount = j["telemetryRetryCount"];
        reportRetryCount = j["reportRetryCount"];
        maxWiFiRetryCount = j["maxWiFiRetryCount"];
    }

    std::string toJSON() {
        return toJSONObject().dump();
    }

    std::vector<uint8_t> toCBOR() {
        return json::to_cbor(toJSONObject());
    }
};

int main() {
    Preference pref{};
    std::string json_string = pref.toJSON();
    std::vector<uint8_t> cbor = pref.toCBOR();

    Preference pref2{};
    pref2.fromJSON(json_string);

    printf("JSON length: %lu\tCBOR length: %lu\r\n", json_string.size(), cbor.size());

    return 0;
}
