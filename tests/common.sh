# pretty if possible
if [[ -f /sbin/functions.sh ]] ; then
    source /sbin/functions.sh
else
    function ebegin() { echo $* ; }
    function eend() { : ; }
fi

[[ -z "${srcdir}" ]] && srcdir=.

get_caller() {
    local x=${1##*/}
    echo ${x%-*}
}

indent() {
    echo -n "   "
}

run_test() {
    local caller="$(get_caller ${0})" name="${1}" opts="${2}" rv=0
    local actual="${srcdir}/actual/${caller}" expected="${srcdir}/expected/${caller}"

    [[ -d ${srcdir}/actual ]] || mkdir ${srcdir}/actual

    ebegin "Testing ${name}"

    if ! ${srcdir}/src/run_lhs_test ${caller} ${opts} &> ${actual} ; then
	# if 5th arg is passed, this is an expected failure
	[[ -z "${5}" ]] && rv=1 || rv=0
    fi

    diff ${expected} ${actual} || rv=1

    eend ${rv}
    return ${rv}
}
