import cv2
import numpy as np
import getopt
import sys
import os
# import matplotlib.pyplot as plt

usrfile_I = ""
img_i_bpp = 2
img_i_w = 640
img_i_h = 480
img_i_numfr = 0

usrfile_S = ""
disable_plt_show = 0

try:
    options, remainder = getopt.gnu_getopt(
        sys.argv[1:],
        "hzi:w:q:b:f:s:",
        ["help"
         ])
except getopt.GetoptError as err:
    print('ERROR:', err)
    sys.exit(1)

def help() :
    print('Mandatory option: ')
    print('\t-h --help')
    print('\t-i     <path> - input raw file')
    print('\t   -b    <byte per pixel> default:%d' % (img_i_bpp))
    print('\t   -w    <image width> default:%d' % (img_i_w))
    print('\t   -q    <image height> default:%d' % (img_i_h))
    print('\t   -f    <frame number for show> default:%d' % (img_i_numfr))
    print('\t-s     <path> - save image from output raw file')
    print('\t-z  disable plt.show()')
    print("usage:")
    print("\t %s -i <path to input raw file>" % (os.path.basename(__file__)))
    sys.exit()

for opt, arg in options:
    if opt in ('-i'):
        usrfile_I = arg
    elif opt in ('-b'):
        img_i_bpp = int(arg)
    elif opt in ('-w'):
        img_i_w = int(arg)
    elif opt in ('-q'):
        img_i_h = int(arg)
    elif opt in ('-f'):
        img_i_numfr = int(arg)
    elif opt in ('-s'):
        usrfile_S = arg
    elif opt in ('-z'):
        disable_plt_show = 1
    elif opt in ('--help'):
        help()

if (not usrfile_I):
    print("error: set path to input files.")
    help()

if (img_i_bpp == 1):
    pixeltype = 'uint8'
else:
    pixeltype = 'uint16'
img0 = np.fromfile(usrfile_I, dtype=pixeltype)
img_i = np.reshape(img0, (-1, img_i_h, img_i_w))
print("img_i: Nframe, Resolution: ", img_i.shape)

# fig = plt.figure(figsize=(18,6))
# fig_axs_list = []

# fig_axs_0_list = []
# fig_axs_0_list.append(fig.add_subplot(1, 1, 1))
# fig_axs_list.append(fig_axs_0_list)

# fig_axs_list[0][0].set_title('input')
# fig_axs_list[0][0].get_xaxis().set_ticks([])
# fig_axs_list[0][0].get_yaxis().set_ticks([])
# fig_axs_list[0][0].imshow(img_i[img_i_numfr, :, :], cmap='gray') #, vmin=0, vmax=255)

if usrfile_S != "":
    ofile_location = os.path.dirname(usrfile_S)
    ofile_name = os.path.basename(usrfile_S)
    ofile_name, ofile_ext = os.path.splitext(ofile_name)
    file_save = os.path.join(ofile_location + '/' + ofile_name + ofile_ext)
    cv2.imwrite(file_save, img_i[img_i_numfr, :, :])
    print ("save image(output): " + file_save)
    # file_save = os.path.join(ofile_location + '/' + ofile_name + ".raw")
    # img_i[img_i_numfr, :, :].tofile(file_save)
    # print ("save image(output): " + file_save)

# if (disable_plt_show == 0):
#     plt.show()
