#!/bin/bash
source common.sh || exit 1
run_test "metadata.xml parsing" \
    "${PORTDIR}/app-misc/foo/metadata.xml" || exit 1
indent
