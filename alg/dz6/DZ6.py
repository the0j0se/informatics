import pygame
import random
import math
from queue import PriorityQueue

pygame.init()

WIDTH = 600
GRID_SIZE = 10
CELL_SIZE = WIDTH // GRID_SIZE
WIN = pygame.display.set_mode((WIDTH, WIDTH))
pygame.display.set_caption("Алгоритм A* (Вариант 6)")

RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
PURPLE = (128, 0, 128)
GREY = (128, 128, 128)
TURQUOISE = (64, 224, 208)

MAP_MATRIX = [
    [0, 1, 0, 1, 1, 0, 0, 1, 0, 0],
    [0, 0, 1, 1, 0, 0, 1, 0, 0, 1],
    [0, 1, 0, 0, 1, 1, 0, 0, 0, 1],
    ['S', 0, 0, 1, 0, 0, 0, 1, 0, 1],
    [0, 1, 0, 1, 1, 0, 0, 0, 0, 1],
    [1, 0, 0, 1, 0, 0, 1, 0, 0, 1],
    [1, 0, 0, 1, 0, 1, 0, 0, 0, 1],
    [0, 1, 0, 0, 0, 0, 0, 1, 0, 1],
    [1, 1, 0, 1, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 1, 1, 1, 0, 0, 1, 'E']
]

class Cell:
    def __init__(self, row, col):
        self.row = row
        self.col = col
        self.x = col * CELL_SIZE
        self.y = row * CELL_SIZE
        self.color = WHITE
        self.neighbors = []

    def get_pos(self): return self.row, self.col
    def is_obstacle(self): return self.color == BLACK
    def is_start(self): return self.color == BLUE
    def is_end(self): return self.color == RED
    def reset(self): self.color = WHITE
    def make_start(self): self.color = BLUE
    def make_barrier(self): self.color = BLACK
    def make_end(self): self.color = RED
    def make_closed(self): self.color = TURQUOISE
    def make_open(self): self.color = PURPLE
    def make_path(self): self.color = GREEN

    def draw(self, win):
        pygame.draw.rect(win, self.color, 
                         (self.x, self.y, CELL_SIZE, CELL_SIZE))

    def update_neighbors(self, grid):
        self.neighbors = []
        if self.row < GRID_SIZE - 1:
            if not grid[self.row + 1][self.col].is_obstacle():
                self.neighbors.append(grid[self.row + 1][self.col])
        if self.row > 0:
            if not grid[self.row - 1][self.col].is_obstacle():
                self.neighbors.append(grid[self.row - 1][self.col])
        if self.col < GRID_SIZE - 1:
            if not grid[self.row][self.col + 1].is_obstacle():
                self.neighbors.append(grid[self.row][self.col + 1])
        if self.col > 0:
            if not grid[self.row][self.col - 1].is_obstacle():
                self.neighbors.append(grid[self.row][self.col - 1])

    def __lt__(self, other):
        return False

