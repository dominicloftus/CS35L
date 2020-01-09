#!/bin/bash

arr=("/usr/bin/akonadi2xml"
"/usr/bin/berkeley_db47_svc"
"/usr/bin/chgrp"
"/usr/bin/cube-config-backend"
"/usr/bin/diff3"
"/usr/bin/eu-ar"
"/usr/bin/gcc-ranlib"
"/usr/bin/gnatxref"
"/usr/bin/gtester"
"/usr/bin/hugeedit"
"/usr/bin/itweb-settings"
"/usr/bin/kfontview"
"/usr/bin/ldd"
"/usr/bin/lslogins"
"/usr/bin/mockchain"
"/usr/bin/nl-classid-lookup"
"/usr/bin/orc-bugreport"
"/usr/bin/pamtojpeg2k"
"/usr/bin/pcdovtoppm"
"/usr/bin/pinentry"
"/usr/bin/pnmquant"
"/usr/bin/ppmforge"
"/usr/bin/pwmake"
"/usr/bin/rlog"
"/usr/bin/sctp_test"
"/usr/bin/spam"
"/usr/bin/taskset"
"/usr/bin/umask"
"/usr/bin/wrestool"
"/usr/bin/xsetwacom")

for x in "${arr[@]}"
do
    ldd $x
done

