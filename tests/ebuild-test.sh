#!/bin/bash
source common.sh || exit 1
run_test "ebuild parsing" \
    "${PORTDIR}/sys-libs/libfoo/libfoo-1.9.ebuild" || exit 1
indent
