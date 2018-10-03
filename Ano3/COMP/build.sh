#!/usr/bin/env sh
cd $(dirname "$1")
case "$2" in
	"" ) platformio run ;;
	"u") platformio run -t upload ;;
esac
