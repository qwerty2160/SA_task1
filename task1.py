n = 0
m = 0
abc = list("abcdhfgijkln")
table0 = list()
table1 = list()
cannonicalMatrices = list()
rmoreMatrix = list()
exp_numbers = list()
def getDataFromUser():
	global table0, exp_numbers, n, m
	n = int(input("Введите количество экспертов: "))
	m = int(input("Введите количество вариантов: "))
	for i in range(n):
		print("Номер эксперта {0}: ".format(i+1), end='')
		exp_numbers.append(int(input()))
	print("\nВвод исходной таблицы:\n")
	print(" "*2, end='')
	for i in range(n):
		print("E{}".format(exp_numbers[i]), end=' ')
	print()
	for i in range(m):
		print("V{}:".format(i+1), end='')
		table0.append(list(input()))

def createTable1():
	global table0, table1, exp_numbers, n, m, abc
	table1 = table0.copy()
	print("\nТаблица 1. Участники экспертного опроса и ранжируемые объекты.\n")
	print(" "*6, end='')
	for i in range(n):
		print("E{}".format(exp_numbers[i]), end='\t')
	print()
	for i in range(m):
		print("V{}{}:".format(i+1, abc[i]), end='\t')
		for j in range(n):
			table1[i][j] = (abc.index(table1[i][j]))+1
			print("V{}".format(table1[i][j]), end='\t')
		print()

def createCannonicalMatrices():
	global table0, table1, exp_numbers, n, m, abc, cannonicalMatrices
	for i in range(n):
		exp_list = list()
		exp_matrix = list()
		for j in range(m):
			exp_list.append(table1[j][i])
			exp_matrix.append(list("0"*m))
		for j in range(m):
			for t in range(m):
				if exp_list.index(t+1) > exp_list.index(j+1):
					exp_matrix[j][t] = 1
				elif exp_list.index(t+1) < exp_list.index(j+1):
					exp_matrix[j][t] = -1
				else:
					exp_matrix[j][t] = 0
		cannonicalMatrices.append(exp_matrix)
		print("\nМатрица упорядочения в канонической форме для эксперта E{}.\n".format(exp_numbers[i]))
		print("E{}".format(exp_numbers[i]), end='\t')
		for i in range(m):
			print("V{}".format(i+1), end='\t')
		print()
		for i in range(m):
			print("V{}".format(i+1), end='\t')
			for j in range(m):
				print(exp_matrix[i][j], end='\t')
			print()

def kemeni(x, y):
	global m
	s = 0
	for i in range(m):
		for j in range(m):
			s+=abs(x[i][j]-y[i][j])
	return int(s*0.5)
	
def createRmore():
	global table0, table1, exp_numbers, n, m, cannonicalMatrices, rmoreMatrix
	for i in range(n+1):
		rmoreMatrix.append(list(" "*(n+2)))
	for i in range(n):
		for j in range(n):
			m1 = cannonicalMatrices[i]
			m2 = cannonicalMatrices[j]
			rmoreMatrix[i][j]=kemeni(m1, m2)
	alpha_sigma = 0 #сумма сумм
	for i in range(n):
		s_col = 0
		s_row = 0
		s_row_square = 0
		for j in range(n):
			s_col += int(rmoreMatrix[j][i])
			s_row += int(rmoreMatrix[i][j])
			s_row_square+=int(rmoreMatrix[i][j])**2
		rmoreMatrix[i][j+1] = s_row
		rmoreMatrix[i][j+2] = s_row_square
		rmoreMatrix[j+1][i] = s_col
		alpha_sigma+=s_row
	rmoreMatrix[j+1][i+1] = alpha_sigma
	
	print("\nРасстояния между ответами-ранжированиями экспертов E{}-E{}.\n".format(exp_numbers[0], exp_numbers[-1]))
	print("Dij", end='\t')
	for i in range(n):
			print("E{}".format(exp_numbers[i]), end='\t')
	print("ΣрК\tΣкрК\t")
	for i in range(n+1):
		if i<n:
			print("E{}".format(exp_numbers[i]), end='\t')
		else:
			print("Σ", end='\t')
		for j in range(n+2):
			print(rmoreMatrix[i][j], end='\t')
		print()
	min_kvkem = rmoreMatrix[0][n-1+2]
	min_kvkem_exp_ind = 0
	for i in range(1, n):
		if min_kvkem>rmoreMatrix[i][n-1+2]:
			min_kvkem_exp_ind=i
		min(min_kvkem, rmoreMatrix[i][n-1+2])
	print("\nНаиболее согласованное ранжирование - эксперт E{}.".format(exp_numbers[min_kvkem_exp_ind]))
	
if __name__ == "__main__":
	getDataFromUser()
	createTable1()
	createCannonicalMatrices()
	createRmore()
