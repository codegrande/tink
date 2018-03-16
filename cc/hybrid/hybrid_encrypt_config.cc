// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////

#include "tink/hybrid/hybrid_encrypt_config.h"

#include "tink/config.h"
#include "tink/aead/aead_config.h"
#include "tink/hybrid/hybrid_encrypt_catalogue.h"
#include "tink/util/status.h"
#include "proto/config.pb.h"

namespace util = crypto::tink::util;

namespace crypto {
namespace tink {

namespace {

google::crypto::tink::RegistryConfig* GenerateRegistryConfig() {
  google::crypto::tink::RegistryConfig* config =
      new google::crypto::tink::RegistryConfig();
  config->MergeFrom(AeadConfig::Tink_1_1_0());
  config->add_entry()->MergeFrom(*Config::GetTinkKeyTypeEntry(
      HybridEncryptConfig::kCatalogueName, HybridEncryptConfig::kPrimitiveName,
      "EciesAeadHkdfPublicKey", 0, true));
  config->set_config_name("TINK_HYBRID_ENCRYPT_1_1_0");
  return config;
}

}  // anonymous namespace

constexpr char HybridEncryptConfig::kCatalogueName[];
constexpr char HybridEncryptConfig::kPrimitiveName[];

// static
const google::crypto::tink::RegistryConfig& HybridEncryptConfig::Tink_1_1_0() {
  static const auto config = GenerateRegistryConfig();
  return *config;
}

// static
util::Status HybridEncryptConfig::RegisterStandardKeyTypes() {
  auto status = Init();
  if (!status.ok()) return status;
  return Config::Register(Tink_1_1_0());
}

// static
util::Status HybridEncryptConfig::Init() {
  AeadConfig::Init();
  return Registry::AddCatalogue(kCatalogueName, new HybridEncryptCatalogue());
}

}  // namespace tink
}  // namespace crypto
