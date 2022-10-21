# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    filler.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 18:33:20 by parkharo          #+#    #+#              #
#    Updated: 2022/10/21 19:29:45 by parkharo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from operator import truediv
import pygame as pg
import sys
import time
import subprocess
from curses.ascii import isalpha, isdigit

pg.init()

size = width, height = (800, 600)

crimson_red = 153, 0, 0
champagne_white = 247, 231, 206
resres =  2.2375

p1used = 7, 135, 30
p1new = 110, 246, 134

p2used = 139, 3, 107
p2new = 250, 106, 217

pause = False

screen = pg.display.set_mode((800, 600))
screen.fill(crimson_red)
pg.display.set_caption("My filler")

clock = pg.time.Clock()
headline_font = "visualizer/fonts/Pixtile-jEPr9.ttf"
interface_font = "visualizer/fonts/PixeloidSans-nR3g1.ttf"

def print_menu(p1, p2):
	text_out = pg.font.Font(interface_font, int(16))
	game_out = pg.font.Font(headline_font, int(50))

	text_surface = game_out.render("Filler by parkharo", True, champagne_white)
	screen.blit(text_surface, (20, 30))

	text_surface = text_out.render("Player 1: " + p1, True, champagne_white)
	screen.blit(text_surface, (20, 120))

	text_surface = text_out.render("Player 2: " + p2, True, champagne_white)
	screen.blit(text_surface, (420,120))
	pg.display.update()
	pg.time.delay(100)

def parse_players():
		for _ in range(5):
			sys.stdin.readline()
		str = sys.stdin.readline()
		splitted = str.split("/")
		p1 = splitted[-1]
		p1 = p1.replace("\n","")
		str = sys.stdin.readline()
		str = sys.stdin.readline()
		splitted = str.split("/")
		p2 = splitted[-1]
		p2 = p2.replace("\n","")
		str = sys.stdin.readline()
		print_menu(p1, p2)
		return (p1, p2)


def parse_map(rows, columns, moves_p1, moves_p2):
	x = 0;
	y = 0;
	x_coord = 400 / resres;
	y_coord = 450 / resres ;
	moves_p1_str = f'{moves_p1}'
	moves_p2_str = f'{moves_p2}'

	# clear = pg.Surface((0 , 140))
	# clear.fill(crimson_red)
	# screen.blit(clear, (100 / resres, 130 / resres ))

	flag_p1 = 0
	flag_p2 = 0
	str = sys.stdin.readline()
	while (y < int(rows)):
		str = sys.stdin.readline()
		while (isdigit(str[x]) or str[x] == ' '):
			x += 1
		while (x < (int(columns) + 4)):
			if str[x] == '.':
				screen.blit(empty, (x_coord, y_coord))
			if str[x] == 'O':
				screen.blit(p1_old, (x_coord, y_coord))
			if str[x] == 'o':
				screen.blit(p1_new, (x_coord, y_coord))
				flag_p1 = 1
			if str[x] == 'x':
				screen.blit(p2_new, (x_coord, y_coord))
				flag_p2 = 1
			if str[x] == 'X':
				screen.blit(p2_old, (x_coord, y_coord))
			x += 1
			x_coord += square_side + 1
		x = 0
		x_coord = 400 / resres
		y += 1
		y_coord += square_side + 1
	if flag_p1 == 1:
		moves_p1 += 1
	if flag_p2 == 1:
		moves_p2 += 1
	flag_p1 = 0
	flag_p2 = 0
	print_score(moves_p1, moves_p2)
	return (moves_p1, moves_p2)

def print_score(moves_p1, moves_p2):

	pg.draw.rect(screen, crimson_red, pg.Rect(20,140, 465, 27))
	pg.display.update()
	
	text_out = pg.font.Font(interface_font, int(26))
	text_surface = text_out.render(str(moves_p1), True, champagne_white)
	screen.blit(text_surface, (20, 140))
	text_surface = text_out.render(str(moves_p2), True, champagne_white)
	screen.blit(text_surface, (420, 140))

	

