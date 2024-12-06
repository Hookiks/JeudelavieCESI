import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class GameOfLife:
    ON = 255
    OFF = 0
    vals = [ON, OFF]

    def __init__(self, N=100, p=[0.2, 0.8]):
        self.N = N
        self.grid = np.random.choice(self.vals, N*N, p=p).reshape(N, N)

    def update(self, frameNum, img):
        newGrid = self.grid.copy()
        for i in range(self.N):
            for j in range(self.N):
                total = int((self.grid[i, (j-1)%self.N] + self.grid[i, (j+1)%self.N] +
                             self.grid[(i-1)%self.N, j] + self.grid[(i+1)%self.N, j] +
                             self.grid[(i-1)%self.N, (j-1)%self.N] + self.grid[(i-1)%self.N, (j+1)%self.N] +
                             self.grid[(i+1)%self.N, (j-1)%self.N] + self.grid[(i+1)%self.N, (j+1)%self.N])/255)
                if self.grid[i, j] == self.ON:
                    if (total < 2) or (total > 3):
                        newGrid[i, j] = self.OFF
                else:
                    if total == 3:
                        newGrid[i, j] = self.ON
        img.set_data(newGrid)
        self.grid[:] = newGrid
        return img

    def animate(self):
        fig, ax = plt.subplots()
        img = ax.imshow(self.grid, interpolation='nearest')
        ani = animation.FuncAnimation(fig, self.update, fargs=(img,), frames=10, interval=50, save_count=50)
        plt.show()

if __name__ == "__main__":
    game = GameOfLife(N=100, p=[0.2, 0.8])
    game.animate()