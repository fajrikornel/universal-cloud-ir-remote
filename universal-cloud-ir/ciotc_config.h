/******************************************************************************
 * Copyright 2018 Google
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
// This file contains your configuration used to connect to Cloud IoT Core

// WIFI
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// Cloud iot details.
const char* project_id = "your-GCP-project-id";
const char* location = "your-GCP-location";
const char* registry_id = "your-IoT-core-registry-id";
const char* device_id = "your-IoT-Core-device-id";

// Configuration for NTP
const char* ntp_primary = "time.google.com";
const char* ntp_secondary = "pool.ntp.org";

const unsigned char private_key[] = {
Put your private key here using this format:
// 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, ...
};

const int jwt_exp_secs = 3600; // Maximum 24H (3600*24)

// Certificates for SSL on the LTS server
const char* root_cert = "-----BEGIN CERTIFICATE-----\n"
    // Put the certificate here
    // (the lines between BEGIN and END certificate)
    "-----END CERTIFICATE-----\n";