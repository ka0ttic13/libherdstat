#!/bin/bash
source common.sh || exit 1
run_test "Vars class" \
    "${PORTDIR}/app-misc/foo/foo-1.10.20050629-r1.ebuild" || exit 1
indent
