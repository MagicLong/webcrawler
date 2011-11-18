#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import struct

TMP_FILE = './tmp_for_curl'
UTF_8_BOM = 0xEFBBBF
UTF_L_BOM = 0xFFFE
UTF_B_BOM = 0xFEFF

if __name__ == '__main__':
    f = open(TMP_FILE, 'r')

    x = struct.pack('I', UTF_8_BOM)
    print x
    x = x[:3]

    y = f.read()
    f.close()

    result = x+y

    f = open(TMP_FILE, 'wb')
    f.write(result)

    f.close()
