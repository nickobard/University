#!/bin/bash
#
# progT - Prog Tinker
#
#   This script assembles multiple source header and implementaion files
#   into one, that is acceptable by ProgTest.
#
# HOW TO USE:
#
#   Put delimiters into your code, so progTinker knows what to throw out
#   and what to assemble into one source file.
#   The progtest.cpp source file will be tinkered (generated).
#
# DEPENDENCIES:
#
#   Using with Makefile progTinker expects src.cpp file form
#   the ProgTest in the ./assets/ directory.
#   Otherwise it should be put with the other source files
#   if you want to run it using ./progt.sh
#
# DELIMITERS:
#
#   PROGT_BEGIN
#
#     All lines here will be deleted, and won't be
#     assembled into one source file.
#
#     Using these delimiters specify what pieces of code should
#     not be in the progt.cpp file.
#
#   PROGT_END
#
#   PROGT_INSERT
#     starting from this point all source files will be
#     inserted, placed between text above and
#     under of the PROGT_INSERT delimiter.
#     

rm -f progtest.cpp
sed '/PROGT_BEGIN/,/PROGT_END/d' assets/src.cpp          >> tmp
sed '1,/PROGT_INSERT/!d'         tmp | head -n -1 >> progtmp
sed '/PROGT_BEGIN/,/PROGT_END/d' *.h *.cpp  >> progtmp
sed '1,/PROGT_INSERT/ d'         tmp              >> progtmp
mv progtmp progtest.cpp
rm -f tmp