import pytest
import subprocess
import uuid
import os
import itertools

def test_prj01():
    subprocess.check_call(
        ['../prj-canny/run-shls.sh',
        "-d",
        "%s" % (os.path.abspath("../prj-canny"))])

def test_prj02():
    subprocess.check_call(
        ['../prj-sobel/run-shls.sh',
        "-d",
        "%s" % (os.path.abspath("../prj-sobel"))])
