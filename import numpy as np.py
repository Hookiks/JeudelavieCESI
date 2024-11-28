import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Définir les états des cellules
ON = 255
OFF = 0
vals = [ON, OFF]

# Initialiser la grille
N = 100
grid = np.random.choice(vals, N*N, p=[0.2, 0.8]).reshape(N, N)

def update(frameNum, img, grid, N):
    newGrid = grid.copy()
    for i in range(N):
        for j in range(N):
            # Calculer le nombre de voisins vivants
            total = int((grid[i, (j-1)%N] + grid[i, (j+1)%N] +
                         grid[(i-1)%N, j] + grid[(i+1)%N, j] +
                         grid[(i-1)%N, (j-1)%N] + grid[(i-1)%N, (j+1)%N] +
                         grid[(i+1)%N, (j-1)%N] + grid[(i+1)%N, (j+1)%N])/255)
            # Appliquer les règles du jeu de la vie
            if grid[i, j] == ON:
                if (total < 2) or (total > 3):
                    newGrid[i, j] = OFF
            else:
                if total == 3:
                    newGrid[i, j] = ON
    img.set_data(newGrid)
    grid[:] = newGrid
    return img

# Configurer l'animation
fig, ax = plt.subplots()
img = ax.imshow(grid, interpolation='nearest')
ani = animation.FuncAnimation(fig, update, fargs=(img, grid, N),
                              frames=10, interval=50, save_count=50)

plt.show()