import pytest
import subprocess
import uuid
import os
import itertools

def test_prj01():
    subprocess.check_call(
        ['../prj-01/run-test.sh',
        "-d",
        "%s" % (os.path.abspath("../prj-01"))])

def test_prj02():
    subprocess.check_call(
        ['../prj-02/run-test.sh',
        "-d",
        "%s" % (os.path.abspath("../prj-02"))])
