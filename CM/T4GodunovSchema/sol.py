#!/usr/bin/env python3

import matplotlib.pyplot as plt
import math

layer_dictionary = {}

start_x = -10.0
end_x = 10.0
start_t = 0.0
end_t = 1.0
coef_a = 5.0;
num_x_intervals = 100;

step_x = (abs(start_x) + abs(end_x)) / num_x_intervals

# coef_r = 1
# step_t = coef_r * step_x / coef_a

# num_t_intervals = (abs(start_t) + abs(end_t)) / step_t

# start_node_x = math.floor(start_x / step_x)
# end_node_x = math.floor(end_x / step_x)

# start_node_t = math.floor(start_t / step_t)
# end_node_t = math.floor(end_t / step_t)



def calculate_u_layer(n_plus_1):
	n = n_plus_1 - 1;
	for i in range(start_node_x, end_node_x + 1, 1):
		layer_dictionary[n_plus_1].update({i : layer_dictionary[n][i] - (coef_r * (layer_dictionary[n][i] - layer_dictionary[n][i - 1]))})

def calculate_v_fun(x):
	if x <= 0:
		return 3
	else:
		return 1

def calculate_u_solution(x_node,t):
	return calculate_v_fun(x_node*step_x - coef_a * t)

def calculate_u_at_zero_level(n):
	return calculate_v_fun(n * step_x);
	

def init_zero_level():
	for i in range(start_node_x, end_node_x + 1, 1):
		layer_dictionary[start_node_t].update({i : calculate_u_at_zero_level(i)})

def init_borders():
	for i in range(start_node_t, end_node_t + 1, 1):
		layer_dictionary[i].update({start_node_x - 1 : calculate_u_at_zero_level(start_node_x - 1)})

def init_dictionary():
	i = start_node_t;
	for i in range(start_node_t, end_node_t + 1, 1):
		layer_dictionary.update({i : {}})

def do_task(plot_num, r_val, myplt):
	global coef_r
	# coef_r = float(input("Enter r-value: "))
	coef_r = r_val
	global step_t
	step_t = coef_r * step_x / coef_a

	global num_t_intervals
	num_t_intervals = (abs(start_t) + abs(end_t)) / step_t

	global start_node_x
	start_node_x = math.floor(start_x / step_x)
	global end_node_x
	end_node_x = math.floor(end_x / step_x)

	global start_node_t
	start_node_t = math.floor(start_t / step_t)
	global end_node_t
	end_node_t = math.floor(end_t / step_t)

	init_dictionary()
	init_zero_level()
	init_borders()

	for i in range(start_node_t + 1, end_node_t + 1, 1):
		calculate_u_layer(i)

	x_arr = [];
	for i in range(start_node_x, end_node_x + 1, 1):
		x_arr.append(step_x * i)

	t_arr = []
	for j in range(start_node_x, end_node_x + 1, 1):
		t_arr.append(layer_dictionary[end_node_t][j])

	t_sol_arr = [];
	for j in range(start_node_x, end_node_x + 1, 1):
		t_sol_arr.append(calculate_u_solution(j, end_t))	

	print(x_arr)
	print(t_arr)
	# plt1 = fig.add_subplot(plot_num)
	myplt.plot(x_arr, t_arr, label='app')
	myplt.plot(x_arr, t_sol_arr, label='sol')
	

fig = plt.figure()
plt1 = fig.add_subplot(231)
plt2 = fig.add_subplot(232)
plt3 = fig.add_subplot(233)
plt4 = fig.add_subplot(234)
plt5 = fig.add_subplot(235)

do_task(321, 0.25,plt1);
do_task(322, 0.5,plt2);
do_task(323, 0.75,plt3);
do_task(324, 1,plt4);
do_task(325, 1.25,plt5);

plt.title("N = " + str(num_x_intervals) + " and r in {0.25, 0.5, 0.75, 1, 1.25}")
plt.legend(loc='best')
plt.show()