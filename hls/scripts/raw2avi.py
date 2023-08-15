import cv2
import numpy as np
import getopt
import sys
import os
# import matplotlib.pyplot as plt

img1_i_bpp = 2
img1_i_w = 640
img1_i_h = 480

img2_i_bpp = 2
img2_i_w = 640
img2_i_h = 480

usrfile_O = ""
usrfile_I1 = ""
usrfile_I2 = ""

try:
    options, remainder = getopt.gnu_getopt(
        sys.argv[1:],
        "hi:w:q:b:o:f:n:r:e:",
        ["help"
         ])
except getopt.GetoptError as err:
    print('ERROR:', err)
    sys.exit(1)

def help() :
    print('Mandatory option: ')
    print('\t-h --help')
    print('\t-i     <path> - input raw file1')
    print('\t   -b    <byte per pixel> default:%d' % (img1_i_bpp))
    print('\t   -w    <image width> default:%d' % (img1_i_w))
    print('\t   -q    <image height> default:%d' % (img1_i_h))
    print('\t-f     <path> - input raw file2')
    print('\t   -n    <byte per pixel> default:%d' % (img2_i_bpp))
    print('\t   -r    <image width> default:%d' % (img2_i_w))
    print('\t   -e    <image height> default:%d' % (img2_i_h))
    print('\t-o     <path> - output avi file')
    print("usage:")
    print("\t %s -i <path to input raw file> -o  <path to input avi file>" % (os.path.basename(__file__)))
    sys.exit()

for opt, arg in options:
    if opt in ('-i'):
        usrfile_I1 = arg
    elif opt in ('-b'):
        img1_i_bpp = int(arg)
    elif opt in ('-w'):
        img1_i_w = int(arg)
    elif opt in ('-q'):
        img1_i_h = int(arg)
    elif opt in ('-o'):
        usrfile_O = arg
    elif opt in ('-f'):
        usrfile_I2 = arg
    elif opt in ('-n'):
        img2_i_bpp = int(arg)
    elif opt in ('-r'):
        img2_i_w = int(arg)
    elif opt in ('-e'):
        img2_i_h = int(arg)
    elif opt in ('--help'):
        help()

if (not usrfile_I1) or (not usrfile_O):
    print("error: set path to input files.")
    help()

print("input file[0] raw: ", usrfile_I1)
if (img1_i_bpp == 1):
    pixeltype = np.ubyte
else:
    pixeltype = np.ushort
print("img1_i_w: ", img1_i_w)
print("img1_i_h: ", img1_i_h)
img0 = np.fromfile(usrfile_I1, dtype=pixeltype)
img1_i = np.reshape(img0, (-1, img1_i_h, img1_i_w))
img1_i_fr_num, img1_i_h, img1_i_w = img1_i.shape
print("img1_i(frn): ", img1_i_fr_num)

filename_result = os.path.join(usrfile_O)

fourcc = 0
fps = 10

if (usrfile_I2 == ""):
    frame_count = img1_i_fr_num
    fro_h = img1_i_h
    fro_w = img1_i_w
    fro = np.zeros((fro_h, fro_w), dtype=np.uint8)
    video = cv2.VideoWriter(filename_result, fourcc, fps, (fro_w, fro_h), False)
    for nfr in range(frame_count):
        fro[:, :img1_i_w] = cv2.normalize(img1_i[nfr, :, :], np.zeros(0), 0, 255, cv2.NORM_MINMAX).astype(np.uint8)
        video.write(fro)

    video.release()

else:
    print("\n")
    print("input file[1] raw: ", usrfile_I2)
    print("img2_i_w: ", img2_i_w)
    print("img2_i_h: ", img2_i_h)
    img20 = np.fromfile(usrfile_I2, dtype=pixeltype)
    img2_i = np.reshape(img20, (-1, img2_i_h, img2_i_w))
    img2_i_fr_num, img2_i_h, img2_i_w = img2_i.shape
    print("img2_i(frn): ", img2_i_fr_num)

    frame_count = min(img1_i_fr_num,img2_i_fr_num)
    fro_h = max(img1_i_h, img2_i_h)
    fro_w = 2 * max(img1_i_w, img2_i_w)
    fro = np.zeros((fro_h, fro_w), dtype=np.uint8)
    video = cv2.VideoWriter(filename_result, fourcc, fps, (fro_w, fro_h), False)
    print("\n")
    print("output file: ", frame_count, fro_h, fro_w)
    for nfr in range(frame_count):
        img1_i_norm = cv2.normalize(img1_i[nfr, :, :], np.zeros(0), 0, 255, cv2.NORM_MINMAX).astype(np.uint8)
        img2_i_norm = cv2.normalize(img2_i[nfr, :, :], np.zeros(0), 0, 255, cv2.NORM_MINMAX).astype(np.uint8)
        for y in range(fro_h):
            fro[y, :img1_i_w] = img1_i_norm[y, :]
            if (y<img2_i_h):
                fro[y, img1_i_w:img1_i_w+img2_i_w] = img2_i_norm[y, :]
        video.write(fro)
    video.release()

print("output file: ", usrfile_O)
