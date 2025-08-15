import imageio.v2 as io
import numpy as np

image = io.imread('OuterHeavenTilemap.png')
total_size_x = image.shape[1]
total_size_y = image.shape[0]
print(total_size_x, total_size_y)

individual_sprites = []

for i in range(0, total_size_y, 32):
    for j in range(0, total_size_x, 32):
        individual_sprites.append(image[i:i+32, j:j+32])

for i in range(0, len(individual_sprites)):
    if i == 0:
        row = individual_sprites[i]
    else:
        row = np.concatenate((row, individual_sprites[i]), axis=1)

io.imwrite('OuterHeavenTilemapRow.png', row)