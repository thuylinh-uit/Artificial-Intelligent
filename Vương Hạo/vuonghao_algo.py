from rules import check, standardized, change

#B0: du lieu goc ban dau gom tap GT va KL
#B1: chuan hoa du ieu
#B2: chuyen phu dinh neu co
#B3: chuyen and tu GT va or tu KL thanh ','
#B4: tach ra cac dong neu o GT co or va o KL co and
#B5: chung minh tung dong -> dua ket luan

def merge(GT, KL):
	"return similiar GT -> KL"
	text = ""
	for i in range(len(GT) - 1): text += GT[i] + ", "
	if len(GT) != 0: text += GT[-1]
	text += " -> ";
	for i in range(len(KL) - 1): text += KL[i] + ", "
	if len(KL) != 0: text += KL[-1]
	return text

def B0(GT, KL):
	for i in range(len(GT)): GT[i] = standardized(GT[i])
	for i in range(len(KL)): KL[i] = standardized(KL[i])
	text = []
	text.append("Bước 0: dữ liệu gốc ban đầu")
	text.append(merge(GT, KL))
	return (GT, KL, text)

def B1(GT, KL):	
	index_from = [23, 21, 19, 18, 17, 16, 15, 13]
	index_to = {23: 22, 21: 20, 19: 4, 18: 3, 17: 1, 16: 1, 15: 1, 13: 1}
	text = []
	text.append("Bước 1: chuẩn hóa dữ liệu về đơn giản hơn")
	for i in range(len(GT)):
		index = check(GT[i])
		if index == -1: 
			print("FAIL")	## this is ? 
		if index in index_from:
			text.append("  chuyen '" + GT[i] + "' thanh '" + change(GT[i], index, index_to[index]) + "'")		
			GT[i] = change(GT[i], index, index_to[index])
	for i in range(len(KL)):
		index = check(KL[i])
		if index == -1: 
			print("FAIL")
		if index in index_from:
			text.append("  chuyen '" + KL[i] + "' thanh '" + change(KL[i], index, index_to[index]) + "'")		
			KL[i] = change(KL[i], index, index_to[index])
	text.append("--- dữ liệu sau khi chuẩn hóa đon giản hơn: ")
	text.append(merge(GT, KL))
	return (GT, KL, text)

def B2(GT, KL):
	index_from = [2, 5, 6]
	index_to = {2: 1, 5: 3, 6: 4}
	text = []
	text.append("Bước 2: chuyển phủ định về vế còn lại")
	while True:
		cnt = 0
		i = 0
		while i < len(GT):
			index = check(GT[i])
			if index in index_from:
				cnt += 1
				text.append("  chuyển '" + GT[i] + "' qua KL")
				KL.append(change(GT[i], index, index_to[index]))
				del GT[i]
			else:
				i += 1
		i = 0
		while i < len(KL):
			index = check(KL[i])
			if index in index_from:
				cnt += 1
				text.append("  chuyển '" + KL[i] + "' qua GT")
				GT.append(change(KL[i], index, index_to[index]))
				del KL[i]
			else:
				i += 1
		if cnt == 0:
			break
		text.append("--- sau khi chuyển: ")
		text.append(merge(GT, KL))
	return (GT, KL, text)

def B3(GT, KL):
	splitGT = [3, 8, 9, 12, 15, 16, 18, 21, 22]
	splitKL = [4, 7, 10, 11, 13, 17, 19, 20, 23]
	text = []
	text.append("Bước 3: tách and từ GT và or từ KL ra thành các mệnh đề mới")
	i = 0
	while i < len(GT):
		index = check(GT[i])
		if index in splitGT:
			pos = GT[i].find("and")
			p1 = str(GT[i][0:pos - 1])
			p2 = str(GT[i][pos + 4:len(GT[i])])
			text.append("  tách GT '" + GT[i] + "' thành 2 phần '" + p1 + "' và '" + p2 + "'")
			GT.append(p1)
			GT.append(p2)
			del GT[i]
		else:
			i += 1
	i = 0
	while i < len(KL):
		index = check(KL[i])
		if index in splitKL:
			pos = KL[i].find("or")
			p1 = str(KL[i][0:pos - 1])
			p2 = str(KL[i][pos + 3:len(KL[i])])
			text.append("  tách KL '" + KL[i] + "' thành 2 phần '" + p1 + "' và '" + p2 + "'")
			KL.append(p1)
			KL.append(p2)
			del KL[i]
		else:
			i += 1
	text.append("--- Kết quả sau khi tách: ")
	text.append(merge(GT, KL))
	return (GT, KL, text)

