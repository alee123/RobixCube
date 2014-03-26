# F = [[1,2,3],[4,5,6],[7,8,9]]
# L = [[1,2,3],[4,5,6],[7,8,9]]
# R = [[1,2,3],[4,5,6],[7,8,9]]
# B = [[1,2,3],[4,5,6],[7,8,9]]
# U = [[1,2,3],[4,5,6],[7,8,9]]
# D = [[1,2,3],[4,5,6],[7,8,9]]


F = [[1,1,1],[1,1,1],[1,1,1]]
L = [[2,2,2],[2,2,2],[2,2,2]]
R = [[3,3,3],[3,3,3],[3,3,3]]
B = [[4,4,4],[4,4,4],[4,4,4]]
U = [[5,5,5],[5,5,5],[5,5,5]]
D = [[6,6,6],[6,6,6],[6,6,6]]

def printMatrix (m):
	for row in m:
		for c in row:
			print (c),
		print 

def printCube (U, L, F, R, B, D):
	for row in U:
		print ("      "),
		for c in row:
			print (c),
		print 	

	for k in range(3):
		for l in L[k]:
			print (l),
		print (""),
		for f in F[k]:
			print (f),
		print (""),
		for r in R[k]:
			print (r),
		print (""),
		for b in B[k]:
			print (b),
		print

	for d1 in D:
		print ("      "),
		for d in d1:
			print (d),
		print 		



def rM(matrix, dir):
	if dir=="C":
		temp = zip(*matrix[::-1])
	elif dir == "CC":
		temp = zip(*matrix)[::-1]
	else:
		temp1 = zip(*matrix[::-1])
		temp = zip(*temp1[::-1])
	return temp

def rotateLogic(dir, zero, one, two, three, four):
	tempOne = list(one[2][:])
	four =rM(four, "C")
	two =rM(two, "CC")
	three =rM(three,"180")
	zero =rM(zero, dir)
	if dir=="C":
		one[2] = list(four[2][:])
		four[2] = list(three[2][:])
		three[2] = list(two[2][:])
		two[2] = tempOne
	else:
		one[2] = list(two[2][:])
		two[2] = list(three[2][:])
		three[2] = list(four[2][:])
		four[2] = tempOne
	four =rM(four, "CC")
	two =rM(two, "C")
	three =rM(three,"180")

	return zero, one, two, three, four

def rotate(dir, face):
	global F
	global U
	global R
	global D
	global L
	global B

	if face == "F":
		F, U, R, D, L = rotateLogic(dir, F, U, R, D , L)
	elif face=="U":
		U, B, R, F, L = rotateLogic(dir, U, rM(B, "180"), rM(R,"CC"), F, rM(L, "C"))
		B, R, L = rM(B, "180"), rM(R, "C"), rM(L,"CC")
	elif face=="D":
		D, F, R, B, L = rotateLogic(dir, D, F, rM(R, "C"), rM(B,"180"), rM(L, "CC"))
		R, B, L = rM(R, "CC"), rM(B, "180"), rM(L, "C")
	elif face=="L":
		L, U, F, D, B = rotateLogic(dir, L, rM(U, "CC"), F, rM(D, "C"), B)
		U,D = rM(U, "C"), rM(D, "CC")
	elif face=="R":
		R, U, B, D, F = rotateLogic(dir, R, rM(U,"C"), B, rM(D, "CC"), F)
		U, D = rM(U, "CC"), rM(D, "C")
	elif face=="B":
		B, U, L, D, R = rotateLogic(dir, B,rM(U, "180"), L,rM(D, "180"), R)
		U,D =rM(U, "180"),rM(D, "180")



rotate("C", "L")
printCube(U, L, F, R, B, D)

