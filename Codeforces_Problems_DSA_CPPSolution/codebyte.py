class Solution:
    def _init_(self):
        self.grid = []
        self.h = 0
        self.w = 0

    def dfs(self, x, y, visited):
        if x < 0 or x >= self.h or y < 0 or y >= self.w or self.grid[x][y] == 0 or visited[x][y]:
            return 0
        visited[x][y] = True
        size = 1
        for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            size += self.dfs(x + dx, y + dy, visited)
        return size

    def largest_connected_component(self):
        visited = [[False] * self.w for _ in range(self.h)]
        max_size = 0
        for i in range(self.h):
            for j in range(self.w):
                if self.grid[i][j] == 1 and not visited[i][j]:
                    max_size = max(max_size, self.dfs(i, j, visited))
        return max_size

    def max_connected_after_fill(self, h, w, grid):
        self.h, self.w, self.grid = h, w, [row[:] for row in grid]
        max_size = self.largest_connected_component()


        for i in range(h):
            original_row = self.grid[i][:]
            self.grid[i] = [1] * w
            max_size = max(max_size, self.largest_connected_component())
            self.grid[i] = original_row

        
        for j in range(w):
            original_column = [self.grid[i][j] for i in range(h)]
            for i in range(h):
                self.grid[i][j] = 1
            max_size = max(max_size, self.largest_connected_component())
            for i in range(h):
                self.grid[i][j] = original_column[i]

        return max_size

if _name_ == '_main_':
    h, w = 3, 6
    grid =[
    [0, 0, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [1, 0, 0, 0, 1, 0]
]

    solution = Solution()
    result = solution.max_connected_after_fill(h, w, grid)
    print(f'Maximum possible size of the largest connected group: {result}')A