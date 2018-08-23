#include "get_sni.h"

#include "envoy/buffer/buffer.h"
#include "envoy/network/connection.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Filter {

Network::FilterStatus GetSNIFilter::onNewConnection() {
  ENVOY_LOG(info, "GetSNIFilter:onNewConnection(), requestedServerName: {}", read_callbacks_->connection().requestedServerName());
  return Network::FilterStatus::Continue;
}

} // namespace Filter
} // namespace Envoy
