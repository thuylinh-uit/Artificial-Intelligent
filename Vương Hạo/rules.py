import string
# list of rules:
#1	a
#2	not(a)
#3	a and b
#4	a or b
#5	not(a and b)
#6	not(a or b)
#7	not(a) or not(b)
#8	not(a) and not(b)
#9	not(a) and b
#10	not(a) or b
#11	a or not(b)
#12	a and not(b)
#13	a or a
#14	a or not(a) <none>
#15	a and a
#16	a and (a not b)
#17	a or (a and b)
#18	a and (not(a) or b)
#19	a or (not(a) and b)
#20	a or (b and c)
#21	(a or b) and (a or c)
#22	a and (a or b)
#23	(a and b) or (a and c)

global rule
rule = {
	"a": 1,
	"not(a)": 2,
	"a and b": 3,
	"a or b": 4,
	"not(a and b)": 5,
	"not(a or b)": 6,
	"not(a) or not(b)": 7,
	"not(a) and not(b)": 8,
	"not(a) and b": 9,
	"not(a) or b": 10,
	"a or not(b)": 11,
	"a and not(b)": 12,
	"a or a": 13,
	"a or not(a)": 14,
	"a and a": 15,
	"a and (a not b)": 16,
	"a or (a and b)": 17,
	"a and (not(a) or b)": 18,
	"a or (not(a) and b)": 19,
	"a or (b and c)": 20,
	"(a or b) and (a or c)": 21,
	"a and (a or b)": 22,
	"(a and b) or (a and c)": 23,
}

inv_rule = {
	1: "a",
	2: "not(a)",
	3: "a and b",
	4: "a or b",
	5: "not(a and b)",
	6: "not(a or b)",
	7: "not(a) or not(b)",
	8: "not(a) and not(b)",
	9: "not(a) and b",
	10: "not(a) or b",
	11: "a or not(b)",
	12: "a and not(b)",
	13: "a or a",
	14: "a or not(a)", 
	15: "a and a",
	16: "a and (a not b)",
	17: "a or (a and b)",
	18: "a and (not(a) or b)",
	19: "a or (not(a) and b)",
	20: "a or (b and c)",
	21: "(a or b) and (a or c)",
	22: "a and (a or b)",
	23: "(a and b) or (a and c)",
}

clause = {
	1:"a",
	2:"b",
	3:"c",
	4:"d",
	5:"e",
	6:"f",
	7:"g",
	8:"h",
	9:"i",
	10:"j",
	11:"k",
	12:"l",
	13:"m",
	14:"n",
	15:"o",
	16:"p",
	17:"q",
	18:"s",
	19:"r",
	20:"s",
	21:"t",
	22:"v",
	23:"x",
	24:"y",
	25:"z",
	26:"w",

}

def convert(raw_data):
	data = str(raw_data) 
	while data.find("and") != -1: data = data.replace("and", "!", 1)
	while data.find("or") != -1: data = data.replace("or", "@", 1)
	while data.find("not") != -1: data = data.replace("not", "#", 1)
	foo = 1
	change = dict()
	for i in range(len(data)):
		if data[i] in string.ascii_lowercase:
			if data[i] not in change:
				change[data[i]] = clause[foo]
				foo += 1
			data = data[0:i] + change[data[i]] + data[i + 1:len(data)]
	while data.find("!") != -1: data = data.replace("!", "and", 1)
	while data.find("@") != -1: data = data.replace("@", "or", 1)
	while data.find("#") != -1: data = data.replace("#", "not", 1)
	return data

def check(raw_data):
	"return index ..."
	data = convert(raw_data)
	if data in rule:
		return rule[data]
	return -1

def standardized(raw_data):
	data = raw_data.lower().strip()
	for i in [("  ", " "), ("( ", "("), (" )", ")"), ("not (", "not(")]:
		while data.find(i[0]) != -1: data = data.replace(i[0], i[1], 1)
	return data

def change(raw_data, index_from, index_to):
	print(check(raw_data), raw_data)
	if check(raw_data) == index_from:
		change = dict()
		temp_data = raw_data
		while temp_data.find("and") != -1: temp_data = temp_data.replace("and", "!", 1)
		while temp_data.find("or") != -1: temp_data = temp_data.replace("or", "@", 1)
		while temp_data.find("not") != -1: temp_data = temp_data.replace("not", "#", 1)
		foo = 1
		for i in range(len(temp_data)):
			if temp_data[i] in string.ascii_lowercase:
				if temp_data[i] not in change:
					change[clause[foo]] = temp_data[i]
					foo += 1

		data = inv_rule[index_to]
		while data.find("and") != -1: data = data.replace("and", "!", 1)
		while data.find("or") != -1: data = data.replace("or", "@", 1)
		while data.find("not") != -1: data = data.replace("not", "#", 1)

		for i in range(len(data)):
			if data[i] in string.ascii_lowercase:
				data = data[0:i] + change[data[i]] + data[i + 1:len(data)]

		while data.find("!") != -1: data = data.replace("!", "and", 1)
		while data.find("@") != -1: data = data.replace("@", "or", 1)
		while data.find("#") != -1: data = data.replace("#", "not", 1)
		return data
	return "fail"



if __name__ == "__main__":
	print(standardized("not(a  and B)"))
	print(check("not(a and b)"))
	print(change(standardized("(a and b) or (a and c)"), 23, 22))