def parse_piece(p_rows, p_columns, first_player):
	x = 0;
	y = 0;

	if (p_rows < p_columns):
		divider_p = int(p_columns)
	else:
		divider_p = int(p_rows)
	side = 100  / divider_p / resres
	# x_coord1 = 110 / resres
	# x_coord2 = 1300 / resres
	# p1_new = pg.Surface((side - 2, side - 2))
	# p1_new.fill(p1new)
	# p2_new = pg.Surface((side - 2, side - 2))
	# p2_new.fill(p2new)
	# empty = pg.Surface((side - 2, side - 2))
	# empty.fill('gray19')
	# clear_p1 = pg.Surface((130  /resres , 100 / resres ))
	# clear_p1.fill(crimson_red)
	# text_out = pg.font.Font(interface_font, 15)
	# if (first_player % 2 == 1):
	# 	piece = p1_new
	# 	x_coord = x_coord1
	# 	y_coord = 420 / resres
		#screen.blit(clear_p1, (x_coord1, y_coord))
	# else:
	# 	piece = p2_new
	# 	x_coord = x_coord2
	# 	y_coord = 420 / resres
	# 	#screen.blit(clear_p1, (x_coord2, y_coord))
	while (y < int(p_rows)):
		string = sys.stdin.readline()
		# while (x < int(p_columns)):
		# 	# if (string[x] == '*'):
		# 	# 	screen.blit(piece, (x_coord, y_coord))
		# 	# if (string[x] == '.'):
		# 	# 	screen.blit(empty, (x_coord, y_coord))
		# 	x += 1
		# 	x_coord1 += side
		# 	x_coord2 += side
		# x_coord1 = 110 / resres
		# x_coord2 = 430 / resres
		# x = 0
		# y_coord += side
		y += 1

def paused():
	while 1:
		for event in pg.event.get():

			if event.type == pg.QUIT:
				pg.quit()
				exit()

			if event.type == pg.KEYDOWN:
					if event.key == pg.K_ESCAPE:
						pg.quit()
						exit()

		pg.display.update()
		clock.tick(15)


p1, p2 = parse_players()

first_player = 1
old_symb = " (X):"
moves_p1 = 0;
moves_p2 = 0;

read_str = sys.stdin.readline().rstrip(':\n').split(' ')
rows = int(read_str[1])
cols = int(read_str[2])

divider = int(rows) if (rows < cols) else int(cols)
square_side = 700 / resres / divider - 1

p1_old = pg.Surface((square_side, square_side))
p1_old.fill(p1used)
p1_new = pg.Surface((square_side, square_side))
p1_new.fill(p1new)
p2_old = pg.Surface((square_side, square_side))
p2_old.fill(p2used)
p2_new = pg.Surface((square_side, square_side))
p2_new.fill(p2new)
empty = pg.Surface((square_side, square_side))
empty.fill('gray19')

while 1:
	delay = 21
	for event in pg.event.get():
		if event.type == pg.QUIT:
			pg.quit()
			exit()
		if event.type == pg.KEYDOWN:
				if event.key == pg.K_ESCAPE:
					pg.quit()
					exit()

	if 'fin' in read_str[2]:
		paused()
	moves_p1, moves_p2 = parse_map(rows, cols, moves_p1, moves_p2)
	read_str = sys.stdin.readline().rstrip(':\n').split(' ')
	while 'Piece' in read_str[0]:
		p_rows = int(read_str[1])
		p_columns = int(read_str[2])
		parse_piece(p_rows, p_columns, first_player)
		read_str = sys.stdin.readline().rstrip(':\n').split(' ')
		if read_str[1] != old_symb:
			first_player += 1
			old_symb = read_str[1]
		else:
			if 'X' in old_symb:
				first_player = 0
			if 'O' in old_symb:
				first_player = 1
		read_str = sys.stdin.readline().rstrip(':\n').split(' ')

	pg.display.update()
	pg.time.delay(delay)