#!/bin/bash

ENVOY_PORT=15001

./set_iptables.sh $ENVOY_PORT `id -u root`
envoy -c envoy_config.json --v2-config-only
