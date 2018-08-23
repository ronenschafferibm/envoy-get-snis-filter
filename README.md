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

1. Replace line 5 in [`envoy-get-sni-filter/envoy/ci/run_envoy_docker.sh`](https://github.com/envoyproxy/envoy/blob/5ec8b37da9de5893c04f75bbf2820014c62ea529/ci/run_envoy_docker.sh#L5):
```
. ci/envoy_build_sha.sh
```
with:
```
SCRIPT_DIR_PATH="`dirname \"$0\"`"
. "$SCRIPT_DIR_PATH"/envoy_build_sha.sh
```

1. Set the output build dir path:
``` export ENVOY_DOCKER_BUILD_DIR=~/envoyproxy/envoy-get-snis-filter/build```

1. Build the example with docker by running the script `'./ci/do_ci.sh build'` inside docker:
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

## Running

1. Run first instance of envoy
    ```
    envoy -c ./envoy_config.json --v2-config-only
    ```

1. From a new terminal, run a second instance of envoy
    ```
    envoy -c envoy_config2.json --v2-config-only --base-id 2
    ```

1. From a new terminal make a request to the first envoy
    ```
    curl -Ivk https://edition.cnn.com --resolve edition.cnn.com:443:127.0.0.1
    ```


1. In the second envoy's log, one can spot the inner SNI `edition.cnn.com` while the outer SNI is `envoy2.local`
    ```
    [2018-08-23 17:49:26.383][28869][info][filter] get_snis.cc:12] GetSNIsFilter:onNewConnection(), connection requestedServerName: envoy2.local
    [*** LOG ERROR ***] [2018-08-23 17:49:26] [filter] string pointer is null
    [2018-08-23 17:49:26.450][28869][info][filter] get_snis.cc:18] GetSNIsFilter:onData(), connection requestedServerName: envoy2.local
    [2018-08-23 17:49:26.450][28869][info][filter] get_snis.cc:19] GetSNIsFilter:onData(), network level requestedServerName: edition.cnn.com
    [2018-08-23 17:49:26.519][28869][info][filter] get_snis.cc:18] GetSNIsFilter:onData(), connection requestedServerName: envoy2.local
    [2018-08-23 17:49:26.520][28869][info][filter] get_snis.cc:19] GetSNIsFilter:onData(), network level requestedServerName: edition.cnn.com
    [2018-08-23 17:49:26.584][28869][info][filter] get_snis.cc:18] GetSNIsFilter:onData(), connection requestedServerName: envoy2.local
    [2018-08-23 17:49:26.584][28869][info][filter] get_snis.cc:19] GetSNIsFilter:onData(), network level requestedServerName: edition.cnn.com
    [2018-08-23 17:49:26.652][28869][info][filter] get_snis.cc:18] GetSNIsFilter:onData(), connection requestedServerName: envoy2.local
    [2018-08-23 17:49:26.652][28869][info][filter] get_snis.cc:19] GetSNIsFilter:onData(), network level requestedServerName: edition.cnn.com
    [2018-08-23 17:49:26.652][28869][info][filter] get_snis.cc:18] GetSNIsFilter:onData(), connection requestedServerName: envoy2.local
    [2018-08-23 17:49:26.652][28869][info][filter] get_snis.cc:19] GetSNIsFilter:onData(), network level requestedServerName: edition.cnn.com
    [2018-08-23T14:49:26.383Z] "- - -" 0 - 783 6642 333 - "-" "-" "-" "-" "151.101.1.67:443"
    ```


# How it works
The first envoy redirects its traffic to the second envoy which listens on port 15002.
The second envoy sends the traffic to `cnn.com`

