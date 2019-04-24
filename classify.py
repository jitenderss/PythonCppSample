from PIL import Image
import numpy as np
import sys
import tensorflow as tf

def evaluate(a):
    print "evaluate"
    if not hasattr(sys, 'argv'):
        sys.argv  =  ['']
        print "issue"
    image = Image.open(a)
    image = image.resize([256, 256])
    image_array = np.array(image)
    print image_array
    max_index = np.argmax([1, 2, 32])
    return max_index
