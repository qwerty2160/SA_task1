obj_dict = dict() #m1, m2, m3... РАССМАТРИВАЕМЫЙ ОБЪЕКТ
clas_dict = dict() #a,b,c... КЛАССЫ

def getDataFromUser():
	global obj_dict, clas_dict
	letters_clas_list = list(input("Буквы классов (слитно): ").upper())
	for letter in letters_clas_list:
		print("Ввод класса {} (слитно): ".format(letter), end='')
		clas_dict[letter]=tuple(map(int, list(input())))
	number = int(input("Введите цифру объекта, M"))
	print("Ввод объекта M{} (слитно): ".format(number), end='')
	obj_dict["M"+str(number)]=tuple(map(int, list(input())))

def method1():
	global obj_dict, clas_dict
	print("\n1. Классификация (распознавание) от объектов до центров тяжести классов:\n")
	for tmp in obj_dict: obj = tmp
	min_clas = None
	min_p = 32768
	p_list = list()
	for clas in clas_dict:
		print("p({},{})=√(".format(obj, clas), end='')
		p = 0
		for i in range(len(obj_dict[obj])):
			print("({}-{})²".format(obj_dict[obj][i], clas_dict[clas][i]), end='')
			print("+" if len(obj_dict[obj])-i>=2 else "", end='')
			p+=(obj_dict[obj][i]-clas_dict[clas][i])**2
		print(")=√({})={}".format(p, p**0.5))
		p_list.append(p)
		if min_p > p: min_p = p; min_clas = clas
	if p_list.count(min_p) == 1:
		print("{} ∈ {}".format(obj, min_clas))
		return
	print("Отнести невозможно, требуется больше данных")

def method2():
	print("2. Классификация (распознавание) от объектов до центров тяжести классов с учетом весовых коэффициентов:")
	print("не используется без коэффициентов d")
	
def method3():
	global obj_dict, clas_dict
	print("\n3. Классификация (распознавание) по скалярному произведению:\n")
	for tmp in obj_dict: obj = tmp
	max_clas = None
	max_b = -32768
	b_list = list()
	for clas in clas_dict:
		print("B({},{})=".format(obj, clas), end='')
		b = 0
		for i in range(len(obj_dict[obj])):
			print("{}*{}".format(obj_dict[obj][i], clas_dict[clas][i]), end='')
			print("+" if len(obj_dict[obj])-i>=2 else "", end='')
			b+=obj_dict[obj][i]*clas_dict[clas][i]
		print("={}".format(b))
		b_list.append(b)
		if max_b < b: max_b = b; max_clas = clas
	if b_list.count(max_b) == 1:
		print("{} ∈ {}".format(obj, max_clas))
		return
	print("Отнести невозможно, требуется больше данных")

def method4():
	global obj_dict, clas_dict
	print("\n4. Классификация (распознавание) с использованием корреляционного метода:\n")
	for tmp in obj_dict: obj = tmp
	max_clas = None
	max_r = -32768
	r_list = list()
	for clas in clas_dict:
		print("r({},{})=".format(obj, clas), end='')
		b = 0
		for i in range(len(obj_dict[obj])):	b+=obj_dict[obj][i]*clas_dict[clas][i]
		r = b-sum(obj_dict[obj])*sum(clas_dict[clas])/len(obj_dict[obj])
		print("{}-(({})*({}))/{}".format(b, "+".join(map(str, obj_dict[obj])), "+".join(map(str, clas_dict[clas])), len(obj_dict[obj])), end='')
		print("={}".format(r))
		r_list.append(r)
		if max_r < r: max_r = r; max_clas = clas
	if r_list.count(max_r) == 1:
		print("{} ∈ {}".format(obj, max_clas))
		return
	print("Отнести невозможно, требуется больше данных")

def method5():
	global obj_dict, clas_dict
	print("\n5. Классификация (распознавание) по углу между векторами объекта и центра тяжести классов:\n")
	for tmp in obj_dict: obj = tmp
	max_clas = None
	max_phi = -32768
	phi_list = list()
	for clas in clas_dict:
		print("cosφ({},{})=".format(obj, clas), end='')
		b = 0
		for i in range(len(obj_dict[obj])):	b+=obj_dict[obj][i]*clas_dict[clas][i]
		obj_squares_tmp = list(map(lambda x: x**2, obj_dict[obj]))
		clas_squares_tmp = list(map(lambda x: x**2, clas_dict[clas]))
		phi = b/(sum(obj_squares_tmp)**0.5*sum(clas_squares_tmp)**0.5)
		print("{}/(√({})*√({}))".format(b, "+".join(map(str, obj_squares_tmp)), "+".join(map(str, clas_squares_tmp))), end='')
		print("={}".format(phi))
		phi_list.append(phi)
		if max_phi < phi: max_phi = phi; max_clas = clas
	if phi_list.count(max_phi) == 1:
		print("{} ∈ {}".format(obj, max_clas))
		return
	print("Отнести невозможно, требуется больше данных")

if __name__ == "__main__":
	try:
		getDataFromUser()
		method1()
		method3()
		method4()
		method5()
	except Exception:
		print("Произошла ошибка при вводе данных или иная ошибка!")
