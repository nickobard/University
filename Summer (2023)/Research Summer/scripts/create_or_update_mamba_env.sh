#!/usr/bin/env bash

set -e # stop script execution after failure of any command
set -x # print all executed commands

mamba env create -f environment.yml || mamba env update --file environment.yml --prune
