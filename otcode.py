import pygame
import sys
import time

pygame.init()

WIDTH, HEIGHT = 400, 500
BOARD_SIZE = 400
CELL_SIZE = BOARD_SIZE // 3
LINE_COLOR = (0, 0, 0)
BG_COLOR = (255, 255, 255)
WIN_LINE_COLOR = (255, 0, 0)
STATUS_BG = (220, 220, 220)
FPS = 30

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Tic Tac Toe")
clock = pygame.time.Clock()

grid = [[None for _ in range(3)] for _ in range(3)]
current_player = "X"
winner = None
draw = False
game_over_time = None

def draw_board():
    screen.fill(BG_COLOR)
    for i in range(1, 3):
        pygame.draw.line(screen, LINE_COLOR, (0, i * CELL_SIZE), (BOARD_SIZE, i * CELL_SIZE), 3)
        pygame.draw.line(screen, LINE_COLOR, (i * CELL_SIZE, 0), (i * CELL_SIZE, BOARD_SIZE), 3)
    pygame.draw.rect(screen, STATUS_BG, (0, BOARD_SIZE, WIDTH, HEIGHT - BOARD_SIZE))
    draw_status()

def draw_status():
    font = pygame.font.SysFont(None, 40)
    if winner:
        status_text = f"{winner} wins!"
    elif draw:
        status_text = "Draw!"
    else:
        status_text = f"{current_player}'s turn"
    text_surface = font.render(status_text, True, (0, 0, 0))
    text_rect = text_surface.get_rect(center=(WIDTH // 2, BOARD_SIZE + (HEIGHT - BOARD_SIZE) // 2))
    pygame.draw.rect(screen, STATUS_BG, (0, BOARD_SIZE, WIDTH, HEIGHT - BOARD_SIZE))
    screen.blit(text_surface, text_rect)

def draw_marks():
    for row in range(3):
        for col in range(3):
            center_x = col * CELL_SIZE + CELL_SIZE // 2
            center_y = row * CELL_SIZE + CELL_SIZE // 2
            if grid[row][col] == "X":
                offset = CELL_SIZE // 3
                start_pos1 = (col * CELL_SIZE + offset, row * CELL_SIZE + offset)
                end_pos1 = (col * CELL_SIZE + CELL_SIZE - offset, row * CELL_SIZE + CELL_SIZE - offset)
                start_pos2 = (col * CELL_SIZE + offset, row * CELL_SIZE + CELL_SIZE - offset)
                end_pos2 = (col * CELL_SIZE + CELL_SIZE - offset, row * CELL_SIZE + offset)
                pygame.draw.line(screen, LINE_COLOR, start_pos1, end_pos1, 4)
                pygame.draw.line(screen, LINE_COLOR, start_pos2, end_pos2, 4)
            elif grid[row][col] == "O":
                radius = CELL_SIZE // 3
                pygame.draw.circle(screen, LINE_COLOR, (center_x, center_y), radius, 4)

def check_win():
    global winner, draw
    # Check rows
    for row in range(3):
        if grid[row][0] == grid[row][1] == grid[row][2] and grid[row][0] is not None:
            winner = grid[row][0]
            return ("row", row)
    # Check columns
    for col in range(3):
        if grid[0][col] == grid[1][col] == grid[2][col] and grid[0][col] is not None:
            winner = grid[0][col]
            return ("col", col)
    # Check main diagonal
    if grid[0][0] == grid[1][1] == grid[2][2] and grid[0][0] is not None:
        winner = grid[0][0]
        return ("diag", 0)
    # Check anti-diagonal
    if grid[0][2] == grid[1][1] == grid[2][0] and grid[0][2] is not None:
        winner = grid[0][2]
        return ("anti", 0)
    # Check for draw
    if all(all(cell is not None for cell in row) for row in grid):
        draw = True
    return None

def draw_win_line(win_info):
    if win_info is None:
        return
    win_type, index = win_info
    if win_type == "row":
        y = index * CELL_SIZE + CELL_SIZE // 2
        start = (20, y)
        end = (BOARD_SIZE - 20, y)
    elif win_type == "col":
        x = index * CELL_SIZE + CELL_SIZE // 2
        start = (x, 20)
        end = (x, BOARD_SIZE - 20)
    elif win_type == "diag":
        start = (20, 20)
        end = (BOARD_SIZE - 20, BOARD_SIZE - 20)
    elif win_type == "anti":
        start = (BOARD_SIZE - 20, 20)
        end = (20, BOARD_SIZE - 20)
    pygame.draw.line(screen, WIN_LINE_COLOR, start, end, 5)

def reset_game():
    global grid, current_player, winner, draw, game_over_time
    grid = [[None for _ in range(3)] for _ in range(3)]
    current_player = "X"
    winner = None
    draw = False
    game_over_time = None
    draw_board()
    draw_marks()
    pygame.display.update()

def handle_click(pos):
    global current_player
    x, y = pos
    if x >= BOARD_SIZE or y >= BOARD_SIZE:
        return
    col = x // CELL_SIZE
    row = y // CELL_SIZE
    if grid[row][col] is None:
        grid[row][col] = current_player
        current_player = "O" if current_player == "X" else "X"

draw_board()
pygame.display.update()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.MOUSEBUTTONDOWN and winner is None and not draw:
            handle_click(pygame.mouse.get_pos())
    draw_board()
    draw_marks()
    win_info = check_win()
    if winner or draw:
        draw_win_line(win_info)
        draw_status()
        if game_over_time is None:
            game_over_time = time.time()
        elif time.time() - game_over_time >= 10:
            reset_game()
    pygame.display.update()
    clock.tick(FPS)
