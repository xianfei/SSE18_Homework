from pygame import image, Surface
# from load_tiles import load_tiles, get_tile_rect, SIZE
from test1 import load_tiles, get_tile_rect, SIZE  # 改成从第一次作业导入
# from generate_maze import create_maze
from test2 import create_maze  # 改成从第二次作业导入


def parse_grid(data):
    """Parses the string representation into a nested list"""
    return data.strip().split('\n')


def draw_grid(data, tile_img, tiles):
    """Returns an image of a tile-based grid"""
    xs = len(data[0]) * SIZE
    ys = len(data) * SIZE
    img = Surface((xs, ys))
    for y, row in enumerate(data):
        for x, char in enumerate(row):
            rect = get_tile_rect(x, y)  # 把 xs ys 改为 x y
            if char == '*': char = '.'  # 把*改成.（不确定 第一次输出全是小人 看输出示例好像应该是这样改）
            img.blit(tile_img, rect, tiles[char])  # 交换 rect 和 tiles[char] 的位置
    return img  # 删除一个tab


if __name__ == '__main__':
    tile_img, tiles = load_tiles()
    level = create_maze(12, 7)
    level = parse_grid(level)
    maze = draw_grid(level, tile_img, tiles)
    image.save(maze, 'maze.png')
