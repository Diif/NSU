import numpy as np
import matplotlib.pyplot as plt

# Parameters for the continuous-time signal
f1 = 10
f2 = 15
A1 = 1.0
A2 = 1.0

time_sec = 1.0
# Continuous-time axis (high resolution)
t_cont = np.linspace(0, time_sec, 10000, endpoint=False)

# Continuous-time signal
x_cont = A1 * np.cos(2 * np.pi * f1 * t_cont) + A2 * np.cos(2 * np.pi * f2 * t_cont)

# Sampling parameters
fs = f2*2 + 1 # Sampling frequency (Hz) — below Nyquist for f2
Ts = 1 / fs
t_samp = np.arange(0, time_sec, Ts)

# Sampled signal
x_samp = A1 * np.cos(2 * np.pi * f1 * t_samp) + A2 * np.cos(2 * np.pi * f2 * t_samp)

# Compute FFT of sampled signal
N = len(x_samp)
X = np.fft.fft(x_samp) / N
freqs = np.fft.fftfreq(N, Ts)

# Calculate and print the aliased frequency for f2
f2_mod = f2 % fs
if f2_mod > fs/2:
    f2_alias = fs - f2_mod
else:
    f2_alias = f2_mod
print(f"Original f2 = {f2} Hz, sampled at {fs} Hz, aliases to {f2_alias} Hz")


t_dense = np.linspace(0, time_sec, 10000, endpoint=False)
x_rec = np.zeros_like(t_dense)

for n in range(len(t_samp)):
    # рассчитаем sinc((t_dense - nTs)/Ts)
    u = (t_dense - t_samp[n]) / Ts
    x_rec += x_samp[n] * np.sinc(u)  # np.sinc реализует sin(pi*u)/(pi*u)


# Plot all on one figure with three subplots
plt.figure(figsize=(12, 10))

# 1. Continuous and sample points
plt.subplot(4, 1, 1)
plt.plot(t_cont, x_cont, label='Continuous Signal')
plt.stem(t_samp, x_samp, linefmt='C1-', markerfmt='C1o', basefmt='k-', label='Samples')
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.title("Continuous-Time Signal and Samples")
plt.xticks(np.arange(0, time_sec + 0.1, 0.1))
plt.legend()

# 2. Magnitude Spectrum
plt.subplot(4, 1, 2)
plt.stem(freqs, np.abs(X))
plt.xlim(0, fs/2)
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude")
plt.title("Magnitude Spectrum of Sampled Signal")
plt.xticks(np.arange(0, fs/2 + 1, 1))

# 3. Sinc Interpolation Reconstruction
plt.subplot(4, 1, 3)
plt.plot(t_dense, x_rec, label='Reconstructed Signal')
plt.stem(t_samp, x_samp, linefmt='C1-', markerfmt='C1o', basefmt='k-', label='Samples')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('Reconstruction via Sinc Interpolation')
plt.legend()

u = t_dense = np.linspace(-20, +20, 10000, endpoint=False)
sinc_samp = np.sinc(u)

plt.subplot(4, 1, 4)
plt.plot(t_dense, sinc_samp, label='sinc')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('Reconstruction via Sinc Interpolation')
plt.legend()

plt.tight_layout()
plt.show()