import pytest
import subprocess
import uuid
import os
import itertools

def test_test_01():

    subprocess.check_call(
        ['/home/v.halavachenka/work/vicg42-github/microchip-fpga/hls/test-01/run-test.sh'])

def test_test_02():

    subprocess.check_call(
        ['/home/v.halavachenka/work/vicg42-github/microchip-fpga/hls/test-02/run-test.sh'])
