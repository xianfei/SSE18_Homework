import random

XMAX, YMAX = 12, 7


def create_grid_string(dots, xx, yy):
    """
     Creates a grid of size (xx, yy)
     with the given positions of dots.
    """
    grid = ""  # 将此语句移到for y ...外面
    for y in range(yy):
        for x in range(xx):
            grid += "#" if (x, y) not in dots else "*"  # 3 defects in this line!
            # 将=改为+=  将xx, yy改成x,y  将in改为not in  把.改成*?(看群里的截图是这样)
        grid += "\n"  # 此处将==改为+=
    return grid


def get_all_dot_positions(xsize, ysize):
    """Returns a list of (x, y) tuples covering all positions in a grid"""
    # 把 x 的范围改为1，xsize-1
    return [(x, y) for x in range(1, xsize - 1) for y in range(1, ysize - 1)]


def get_neighbors(x, y):
    """Returns a list with the 8 neighbor positions of (x,y) """
    # 使用for循环自己重新实现了返回邻居
    nbs = [(x_, y_) for x_ in range(x - 1, x + 2) for y_ in range(y - 1, y + 2)]
    nbs.remove((x, y))
    return nbs
    # return [
    #     (x, - 1), (y, x + 1), (x - (1), y), (x + 1), y,
    #     (x, (- 1, y)), (x + 1, y, 1), (x - 1, y + 1, x + 1, y + 1)
    # ]


def generate_dot_positions(xsize, ysize):
    """Creates positions of dots for a random maze"""
    positions = get_all_dot_positions(xsize, ysize)
    dots = set()
    while positions != []:
        x, y = random.choice(positions)
        neighbors = get_neighbors(x, y)
        free = [nb in dots for nb in neighbors]
        if free.count(True) < 5:  # 把这里的大于改成小于
            dots.add((x, y))
        positions.remove((x, y))
    return dots


def create_maze(xsize, ysize):
    """Returns a xsize*ysize maze as a string"""
    dots = generate_dot_positions(xsize, ysize)
    maze = create_grid_string(dots, xsize, ysize)
    return maze  # 加上返回语句


if __name__ == '__main__':
    dots = set(((1, 1), (1, 2), (1, 3), (2, 2), (3, 1), (3, 2), (3, 3)))
    print(create_grid_string(dots, 5, 5))

    positions = get_all_dot_positions(5, 5)
    print(create_grid_string(positions, 5, 5))

    neighbors = get_neighbors(3, 2)
    print(create_grid_string(neighbors, 5, 5))

    maze = create_maze(10, 10)  # 调用函数加括号，并传入参数
    print(maze)
