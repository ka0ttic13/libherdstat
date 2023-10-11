#!/bin/bash

if [[ -z "${2}" ]] ; then
    echo "usage: mk_run_lhs_test.sh <src> <headers>"
    exit 1
fi

src=${1}
shift

# generate #include's for each header
for x in "$@" ; do
    includes="${includes}\n#include \"${x}\""
done

# generate insert statements for each test
for x in "$@" ; do
    [[ ${x} == *.hh ]] || continue
    test_name="$(sed -n -e 's|DECLARE_TEST_HANDLER(\(.*\))|\1|p' ${x})"
    inserts="${inserts}\n        tests[\"${x%-test*}\"] = new ${test_name}();"
done

sed \
    -e "s|\@TEST_INCLUDES\@|${includes}|" \
    -e "s|\@TEST_INSERTS\@|${inserts}|" ${src} > ${src%.in}
