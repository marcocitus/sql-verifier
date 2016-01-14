#!/bin/bash
# 
# This script assumes distributed tables named s1, s2, s3, s4
# and local tables l1, l2, l3, l4 exist.
#
# Run with ./generate-joins | xargs -d '\n' -n 1 ./compare.sh 

LOCAL_QUERY=${1//table/l}
DIST_QUERY=${1//table/s}

LOCAL_OUTPUT=$(mktemp)
DIST_OUTPUT=$(mktemp)

psql -c "$DIST_QUERY" > $DIST_OUTPUT 2>&1
RESULT=$?

if [ "$RESULT" = "0" ] ; then
	echo "${DIST_QUERY}"
	psql -c "$LOCAL_QUERY" > $LOCAL_OUTPUT 2>&1
	diff "${LOCAL_OUTPUT}" "${DIST_OUTPUT}"
fi

rm -f "${LOCAL_OUTPUT}" "${DIST_OUTPUT}"
