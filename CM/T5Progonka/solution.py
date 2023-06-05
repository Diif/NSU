#!/usr/bin/env python3

import matplotlib.pyplot as plt
import math

num_intervals = int(input("Enter num intervals: "))
num_points = num_intervals + 1;

x_start = 0;
x_end = 1;

left_border_val = 0;
right_border_val = 0;

h = (abs(x_start) + abs(x_end))/num_intervals

alpha = []
betta = []
x_dictionary = {}

def get_a(num):
	if(num <= 0 or num > num_intervals):
		print("WRONG NUM FOR coef_a: "+ str(num));
		return -9999999;
	if(num == num_intervals):
		return 0;
	else:
		return -1;

def get_c(num):
	if(num < 0 or num > num_intervals):
		print("WRONG NUM FOR coef_c: "+ str(num));
		return -9999999;
	if(num == num_intervals or num == 0):
		return 1;
	else:
		return -2;

def get_b(num):
	if(num < 0 or num >= num_intervals):
		print("WRONG NUM FOR coef_b: " + str(num));
		return -9999999;
	if(num == 0):
		return 0;
	else:
		return -1;

def get_f(num):
	if(num < 0 or num > num_intervals):
		print("WRONG NUM FOR f: " + str(num));
		return -9999999;
	if(num == 0):
		return left_border_val;
	if(num == num_intervals):
		return right_border_val;
	else:
		return -2*h*h

def calc_alpha(num):
	if(num==0):
		return get_b(0) / get_c(0)
	else:
		return get_b(num) / (get_c(num) - alpha[num-1]*get_a(num))

def calc_betta(num):
	if(num==0):
		return get_f(0) / get_c(0)
	else:
		return (get_f(num) + betta[num-1]*get_a(num))/(get_c(num) - alpha[num-1] * get_a(num))

def fill_alpha_and_betta():
	for i in range(0, num_points, 1):
		betta.append(calc_betta(i));
		if(i == num_intervals):
			break;
		alpha.append(calc_alpha(i));

def calc_x(num):
	if(num == num_intervals):
		return betta[num_intervals]
	else:
		return x_dictionary[num + 1]*alpha[num] + betta[num];

def fill_x():
	for i in range(num_intervals, -1, -1):
		x_dictionary.update({i : calc_x(i)})

def calc_real_fun(x):
	return -x*x + x

fill_alpha_and_betta();
fill_x();

# небольшая перегрузка "х" получилась... Раньше был решением.
arr_x = [];
arr_y = [];
arr_real_y = [];
arr_real_x = []

for i in range(0, num_points, 1):
	arr_y.append(x_dictionary[i]);
	arr_x.append(h*i);

num_points_real = 1000000;
good_step = (abs(x_start) + abs(x_end)) / num_points_real
for i in range(0,num_points_real, 1):
	arr_real_y.append(calc_real_fun(good_step*i));
	arr_real_x.append(good_step*i);

	
# fig = plt.figure()
# plt1 = fig.add_subplot(211)
# plt2 = fig.add_subplot(212)
plt1 = plt
# plt2.plot(arr_x, arr_y, label='app')

plt1.plot(arr_x, arr_y, label='app')
plt1.plot(arr_real_x, arr_real_y, label='sol')


plt.title("Num intervals = " + str(num_intervals))
plt.legend(loc='best')
plt.show()