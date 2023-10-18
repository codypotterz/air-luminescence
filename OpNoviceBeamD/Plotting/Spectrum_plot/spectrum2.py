import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)

speed_of_light = 2.99792458 * (10 ** 17)  # nm/s
planck_c = 4.1356677516 * (10 ** -15)  # eV * s

if __name__ == "__main__":
    # Read out
    pixel, energy, count = \
        np.loadtxt("OpN_5p1MeV.ascii", dtype={'names': ('a', 'b', 'c'), 'formats': ('f4', 'f4', 'f4')},
                   skiprows=213, unpack=True
                   )

    pixel1, energy1, count1 = \
        np.loadtxt("OpN_8p3MeV.ascii", dtype={'names': ('a', 'b', 'c'), 'formats': ('f4', 'f4', 'f4')},
                   skiprows=213, unpack=True
                   )

    # eV to nm conversion
    energy_eV = np.array(energy) * 10 ** 6
    wavelength_inverse = np.array(energy_eV) / (speed_of_light * planck_c)
    wavelength = 1 / wavelength_inverse
    fig, ax = plt.subplots(figsize=(20, 11))

    energy_eV1 = np.array(energy1) * 10 ** 6
    wavelength_inverse1 = np.array(energy_eV1) / (speed_of_light * planck_c)
    wavelength1 = 1 / wavelength_inverse1

    ax.plot(wavelength, count, linestyle='solid', lw=1.5, color='black', label='5.1 MeV ')
    ax.plot(wavelength1, count1, linestyle='solid', lw=1.5, color='red', label='8.3 MeV ')
    ax.set(xlabel="Wavelength (nm) ", ylabel="No. of photons", xlim=(200,398), ylim=(0, 9000000))



    ax.xaxis.set_major_locator(MultipleLocator(10))
    ax.xaxis.set_minor_locator(AutoMinorLocator(5))
    plt.title("Radioluminescence Spectrum - MC simulation of alpha beams", fontsize=20)

    ax.grid()
    leg = ax.legend()
    leg.set_draggable(True)
    plt.legend(fontsize=20)
    plt.show()
