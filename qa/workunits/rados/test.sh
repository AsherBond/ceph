#!/bin/sh -e

test_rados_api_aio
test_rados_api_io
test_rados_api_list
test_rados_api_misc
test_rados_api_pool
test_rados_api_snapshots
test_rados_api_stat
test_rados_api_watch_notify

testrados_list_parallel
testrados_open_pools_parallel
testrados_delete_pools_parallel
testrados_watch_notify

exit 0
