#!/bin/bash
ls -d1 src/* inc/* | grep -E "(.c|.h)$" | xargs wc
