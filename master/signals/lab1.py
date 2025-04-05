import numpy as np
import matplotlib.pyplot as plt

def compute_and_plot(signal, fs, title):
    """
    Вычисляет FFT сигнала и строит графики амплитудного и фазового спектров.
    Подпись оси частот выполняется вручную.
    """
    N = len(signal)
    fft_signal = np.fft.fft(signal)
    freqs = np.fft.fftfreq(N, d=1/fs)
    amplitude = np.abs(fft_signal) / N  # нормировка
    phase = np.angle(fft_signal)
    eps = 0.01
    phase = np.where(amplitude < eps, 0, phase)
    
    # Построение графиков
    fig, axs = plt.subplots(1, 2, figsize=(14, 5))
    
    # Амплитудный спектр
    axs[0].stem(freqs, amplitude, 'b', markerfmt=" ", basefmt=" ")
    axs[0].set_xlabel("Frequency (Hz)")
    axs[0].set_ylabel("Amplitude")
    axs[0].set_title(title + " - Amplitude Spectrum")
    axs[0].set_xlim(-200, 200)
    # Ручная подпись оси X с шагом 50 Гц
    axs[0].set_xticks(np.arange(-200, 201, 50))
    
    # Фазовый спектр
    axs[1].stem(freqs, phase, 'r', markerfmt=" ", basefmt=" ")
    axs[1].set_xlabel("Frequency (Hz)")
    axs[1].set_ylabel("Phase (radians)")
    axs[1].set_title(title + " - Phase Spectrum")
    axs[1].set_xlim(-200, 200)
    axs[1].set_xticks(np.arange(-200, 201, 50))

# Задаём основные параметры
fs = 1000       # Частота дискретизации, Гц
t_total = 1.0 - 0.07  # Продолжительность сигнала, секунда
t = np.linspace(0, t_total, int(fs * t_total), endpoint=False)

# Частоты косинусов
f1 = 50   # Гц
f2 = 120  # Гц

# Создание сигнала как суммы двух косинусов
signal = np.cos(np.pi + 2 * np.pi * f1 * t) + np.cos(np.pi + 2 * np.pi * f2 * t)

plt.figure(figsize=(10, 4))
plt.plot(t, signal, label='Signal')
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.title("Signal vs. Time")
plt.legend()
plt.grid(True)
plt.show()


# Построение спектров для исходного сигнала (1 секунда)
compute_and_plot(signal, fs, "Original Signal (1s)")

# --- Варьирование интервала (длительности) сигнала ---
# Создадим сигналы разной длительности: 0.5 с, 1.0 с, 2.0 с.
durations = [0.5, 1.0, 2.0]
for dur in durations:
    t_dur = np.linspace(0, dur, int(fs * dur), endpoint=False)
    sig_dur = np.cos(np.pi + 2 * np.pi * f1 * t_dur) + np.cos(np.pi + 2 * np.pi * f2 * t_dur)
    compute_and_plot(sig_dur, fs, f"Signal ({dur}s)")

# Объяснение:
# - При увеличении длительности сигнала (например, 2 с) увеличивается частотное разрешение,
#   и спектральные пики становятся уже.
# - При уменьшении длительности (например, 0.5 с) спектральные пики становятся шире из-за эффекта оконного обрезания.

# --- Нулевое дополнение (Zero-Padding) ---
# Дополнить сигнал, длительностью 1 с, нулями до длины 2048 точек.
N_orig = len(signal)
N_pad = 2048
signal_zero_padded = np.pad(signal, (0, N_pad - N_orig), mode='constant')
compute_and_plot(signal_zero_padded, fs, "Zero-Padded Signal (1s padded to 2048 pts)")

# Объяснение:
# Zero-padding не улучшает разрешающую способность, но интерполирует спектр, делая его визуально гладче.

# --- Сглаживание краёв (Оконное преобразование) ---
# Применение окна Ханна для сглаживания резких краёв сигнала.
window = np.hanning(len(signal))
signal_windowed = signal * window
compute_and_plot(signal_windowed, fs, "Windowed Signal (Hann window)")

# Объяснение:
# Применение окна уменьшает спектральную утечку за счёт плавного затухания сигнала на краях.
# Однако это может привести к незначительному расширению основного лепестка спектра.
