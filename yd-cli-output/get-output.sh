#!/bin/bash -e

function get_output()
{
    export LANG=$1
    yandex-disk status > status-$LANG.out
    yandex-disk --help > help-$LANG.out
}

get_output "en_US.UTF-8"
get_output "ru_RU.utf8"

