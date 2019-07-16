import numpy as np 
import pygame as pg 
def enter():
	global tree, chil, root

	with open("formula.data") as cin:
		tree = np.array(cin.readline().strip().split(' '))

	chil = np.zeros((tree.shape[0], 2), np.int32) - np.ones((tree.shape[0], 2), np.int32)
	
	A, B = list(), list()
	def up():
		while len(B) > 1 and tree[A[len(A) - 1]] != "(":
			d = A.pop(len(A) - 1)
			chil[d][1] = B.pop(len(B) - 1)
			chil[d][0] = B.pop(len(B) - 1)	
			B.append(d)

	for i, t in enumerate(tree):
		if t == "(" or t == "nt" or t == "//":
			A.append(i)
		elif t != ")":
			B.append(i)
			up()
		else:
			A.pop(len(A) - 1)
			up()
	up()
	print(chil)
	root = B[0]

def dfs(u):
	if (u == -1):
		return []
	tmp = list()
	tmp += dfs(chil[u][0])
	tmp += dfs(chil[u][1])
	tmp.append(tree[u])
	return tmp

def process(s):
	global width, height, list_rect, list_line, name
	width, height = (0, 0)
	list_rect, list_line, name = list(), list(), list()

	def merge_nt(list_rectA, list_lineA, widthA, heightA, list_rectB, list_lineB, widthB, heightB):
		if heightA < heightB:
			return merge_nt(list_rectB, list_lineB, widthB, heightB, list_rectA, list_lineA, widthA, heightA)
		
		list_rectC = list_rectA.copy()
		list_lineC = list_lineA.copy()
		widthC = widthA + widthB
		heightC = heightA
		delta = (heightA - heightB) // 2
		for i in range(len(list_rectB)):
			list_rectC.append(list_rectB[i])
			list_rectC[-1][0] += widthA
			list_rectC[-1][1] += delta
		for i in range(len(list_lineB)):
			list_lineC.append(list_lineB[i])
			list_lineC[-1][0] += widthA
			list_lineC[-1][2] += widthA
			list_lineC[-1][1] += delta
			list_lineC[-1][3] += delta
		return (list_rectC, list_lineC, widthC, heightC)

	def merge_ss(list_rectA, list_lineA, widthA, heightA, list_rectB, list_lineB, widthB, heightB):
		if widthA < widthB:
			return merge_ss(list_rectB, list_lineB, widthB, heightB, list_rectA, list_lineA, widthA, heightA)

		list_rectC = list_rectA.copy()
		list_lineC = list_lineA.copy()
		widthC = widthA
		heightC = heightA + heightB + 30
		delta = (widthA - widthB) // 2
		for i in range(len(list_rectB)):
			list_rectC.append(list_rectB[i])
			list_rectC[-1][0] += delta
			list_rectC[-1][1] += heightA + 30
		for i in range(len(list_lineB)):
			list_lineC.append(list_lineB[i])
			list_lineC[-1][0] += delta
			list_lineC[-1][2] += delta
			list_lineC[-1][1] += (heightA + 30)
			list_lineC[-1][3] += (heightA + 30)
		list_lineC.append([1, heightA // 2, 1, heightA + 30 + heightB // 2])
		list_lineC.append([widthA, heightA // 2, widthA, heightA + 30 + heightB // 2])
		if (widthA > widthB):
			list_lineC.append([1, heightA + 30 + heightB // 2, delta, heightA + 30 + heightB // 2])
			list_lineC.append([widthA - delta + 1, heightA + 30 + heightB // 2, widthA, heightA + 30 + heightB // 2])
		list_lineC.append([-19, heightC // 2, 0, heightC // 2]) 
		list_lineC.append([widthC + 1, heightC // 2, widthC + 20, heightC // 2])
		widthC += 40
		for i in range(len(list_rectC)):
			list_rectC[i][0] += 20
		for i in range(len(list_lineC)):
			list_lineC[i][0] += 20
			list_lineC[i][2] += 20
		return (list_rectC, list_lineC, widthC, heightC)

	def create(name):
		widthA = 20 + 40 + 20
		heightA = 20
		list_lineA = list()
		list_rectA = list()
		list_lineA.append([1, 10, 20, 10])
		list_lineA.append([61, 10, 80, 10])
		list_rectA.append([21, 1, 40, 20, name])
		return (list_rectA, list_lineA, widthA, heightA)

	print(s)

	A = list()

	cnt = 0
	B = list()

	for i in s:
		if i == "nt":
			u = A.pop(len(A) - 1)
			v = A.pop(len(A) - 1)
			B.append(merge_nt(B[u][0], B[u][1], B[u][2], B[u][3], B[v][0], B[v][1], B[v][2], B[v][3]))
			A.append(len(B) - 1)
			continue
		if i == "//":
			u = A.pop(len(A) - 1)
			v = A.pop(len(A) - 1)
			B.append(merge_ss(B[u][0], B[u][1], B[u][2], B[u][3], B[v][0], B[v][1], B[v][2], B[v][3]))
			A.append(len(B) - 1)
			continue
		B.append(create(i))
		A.append(len(B) - 1)

	list_rect, list_line, width, height = B[-1]

	width += 40
	height += 40
	for i in range(len(list_rect)):
		list_rect[i][0] += 20
		list_rect[i][1] += 20
	for i in range(len(list_line)):
		list_line[i][0] += 20
		list_line[i][1] += 20
		list_line[i][2] += 20
		list_line[i][3] += 20


def main():
	pg.init()
	resolution = (max(width, 800) + 1, max(height, 600) + 1)
	screen = pg.display.set_mode(resolution)
	pg.display.set_caption("Show")

	white = pg.Color(255, 255, 255)
	blue = pg.Color(0, 0, 255)
	for i in list_line:
		pg.draw.line(screen, white, (i[0], i[1]), (i[2], i[3]))
	f = pg.font.Font(None, 20)
	for i in list_rect:
		pg.draw.rect(screen, white, pg.Rect(i[0], i[1], i[2], i[3]))
		text = f.render(i[4], True, blue)
		screen.blit(text, (i[0] +	 3, i[1] + 3))
	running = True
	while running:
		for events in pg.event.get():
			if events.type == pg.QUIT:
				running = False
		if running:
			pg.display.flip()
	pg.quit()

if __name__ == "__main__":
	enter()
	process(dfs(root))
	main()