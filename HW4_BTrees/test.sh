#!/bin/bash
rm *.dot
if make test; then
    ./btree-test
    dot -T x11 before.dot & dot -T x11 after.dot
fi
