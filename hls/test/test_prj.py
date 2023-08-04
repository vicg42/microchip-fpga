import pytest
import subprocess
import uuid
import os
import itertools

def test_prj_alpha_blend():
    subprocess.check_call(
        ['../prj-alpha_blend/build-shls.sh',
        "-d",
        "%s" % (os.path.abspath("../prj-alpha_blend"))])

def test_prj_axi_width_convert():
    subprocess.check_call(
        ['../prj-axi-width-convert/build-shls.sh',
        "-d",
        "%s" % (os.path.abspath("../prj-axi-width-convert"))])

def test_prj_canny():
    result = subprocess.check_call(
        ['../prj-canny/build-shls.sh',
        "-d",
        "%s" % (os.path.abspath("../prj-canny"))])
    assert result == 0, "error"

# def test_prj_canny_fifo_switch():
#     subprocess.check_call(
#         ['../prj-canny-fifo-switch/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-canny-fifo-switch"))])

# def test_prj_gaussian_fifo_pipelined():
#     subprocess.check_call(
#         ['../prj-gaussian-fifo-pipelined/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-gaussian-fifo-pipelined"))])

# def test_prj_gaussian_memory_interface():
#     subprocess.check_call(
#         ['../prj-gaussian-memory-interface/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-gaussian-memory-interface"))])

# def test_prj_gaussian_memory_interface_pipelined():
#     subprocess.check_call(
#         ['../prj-gaussian-memory-interface-pipelined/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-gaussian-memory-interface-pipelined"))])

# def test_prj_pipeline_hazards():
#     subprocess.check_call(
#         ['../prj-pipeline-hazards/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-pipeline-hazards"))])

# def test_prj_rgb2ycbcr():
#     subprocess.check_call(
#         ['../prj-rgb2ycbcr/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-rgb2ycbcr"))])

# def test_prj_simple():
#     subprocess.check_call(
#         ['../prj-simple/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-simple"))])

# def test_prj_sobel():
#     subprocess.check_call(
#         ['../prj-sobel/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-sobel"))])

# def test_prj_ycbcr2rgb():
#     subprocess.check_call(
#         ['../prj-ycbcr2rgb/build-shls.sh',
#         "-d",
#         "%s" % (os.path.abspath("../prj-ycbcr2rgb"))])