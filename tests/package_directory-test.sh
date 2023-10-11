#!/bin/bash
source common.sh || exit 1
run_test "PackageDirectory class" \
    "${PORTDIR}/app-misc/foo" || exit 1
indent
