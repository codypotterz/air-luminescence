"""
Geant4 5.5 MeV alpha beam
"""

import numpy as np
from matplotlib.axes import Axes
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import scipy.ndimage as sn
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)


def load_data(filename: str) -> np.ndarray:
    tally = np.loadtxt(filename, dtype=int, delimiter=',', usecols=2, skiprows=4)
    tally = tally.reshape(120, 180)
    tally = sn.rotate(tally, 90, reshape=True)
    return tally


if __name__ == "__main__":
    tally = load_data("RadioluminescenceDistribution.txt")
    plt_s = plt.subplots(figsize=(15, 15))
    ax: Axes = plt_s[1]

    im = ax.imshow(tally, cmap='magma', extent=(0, 120, 0, 180,))

    divider = make_axes_locatable(ax)
    cax = divider.append_axes("right", size = "2%", pad = 0.0)

    ax.set(xlabel="X axis / mm", ylabel="Y axis / mm")
    ax.set_title('Distribution of radioluminescence photons emitted from Am-241 source', pad=20)

    cbar = plt.colorbar(im, cax=cax)
    cbar.set_label("Intensity (arb. units)", rotation = 90)
    ax.xaxis.set_major_locator(MultipleLocator(10))
    ax.xaxis.set_minor_locator(AutoMinorLocator(5))
    plt.show()
