import pygame as pg
import sys
import time

# Initialize Pygame and set up the screen
pg.init()
WIDTH, HEIGHT = 400, 500
screen = pg.display.set_mode((WIDTH, HEIGHT))
pg.display.set_caption("Tic Tac Toe")
clock = pg.time.Clock()

# Constants for game design
LINE_COLOR = (0, 0, 0)
WIN_LINE_COLOR = (255, 0, 0)
BACKGROUND = (255, 255, 255)
GRID_POS = (50, 50)
CELL_SIZE = 100
STATUS_BAR_HEIGHT = 100
FONT = pg.font.Font(None, 40)

# Game variables
grid = [[None] * 3 for _ in range(3)]
current_player = 'X'
game_over = False
winner = None
def game_initiating_window():

    """initializes game window"""

    pg.display.update()

    time.sleep(3)

    screen.fill(BACKGROUND)

    pg.draw.line(screen, LINE_COLOR, (WIDTH / 3, 0), (WIDTH / 3, HEIGHT), 7)

    pg.draw.line(screen, LINE_COLOR, (WIDTH / 3 * 2, 0), (WIDTH / 3 * 2, HEIGHT), 7)

    pg.draw.line(screen, LINE_COLOR, (0, HEIGHT / 3), (WIDTH, HEIGHT / 3), 7)

    pg.draw.line(screen, LINE_COLOR, (0, HEIGHT / 3 * 2), (WIDTH, HEIGHT / 3 * 2), 7)

    draw_status()



def draw_x(col, row):
    """Draws an X at the specified column and row"""
    base_x = GRID_POS[0] + col * CELL_SIZE
    base_y = GRID_POS[1] + row * CELL_SIZE
    pg.draw.line(screen, LINE_COLOR, (base_x + 20, base_y + 20),
                 (base_x + CELL_SIZE - 20, base_y + CELL_SIZE - 20), 5)
    pg.draw.line(screen, LINE_COLOR, (base_x + CELL_SIZE - 20, base_y + 20),
                 (base_x + 20, base_y + CELL_SIZE - 20), 5)

def draw_o(col, row):
    """Draws an O at the specified column and row"""
    center_x = GRID_POS[0] + col * CELL_SIZE + CELL_SIZE // 2
    center_y = GRID_POS[1] + row * CELL_SIZE + CELL_SIZE // 2
    pg.draw.circle(screen, LINE_COLOR, (center_x, center_y), 40, 5)

def check_win():
    """Checks the grid for a winning combination"""
    global game_over, winner
    # Check rows, columns and diagonals for a winner
    lines = [
        # Horizontal
        [(0, 0), (0, 1), (0, 2)],
        [(1, 0), (1, 1), (1, 2)],
        [(2, 0), (2, 1), (2, 2)],
        # Vertical
        [(0, 0), (1, 0), (2, 0)],
        [(0, 1), (1, 1), (2, 1)],
        [(0, 2), (1, 2), (2, 2)],
        # Diagonal
        [(0, 0), (1, 1), (2, 2)],
        [(0, 2), (1, 1), (2, 0)]
    ]
    for line in lines:
        if all(grid[row][col] == current_player for col, row in line):
            winner = current_player
            game_over = True
            highlight_line(line)
            break

def highlight_line(line):
    """Highlights the winning line"""
    start_pos = (GRID_POS[0] + line[0][1] * CELL_SIZE + CELL_SIZE // 2,
                 GRID_POS[1] + line[0][0] * CELL_SIZE + CELL_SIZE // 2)
    end_pos = (GRID_POS[0] + line[-1][1] * CELL_SIZE + CELL_SIZE // 2,
               GRID_POS[1] + line[-1][0] * CELL_SIZE + CELL_SIZE // 2)
    pg.draw.line(screen, WIN_LINE_COLOR, start_pos, end_pos, 10)

def draw_status():
    """Draws the status bar at the bottom of the screen"""
    status_bar = pg.Rect(0, HEIGHT - STATUS_BAR_HEIGHT, WIDTH, STATUS_BAR_HEIGHT)
    pg.draw.rect(screen, (0, 0, 0), status_bar)
    if game_over:
        if winner:
            text = f"{winner} wins!"
        else:
            text = "It's a draw!"
    else:
        text = f"{current_player}'s turn"
    text_surf = FONT.render(text, True, (255, 255, 255))
    text_rect = text_surf.get_rect(center=(WIDTH // 2, HEIGHT - STATUS_BAR_HEIGHT // 2))
    screen.blit(text_surf, text_rect)

def handle_click(pos):
    """Handles mouse clicks to place X or O in the grid"""
    if game_over:
        return
    col = (pos[0] - GRID_POS[0]) // CELL_SIZE
    row = (pos[1] - GRID_POS[1]) // CELL_SIZE
    if 0 <= col < 3 and 0 <= row < 3 and grid[row][col] is None:
        grid[row][col] = current_player
        check_win()
        if not game_over:
            switch_player()

def switch_player():
    """Switches the player from X to O or O to X"""
    global current_player
    current_player = 'O' if current_player == 'X' else 'X'

def reset_game():
    """Resets the game to the initial state"""
    global grid, game_over, winner, current_player
    grid = [[None] * 3 for _ in range(3)]
    game_over = False
    winner = None
    current_player = 'X'
    draw_grid()
    draw_status()

# Main game loop
draw_grid()
draw_status()
running = True
while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False
        elif event.type == pg.MOUSEBUTTONDOWN and not game_over:
            handle_click(event.pos)
        elif event.type == pg.KEYDOWN and event.key == pg.K_r:
            reset_game()

    pg.display.flip()
    clock.tick(60)

pg.quit()
