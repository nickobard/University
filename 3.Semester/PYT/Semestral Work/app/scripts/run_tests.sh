#!/usr/bin/env bash

set -e  # stop script execution after failure of any command
set -x  # print all executed commands

cd tests
pytest