#!/usr/bin/env sh
upsearch () {
    (test / == "$PWD" || test -e "$1") && return || cd .. && upsearch "$1"
}

cd $(dirname "$1")
upsearch "platformio.ini"

case "$2" in
	"") platformio -f -c emacs run ;;
	* ) platformio -f -c emacs run -t upload ;;
esac
