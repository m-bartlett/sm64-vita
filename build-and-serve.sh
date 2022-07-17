#!/usr/bin/env bash
source vitaup
set -x
make TARGET_VITA=1 vpk -j4 && vita-serve build/us_vita/sm64.us.vpk
