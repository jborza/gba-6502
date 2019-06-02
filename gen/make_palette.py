palette = ["#000000", "#ffffff", "#880000", "#aaffee",
      "#cc44cc", "#00cc55", "#0000aa", "#eeee77",
      "#dd8855", "#664400", "#ff7777", "#333333",
      "#777777", "#aaff66", "#0088ff", "#bbbbbb"]

i = 0
for r,g,b in [(int(color[1:3],16), int(color[3:5],16), int (color[5:7],16)) for color in palette]:
    #gba_color = (((red >> 3) & 31) | (((green >> 3) & 31) << 5) | (((blue >> 3) & 31) << 10))
    #print(r,g,b)
    gba_color = (((r >> 3) & 31) | (((g >> 3) & 31) << 5) | (((b >> 3) & 31) << 10))
    #print(hex(gba_color))
    print(f'palette[{i}] = {hex(gba_color)};')
    i = i+1