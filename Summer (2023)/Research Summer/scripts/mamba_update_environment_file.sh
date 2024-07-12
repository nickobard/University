#!/usr/bin/env bash
set -e # stop script execution after failure of any command
set -x # print all executed commands

mamba env export --from-history | grep -v "^prefix: " >environment.yml
