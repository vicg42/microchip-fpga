import pytest
import subprocess
import uuid
import os
import itertools

def test_vicg_hls_test_01():

    subprocess.check_call(
        ['/home/v.halavachenka/work/microchip-hls/vicg-hls-test-01/run-test.sh'])

def test_vicg_hls_test_02():

    subprocess.check_call(
        ['/home/v.halavachenka/work/microchip-hls/vicg-hls-test-02/run-test.sh'])