def h(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

def reconstruct_path(came_from, current, win, grid):
    while current in came_from:
        current = came_from[current]
        current.make_path()
        draw(win, grid)

def a_star_algorithm(win, grid, start, end):
    # count нужен для разрешения коллизий в PriorityQueue, 
    # если f_score у двух клеток одинаковый
    count = 0 
    open_set = PriorityQueue()
    open_set.put((0, count, start)) # В очередь кладем кортеж: (f_score, count, узел)
    
    came_from = {} # Словарь для восстановления итогового пути
    
    # g_score - стоимость пути от старта до текущей клетки
    g_score = {cell: float("inf") for row in grid for cell in row}
    g_score[start] = 0
    
    # f_score = g_score + h (эвристика)
    f_score = {cell: float("inf") for row in grid for cell in row}
    f_score[start] = h(start.get_pos(), end.get_pos())
    
    # Вспомогательное множество для быстрого поиска элементов в очереди
    open_set_hash = {start}
    
    while not open_set.empty():
        # Обработка закрытия окна во время работы алгоритма
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
        
        # Извлекаем вершину n с наименьшим f(n)
        current = open_set.get()[2]
        open_set_hash.remove(current)
        
        # Если текущая вершина - целевая, путь найден
        if current == end:
            reconstruct_path(came_from, end, win, grid)
            start.make_start()
            end.make_end()
            return True
            
        # Проверяем всех соседей текущей клетки
        for neighbor in current.neighbors:
            # Расстояние до соседа всегда равно текущее + 1
            temp_g_score = g_score[current] + 1
            
            # Если найден более короткий путь к соседу
            if temp_g_score < g_score[neighbor]:
                came_from[neighbor] = current
                g_score[neighbor] = temp_g_score
                f_score[neighbor] = temp_g_score + h(neighbor.get_pos(), end.get_pos())
                
                # Если соседа нет в открытом списке, добавляем его
                if neighbor not in open_set_hash:
                    count += 1
                    open_set.put((f_score[neighbor], count, neighbor))
                    open_set_hash.add(neighbor)
                    neighbor.make_open() # Помечаем зеленым/фиолетовым (в очереди)
                    
        draw(win, grid) # Отрисовываем шаг алгоритма
        
        # Перемещаем текущую клетку в закрытый список (отмечаем как посещенную)
        if current != start:
            current.make_closed()
            
    return False # Если очередь пуста, а цель не найдена

def make_grid():
    grid = []
    start_node = None
    end_node = None
    
    for i in range(GRID_SIZE):
        grid.append([])
        for j in range(GRID_SIZE):
            cell = Cell(i, j)
            val = MAP_MATRIX[i][j]
            if val == 1:
                cell.make_barrier()
            elif val == 'S':
                cell.make_start()
                start_node = cell
            elif val == 'E':
                cell.make_end()
                end_node = cell
            grid[i].append(cell)
            
    return grid, start_node, end_node

def draw_grid(win):
    for i in range(GRID_SIZE):
        pygame.draw.line(win, GREY, (0, i * CELL_SIZE), 
                         (WIDTH, i * CELL_SIZE))
        pygame.draw.line(win, GREY, (i * CELL_SIZE, 0), 
                         (i * CELL_SIZE, WIDTH))

def draw(win, grid):
    win.fill(WHITE)
    for row in grid:
        for cell in row:
            cell.draw(win)
    draw_grid(win)
    pygame.display.update()

def generate_random_grid(grid):
    for row in grid:
        for cell in row:
            cell.reset()

    start_row, start_col = random.randint(0, GRID_SIZE-1), random.randint(0, GRID_SIZE-1)
    end_row, end_col = random.randint(0, GRID_SIZE-1), random.randint(0, GRID_SIZE-1)

    while (start_row, start_col) == (end_row, end_col):
        end_row, end_col = random.randint(0, GRID_SIZE-1), random.randint(0, GRID_SIZE-1)

    start = grid[start_row][start_col]
    end = grid[end_row][end_col]

    start.make_start()
    end.make_end()

    obstacle_count = int(GRID_SIZE * GRID_SIZE * 0.2)
    for _ in range(obstacle_count):
        row, col = random.randint(0, GRID_SIZE-1), random.randint(0, GRID_SIZE-1)
        cell = grid[row][col]
        if not cell.is_start() and not cell.is_end():
            cell.make_barrier()

    return start, end

def main():
    """
    Пробел - запуск
    C - очистить
    """
    grid, start, end = make_grid()
    run = True
    
    while run:
        draw(WIN, grid)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE and start and end:
                    for row in grid:
                        for cell in row:
                            cell.update_neighbors(grid)
                    a_star_algorithm(WIN, grid, start, end)
                if event.key == pygame.K_c:
                    grid, start, end = make_grid()
                if event.key == pygame.K_r:
                    start, end = generate_random_grid(grid)
                    
    pygame.quit()

if __name__ == "__main__":
    main()