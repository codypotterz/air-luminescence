import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)

speed_of_light = 2.99792458 * (10 ** 17)  # nm/s
planck_c = 4.1356677516 * (10 ** -15)  # eV * s

if __name__ == "__main__":
    # Read out
    wavelength2, spectral_irradiance= \
        np.loadtxt("M21_N2NO.dat", dtype={'names': ('a', 'b'), 'formats': ('f4', 'f4')},
                   skiprows=1, unpack=True
                   )

    wavelength_air, spectral_irradiance_air= \
        np.loadtxt("M39_air.dat", dtype={'names': ('a', 'b'), 'formats': ('f4', 'f4')},
                   skiprows=1, unpack=True
                   )
    # eV to nm conversion
    #energy_eV = np.array(energy) * 10 ** 6
    #wavelength_inverse = np.array(energy_eV) / (speed_of_light * planck_c)
    #wavelength = 1 / wavelength_inverse
    fig, ax = plt.subplots(figsize=(20, 11))

    #energy_eV1 = np.array(energy1) * 10 ** 6
    #wavelength_inverse1 = np.array(energy_eV1) / (speed_of_light * planck_c)
    #wavelength1 = 1 / wavelength_inverse1

    spectral_irradiance2 = np.array(spectral_irradiance)
    spectral_irradiance3 = np.array(spectral_irradiance_air)

    #ax.plot(wavelength, count, linestyle='solid', lw=1.5, color='black', label='Geant4 -250 bins - areas')
    #ax.plot(wavelength1, count1, linestyle='solid', lw=1.5, color='red', label='Geant4 -250 bins - intensities')
    #ax.plot(wavelength2, spectral_irradiance2, linestyle='solid', lw=1.5, color='green', label='N2 2397 NO 3 Flux (mL/min)')
    ax.plot(wavelength_air, spectral_irradiance3, linestyle='solid', lw=1.5, color='blue', label='Air measurement')
    ax.set(xlabel="Wavelength (mm) ", ylabel="Spectral Irradiance [nW / (m$^2$ * nm)]", xlim=(200,400), ylim=(0, 500))



    ax.xaxis.set_major_locator(MultipleLocator(10))
    ax.xaxis.set_minor_locator(AutoMinorLocator(5))
    plt.title("Radioluminescence Spectrum (Beamtime - 06.05.2021)", fontsize=20)

    ax.grid()
    leg = ax.legend()
    leg.set_draggable(True)
    plt.legend(fontsize=20)
    plt.show()
