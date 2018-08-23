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

#include "get_snis.h"

#include "envoy/buffer/buffer.h"
#include "envoy/network/connection.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Filter {

Network::FilterStatus GetSNIsFilter::onNewConnection() {
  ENVOY_LOG(info, "GetSNIsFilter:onNewConnection(), connection requestedServerName: {}", read_callbacks_->connection().requestedServerName());
  ENVOY_LOG(info, "GetSNIsFilter:onNewConnection(), network level requestedServerName: {}", read_callbacks_->networkLevelRequestedServerName());
  return Network::FilterStatus::Continue;
}

Network::FilterStatus GetSNIsFilter::onData(Buffer::Instance&, bool) {
  ENVOY_LOG(info, "GetSNIsFilter:onData(), connection requestedServerName: {}", read_callbacks_->connection().requestedServerName());
  ENVOY_LOG(info, "GetSNIsFilter:onData(), network level requestedServerName: {}", read_callbacks_->networkLevelRequestedServerName());
  return Network::FilterStatus::Continue;
}

} // namespace Filter
} // namespace Envoy
