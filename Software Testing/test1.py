# This code contains at least 9 defects .
# Try to fix them all based on the error messages。
import pygame
from pygame import image, Rect, Surface

TILE_POSITIONS = [
    ('#', 0, 0),  # wall
    (' ', 0, 1),  # floor
    ('.', 2, 0),  # dot
    ('*', 3, 0),  # player
]
SIZE = 32


# image = 'tiles.xpm'
def get_tile_rect(x, y):
    return Rect(x * SIZE, y * SIZE, SIZE, SIZE)


def load_tiles():
    tiles = {}
    tile_img = image.load('tiles.xpm')
    for symbol, x, y in TILE_POSITIONS:
        rect = Rect(x * SIZE, y * SIZE, SIZE, SIZE)
        tiles[symbol] = rect
    return tile_img, tiles


if __name__ == '__main__':
    tile_img, tiles = load_tiles()
    m = Surface((32 * 4, 32))
    m.blit(tile_img, get_tile_rect(0, 0), tiles['#'])
    m.blit(tile_img, get_tile_rect(1, 0), tiles[' '])
    m.blit(tile_img, get_tile_rect(2, 0), tiles['*'])
    m.blit(tile_img, get_tile_rect(3, 0), tiles['.'])
    image.save(m, 'tile_combo.png')


# Optional exercise:
# make the print statement below work by modifying the class
# so that it prints the char attribute

class Tile:
    def __init__(self, achar, x, y):
        self.char = achar


t = Tile('#', 0, 0)
print(t.char)
