import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)

speed_of_light = 2.99792458 * (10 ** 17)  # nm/s
planck_c = 4.1356677516 * (10 ** -15)  # eV * s

if __name__ == "__main__":
    # Read out
    pixel, energy, count = \
        np.loadtxt("OpN-50kBq.ascii", dtype={'names': ('a', 'b', 'c'), 'formats': ('f4', 'f4', 'f4')},
                   skiprows=4, unpack=True
                   )

    pixel1, energy1, count1 = \
        np.loadtxt("OpN_50kBq_noGold_10mm.ascii", dtype={'names': ('a', 'b', 'c'), 'formats': ('f4', 'f4', 'f4')},
                    skiprows=4, unpack=True
                    )

    deposited_energy = np.array(energy)
#    spectral_irradiance3 = np.array(spectral_irradiance_air)


    fig, ax = plt.subplots(figsize=(9, 5))
    ax.plot(deposited_energy, count, linestyle='solid', lw=1.5, color='blue')
    ax.plot(energy1, count1, linestyle='solid', lw=1.5, color='blue')
    ax.set(xlabel="Track Length (mm) ", ylabel="No. of alpha particles", xlim=(10,60), ylim=(0, 12000))



    ax.xaxis.set_major_locator(MultipleLocator(10))
    ax.xaxis.set_minor_locator(AutoMinorLocator(10))
    plt.title("Track length of alpha particles emitted by the Am-241 source", fontsize=15)

    ax.set_xticks([10,20,30,40,50])
    ax.grid()
   # leg = ax.legend()
   # leg.set_draggable(True)
   # plt.legend(fontsize=20)
    plt.show()
