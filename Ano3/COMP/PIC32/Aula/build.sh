#!/usr/bin/env sh
case "$2" in
	"") platformio -f -c emacs run ;;
	* ) platformio -f -c emacs run -t upload ;;
esac
