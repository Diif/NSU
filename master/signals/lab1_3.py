import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import butter, filtfilt

# Parameters for the continuous-time signal
f1, f2 = 10, 15
A1, A2 = 1.0, 1.0
time_sec = 1.0 - 0.03

# Continuous-time axis
t_cont = np.linspace(0, time_sec, 10000, endpoint=False)

# Sampling parameters
fs = f2*100
Ts = 1/fs
t_samp = np.arange(0, time_sec, Ts)

# Sampled signal
x_samp = A1*np.cos(2*np.pi*f1*t_samp) + A2*np.cos(2*np.pi*f2*t_samp)
x_samp_cos_filtered = A1*np.cos(2*np.pi*f1*t_samp)

# FFT-based band-pass (select f1)
N = len(x_samp)
X = np.fft.fft(x_samp)/N
freqs = np.fft.fftfreq(N, Ts)

# bin‑width по частоте
bin_width = fs / N

# задаём ширину полосы ±1 Гц вокруг f1
half_band = 1.0  # Гц

# строим маску: все бины, чьи |частота| попадает в [f1 - 1, f1 + 1]
mask = (np.abs(np.abs(freqs) - f1) <= half_band + bin_width/2)

# Frequency-domain filtering
Xf = np.zeros_like(X)
Xf[mask] = X[mask]
x_fft_filt = np.real(np.fft.ifft(Xf * N))

# Time-domain filter via convolution
h = np.real(np.fft.ifft(mask * N))
x_time_filt = np.real(np.convolve(x_samp, h, mode='same')) / N

# Delta impulse
delta = np.zeros_like(x_samp); delta[0] = 1.0
# apply fft-based to delta
D = np.fft.fft(delta) / N
Df = np.zeros_like(D); Df[mask] = D[mask]
delta_fft = np.abs(np.fft.ifft(Df * N))
# convolution to delta
delta_time = np.abs(np.convolve(delta, h, mode='same')) / N

# Butterworth filter design (bandpass around f1 ± 1 Hz)
low, high = (f1-1)/(fs/2), (f1+1)/(fs/2)
b, a = butter(4, [low, high], btype='band')
x_butter = filtfilt(b, a, x_samp)
delta_butter = filtfilt(b, a, delta)

# Plot 1: original, freq, time
fig, axs = plt.subplots(3, 1, figsize=(10, 12))
#axs[0].plot(t_samp, x_samp, 'o-', label='Sampled Signal')
axs[0].plot(t_samp, h, 'o-', label='Sampled Signal')
# axs[0].plot(freqs, mask, 'o-', label='Sampled Signal')
axs[0].set_title('Original Sampled Signal')
axs[0].legend()

axs[1].plot(t_samp, x_fft_filt, 'o-', label='FFT-domain Filter')
axs[1].plot(t_samp, x_samp_cos_filtered, 'o-', label='orig filtered')
axs[1].plot(t_samp, x_butter, 'o-', label='x_butter Signal')
axs[1].set_title('After Frequency-Domain Filtering')
axs[1].legend()

#axs[2].plot(freqs, mask * N, 'o-', label='Time-domain Conv Filter')
# axs[2].plot(t_samp, h, 'o-', label='Time-domain Conv Filter')
axs[2].plot(t_samp, x_time_filt, 'o-', label='Time-domain Conv Filter')
axs[2].plot(t_samp, x_samp_cos_filtered, 'o-', label='orig filtered')
axs[2].set_title('After Time-Domain Filtering (Ideal Impulse Response)')
axs[2].legend()

plt.tight_layout()
plt.show()

# Plot 2: delta, freq, time
fig, axs = plt.subplots(4, 1, figsize=(10, 12))
axs[0].stem(t_samp, delta, basefmt='k-', label='Delta Impulse')
axs[0].set_title('Delta Impulse')
axs[0].legend()

axs[1].plot(t_samp, delta_fft, 'o-', label='Delta FFT-domain Filter')
axs[1].set_title('Delta After Frequency-Domain Filtering')
axs[1].legend()

axs[2].plot(t_samp, delta_time, 'o-', label='Delta Time-domain Conv Filter')
axs[2].set_title('Delta After Time-Domain Filtering (Ideal)')
axs[2].legend()

axs[3].plot(t_samp, delta_butter, 'o-', label='x_butter Signal')
axs[3].set_title('Delta butter')
axs[3].legend()

plt.tight_layout()
plt.show()

# # Butterworth results
# print("Butterworth 4th-order bandpass around f1±1Hz:")
# print("Original signal -> first 5 samples:", x_butter[:5])
# print("Delta impulse -> impulse response samples:", delta_butter[:5])