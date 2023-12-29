#!/bin/bash

createdir() {
# $1 = user
# $2 = group
# $3 = permissions (octal)
# $4 = path to directory
    [ "$VERBOSE" = "yes" ] && OPT="-c"
    [ -d "$4" ] || mkdir -p "$4"
    chown $OPT -h "$1:$2" "$4"
    chmod $OPT "$3" "$4"
}

missingstatoverride () {
    echo "$0: You are missing a dpkg-statoverride on $1.  Add it." >&2
    exit 1
}

fixdirs () {
    dir=$(dpkg-statoverride --list /run/cyrus) \
        || missingstatoverride /run/cyrus
    [ -z "$dir" ] \
        || createdir $dir
    dir=$(dpkg-statoverride --list /run/cyrus/socket) \
        || missingstatoverride /run/cyrus/socket
    [ -z "$dir" ] \
        || createdir $dir
}

dir=$(dpkg-statoverride --list /var/run/cyrus)
[ -z "$dir" ] || createdir $dir
