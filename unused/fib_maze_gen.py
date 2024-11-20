import numpy as np

def generate_fibonacci_maze(size):
    # Initialize maze grid (all ones)
    maze = np.ones((size, size), dtype=int)
    
    # Fibonacci sequence (first few numbers)
    fib = [1, 1]
    while fib[-1] < size:
        fib.append(fib[-1] + fib[-2])
    
    # Start from the center
    x, y = size // 2, size // 2
    
    # Directions: right, down, left, up (clockwise spiral)
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    direction_index = 0  # Start moving to the right
    fib_index = 0       # Start with the first Fibonacci number
    
    # Place paths based on Fibonacci sequence (using 0 for paths)
    while fib_index < len(fib):
        length = fib[fib_index]
        dx, dy = directions[direction_index]
        
        # Create the path (set to 0)
        for _ in range(length):
            if 0 <= x < size and 0 <= y < size:
                maze[x, y] = 0  # Mark the path as 0
            x, y = x + dx, y + dy
        
        # Move to the next direction (right, down, left, up)
        direction_index = (direction_index + 1) % 4
        fib_index += 1
    
    return maze

# Generate a 100x100 Fibonacci maze
maze = generate_fibonacci_maze(1000)

# Print the maze
for row in maze:
    print("".join(str(cell) for cell in row))
