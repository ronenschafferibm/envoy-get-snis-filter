# Get SNIs filter example
This filter is based on [envoy-filter-example](https://github.com/envoyproxy/envoy-filter-example)

It emits to the log the SNI of a connection and the SNI of the network level.

The SNI of a connection is populated by `envoy.listener.tls_inspector` listener filter.

The SNI of the network level is populated by `GetSNIsFilter` network filter.

## Building

1. Update envoy submodule
```
git submodule update --init
```

2. Checkout the branch of envoy with network_level_sni_reader filter
```
cd envoy
git checkout inner-sni-reader
cd -
```

3. Replace line 5 in [`envoy-get-sni-filter/envoy/ci/run_envoy_docker.sh`](https://github.com/envoyproxy/envoy/blob/5ec8b37da9de5893c04f75bbf2820014c62ea529/ci/run_envoy_docker.sh#L5):
```
. ci/envoy_build_sha.sh
```
with:
```
SCRIPT_DIR_PATH="`dirname \"$0\"`"
. "$SCRIPT_DIR_PATH"/envoy_build_sha.sh
```

4. Set the output build dir path:
``` export ENVOY_DOCKER_BUILD_DIR=~/envoyproxy/envoy-get-snis-filter/build```

5. Build the example with docker by running the script `'./ci/do_ci.sh build'` inside docker:
```
$ pwd
~/envoyproxy/envoy-get-snis-filter
$ ./envoy/ci/run_envoy_docker.sh './ci/do_ci.sh build'
```


# Building a docker image for envoy with get SNIs filter

1. Set the working directory:

```cd ~/envoyproxy/envoy-get-snis-filter/```

2. Build the image

```docker build -f ci/Dockerfile-envoy-get-snis -t ronensch/envoy-get-snis-filter .```

3. Push the image to the hub

```docker push ronensch/envoy-get-snis-filter```