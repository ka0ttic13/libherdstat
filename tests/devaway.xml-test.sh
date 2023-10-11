#!/bin/bash
source common.sh || exit 1
run_test "devaway.xml parsing" \
    "${TEST_DATA}/localstatedir/devaway.xml" || exit 1
indent
