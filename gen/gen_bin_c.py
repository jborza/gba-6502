import sys

input_name = sys.argv[1]

hexes = []
with open(input_name,'rb') as f:
    while 1:
        byte = f.read(1)
        if byte == b'':
            break
        val = ord(byte)
        hexval = hex(val)
        hexes.append(hexval)
        #print(byte)
        #print(ord(byte))
#print(hexes)
print(','.join(hexes))