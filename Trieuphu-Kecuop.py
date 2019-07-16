import numpy as np 
import pygame as pg 


def main():
	f = np.zeros((4, 4, 4, 4, 3), np.int32)
	s = np.array([3, 3, 0, 0, 0])
	t = np.array([0, 0, 3, 3, 2])

	q = np.array([], np.int32)
	q.resize((4 * 4 * 4 * 4 * 3, 5))
	l, r = 0, 1
	q[0] = s
	f[ s[0], s[1], s[2], s[3], s[4] ] = 1

	def inside(lef, mid, rig):
		return (lef <= mid) & (mid <= rig)

	isExistAnswer = False
	while (l < r):
		u = q[l] 
		l += 1
		if (u[0] == t[0]) and (u[1] == t[1]) and (u[2] == t[2]) and (u[3] == t[3]) and (u[4] == t[4]):
			isExistAnswer = True
			break
		if (u[4] == 0):
			for x in range(3):
				for y in range(3):
					v = np.array([ u[0] - x, u[1] - y, u[2], u[3], 1 ])
					if inside(1, x + y, 2) and inside(0, v[0], 3) and inside(0, v[1], 3) and ((v[0] == 0) or (v[0] >= v[1])):
						if (f[v[0]][v[1]][v[2]][v[3]][v[4]] == 0):
							f[v[0]][v[1]][v[2]][v[3]][v[4]] = l
							v[4] = 1
							q[r] = v
							r += 1
		if (u[4] == 1) or (u[4] == -1):
			v = np.zeros((5), np.int32)
			if (u[4] == 1):
				v = np.array([ u[0], u[1], 3 - u[0], 3 - u[1], u[4] + 1])
			else:
				v = np.array([ 3 - u[2], 3 - u[3], u[2], u[3], u[4] + 1])
			if inside(0, v[2], 3) and inside(0, v[3], 3) and ((v[2] == 0) or (v[2] >= v[3])):
				if (f[v[0]][v[1]][v[2]][v[3]][v[4]] == 0):
					f[v[0]][v[1]][v[2]][v[3]][v[4]] = l
					q[r] = v
					r += 1
		if (u[4] == 2):
			for x in range(3):
				for y in range(3):
					v = np.array([ u[0], u[1], u[2] - x, u[3] - y, 1 ])
					if inside(1, x + y, 2) and inside(0, v[2], 3) and inside(0, v[3], 3) and ((v[2] == 0) or (v[2] >= v[3])):
						if (f[v[0]][v[1]][v[2]][v[3]][v[4]] == 0):
							f[v[0]][v[1]][v[2]][v[3]][v[4]] = l
							v[4] = -1
							q[r] = v
							r += 1
		
	if isExistAnswer == False:
		print("sai cho nao cmnr")
		exit(0)
	else:
		answer = [t]
		while (l != 0):
			l = f[t[0]][t[1]][t[2]][t[3]][t[4]] - 1
			v = q[l]
			v[4] = abs(v[4])
			answer.append(v)
			t = v

		return np.flip(np.array(answer), 0)

def showAnswer(answer):
	print("Ky hieu: TP = trieu phu | KC = ke cuop")
	print('__')
	d = 1
	tmp = ["bo trai sang bo phai", "bo phai sang bo trai"]
	for i in answer:
		if (i[4] != 1):
			print("bo trai co: ", i[0], "TP va", i[1], "KC")
			print("bo phai co: ", i[2], "TP va", i[3], "KC")
		else:
			d += 1
			print("thuyen cho:", 3 - i[0] - i[2], "TP va", 3 - i[1] - i[3], "KC tu %s" %(tmp[d % 2]))
			print('__')
		pg.time.delay(200)

if __name__ == "__main__":
	answerArray = main()
	showAnswer(answerArray)


# State[x1][y1][x2][y2][t] với:
#	(x1, y1) là số triệu phú và kẻ cướp bờ bên trái
#	(x2, y2) là số triệu phú và kẻ cướp bờ bên phải
#	(t) là vị trí của thuyền: 0 = bờ trái, 1 = đang ở trên sống, 2 = bờ phải

# Mục tiêu: đi từ state S sang state T với:
#	(S) = [3][3][0][0][0]
#	(T) = [0][0][3][3][2]

 