def B4(GT, KL):
	splitKL = [3, 8, 9, 12, 15, 16, 18, 21, 22]
	splitGT = [4, 7, 10, 11, 13, 17, 19, 20, 23]
	temp = []
	temp.append([GT, KL])
	text = []
	text.append("Bước 4: tách ra các dòng nếu bên GT có or và bên KL có and")
	i = 0
	while i < len(temp):
		good = False
		for j in range(len(temp[i][0])):
			index = check(temp[i][0][j])
			if index in splitGT:
				pos = temp[i][0][j].find("or")
				p1 = [list(temp[i][0]), list(temp[i][1])]
				p2 = [list(temp[i][0]), list(temp[i][1])]
				p1[0][j] = str(p1[0][j][0:pos - 1])
				p2[0][j] = str(p2[0][j][pos + 3:len(p2[0][j])])
				temp.append(p1)
				temp.append(p2)
				del temp[i]
				good = True
				break
		if good: continue
		for j in range(len(temp[i][1])):
			index = check(temp[i][1][j])
			if index in splitKL:
				pos = temp[i][1][j].find("and")
				p1 = [list(temp[i][0]), list(temp[i][1])]
				p2 = [list(temp[i][0]), list(temp[i][1])]
				p1[1][j] = str(p1[1][j][0:pos - 1])
				p2[1][j] = str(p2[1][j][pos + 4:len(p2[1][j])])
				temp.append(p1)
				temp.append(p2)
				del temp[i]
				good = True
				break
		if good: continue
		i += 1
	GT = []
	KL = []
	for i in temp:
		text.append(merge(i[0], i[1]))
		GT.append(list(i[0]))
		KL.append(list(i[1]))
	return (GT, KL, text)

def B5(GT, KL):
	cnt = 0
	text = []
	text.append("Bước 5: kiểm tra tính đúng của các GT->KL")
	n = len(GT)
	for i in range(n):
		good = False
		for j in GT[i]:
			if j in KL[i]:
				good = True
				break
		if good: 
			text.append(merge(GT[i], KL[i]) + "   OK")
			cnt += 1
		else:
			text.append(merge(GT[i], KL[i]) + "   NOT OK")
	text.append("--- có " + str(cnt) + "/" + str(n) + " kết luận đúng")
	if cnt == n:
		text.append("--- Vậy mệnh đề được chứng minh")
	else:
		text.append("--- Vậy mệnh đè không được chứng minh")
	return (GT, KL, text)

def run(raw_GT, raw_KL):
	"running vuong hao algorithm"
	GT = raw_GT.split(",")
	KL = raw_KL.split(",")
	answer = []
	GT, KL, text = B0(GT, KL)
	answer.append(text)
	for i in answer[0]: print(i)
	GT, KL, text = B1(GT, KL)
	answer.append(text)
	for i in answer[1]: print(i)
	GT, KL, text = B2(GT, KL)
	answer.append(text)
	for i in answer[2]: print(i)
	GT, KL, text = B3(GT, KL)
	answer.append(text)
	for i in answer[3]: print(i)
	GT, KL, text = B4(GT, KL)
	answer.append(text)
	for i in answer[4]: print(i)
	GT, KL, text = B5(GT, KL)
	answer.append(text)
	for i in answer[5]: print(i)
	return answer

if __name__ == "__main__":
	run("p Or q   ,    NoT   (   r and   s) ,not(g), not (  p)", "p Or q    , p OR r, g, s")