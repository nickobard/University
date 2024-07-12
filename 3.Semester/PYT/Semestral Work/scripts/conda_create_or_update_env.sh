#!/usr/bin/env bash

set -e  # stop script execution after failure of any command
set -x  # print all executed commands


conda env create -f environment.yml || conda env update --file environment.yml --prune