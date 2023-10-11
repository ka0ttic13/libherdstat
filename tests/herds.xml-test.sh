#!/bin/bash
source common.sh || exit 1
run_test "herds.xml parsing" \
    "${TEST_DATA}/localstatedir/herds.xml" || exit 1
indent
