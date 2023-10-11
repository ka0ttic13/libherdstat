#!/bin/bash
source common.sh || exit 1
run_test "LICENSE parsing" \
    "${PORTDIR}/sys-libs/libfoo/libfoo-1.9.ebuild"
indent
