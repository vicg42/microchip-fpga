import cv2
import numpy as np
import getopt
import sys
import os

raw_nframe = 100

usrfile_I = ""
usrfile_O = ""

try:
    options, remainder = getopt.gnu_getopt(
        sys.argv[1:],
        "hi:o:n:",
        ["help"
         ])
except getopt.GetoptError as err:
    print('ERROR:', err)
    sys.exit(1)

def help() :
    print('Mandatory option: ')
    print('\t-h  --help')
    print('\t-i          <path to input image file>')
    print('\t-o          <path to output raw file> ')
    print('\t-n          number of frame raw file. default:', raw_nframe)
    print("usage:")
    print("\t %s -i <path to file> -o <path to file>" % (os.path.basename(__file__)))
    sys.exit()

for opt, arg in options:
    if opt in ('-i'):
        usrfile_I = arg
    elif opt in ('-o'):
        usrfile_O = arg
    elif opt in ('-n'):
        raw_nframe = int(arg, 10)
    elif opt in ('-h', '--help'):
        help()

if (not usrfile_I) or (not usrfile_O):
    print("error: set path to input image files.")
    help()

print ("image(input): ", usrfile_I)
print ("raw(output): ", usrfile_O)
print ("nframe: ", raw_nframe)

img_y = cv2.imread(usrfile_I, -1) #cv2.IMREAD_COLOR)
print ("input image: ", img_y.shape)
print ("input image(ppb): ", img_y.dtype)
img_h = img_y.shape[0]
img_w = img_y.shape[1]
if (img_y.dtype == 'uint16'):
    PIX_MAX_VALUE = 65535
else:
    PIX_MAX_VALUE = 255
print ("PIX_MAX_VALUE: ", PIX_MAX_VALUE)


usrfile_O_location = os.path.dirname(usrfile_O)
usrfile_O_name = os.path.basename(usrfile_O)
usrfile_O_name, usrfile_O_ext = os.path.splitext(usrfile_O_name)

file_save = os.path.join(usrfile_O_location + '/' + usrfile_O_name + '.raw')
frame_out = []
for i in range(raw_nframe):
    frame_out.append(img_y)
RawDataOut = np.array(frame_out)
RawDataOut = RawDataOut.astype('uint16')
RawDataOut.tofile(file_save)
print("create raw file (BPP=%d, Nframe=%d, W=%d, H=%d): %s" % \
    (RawDataOut.itemsize,RawDataOut.shape[0], RawDataOut.shape[2], RawDataOut.shape[1], file_save))
