#!/bin/bash
source common.sh || exit 1
run_test "File/Directory classes" \
    "${PORTDIR}/app-misc/foo" || exit 1
indent
