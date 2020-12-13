import tokens
from memory import varkeys, namespaces

nums = '1234567890'
opers = ["+","-","**","/","*"]
logic_ops = ["==", ">=", "<=", "<", ">", "!="]
class BS_opcode:

	def __init__(self, code, lineNo, namespace):
		self.code = code
		self.lineno = lineNo
		self.n_space = namespace
		self.cmdText = self.code.split(" ",1) if " " in self.code else self.code

	
	def isNumber(self, item):
		dotCount = 0

		for char in list(item):
			if char == '.':
				dotCount += 1
				if dotCount > 1:
					return "2" ## A string
				continue

			if char not in nums:
				return "2" ## A string

		if dotCount == 0:
			return "1" ## is int

		elif dotCount == 1:
			return "0" ## is float

	def str2bool(self, v):
		return str(v).lower() in ('true', 'false')

	def strToHex(self, string):
		returnString = ""
		for i in string:
			returnString += hex(ord(i))

		return returnString.replace("0x", "")

	def getType(self, item):
		BS_return = ""
		BS_Type = ""
		BS_Len = ""
		is_set = False
		if item.startswith(" "):
			item = item[1:]
		if item.endswith(" "):
			item = item[:1]
			

		numReturn = self.isNumber(item)
		tmpLen = len(item)
		BS_name = self.strToHex(item)
		if len(str(tmpLen)) == 1:
			BS_Len = "0" + str(tmpLen)
		else:
			BS_Len = str(tmpLen)

		if numReturn != "2" :
			if numReturn == "1":
				BS_Type = "00"
				is_set = True
				#return((int(item), 0))
			elif numReturn == "0":
				BS_Type = "01"
				is_set = True
				#return ((float(item), 1))

		if item.startswith('"') and item.endswith('"'):
			item = item.replace('"', "")
			BS_Type = "02"
			is_set = True

		elif self.str2bool(item):
			BS_Type = "03"
			is_set = True

		elif self.OpCode == 1 or self.OpCode == 3 and is_set == False:
			varkeys.append(item)
			BS_Type = "04"
			is_set = True
		elif item in opers:
			BS_Type = "05"
			is_set = True
		elif item in varkeys:
			BS_Type = "04"
			is_set = True

		elif item in namespaces or item.endswith(".blf"):
			BS_Type = "06"
			is_set = True

		elif is_set == False:
			raise Exception("BS ERROR 0020 Incorrect Type declaration")

		returnString = f"{BS_Type}{BS_Len}{BS_name}"
		return returnString

	def incorrectSyntax(self):
		raise Exception(f"BS ERROR 0001 Incorrect Syntax -> Line {self.lineno} in namespace '{self.n_space}'")
	
	def getOpCode(self):
		nested = False
		logicMode = None
		fin = []
		if self.cmdText[0].startswith("\t"):
			nested = True
			self.cmdText[0] = self.cmdText[0].replace("\t","")

		self.OpCode = tokens.tokens.get(self.cmdText[0], "ip")#self.incorrectSyntax())
		
		if len(self.cmdText) >= 1:
			endStr = ""
			argSpec = []
			fin = []
			self.args = self.cmdText[1]

			if self.OpCode != 4:
				if '=' in self.args:
					argSpec = self.args.split("=") 
					ops = [e for e in opers if e in argSpec[1]]
					
					if len(ops) != 0:
						tmp = argSpec[1].split(ops[0])
						argSpec.remove(argSpec[1])
						argSpec += tmp

					endStr = "0501"
					evl = self.strToHex(ops[0])
					endStr = f"{endStr}{evl}{evl}"
					#math ops					
				else:
					argSpec.append(self.args)
			else:
				for item in logic_ops:
					if item in self.args:
						argSpec = self.args.split(item)
						logicMode = item
					tmp = self.strToHex(logicMode)
					endStr = "07"
					tmpLen = str(len(logicMode))
					if len(tmpLen) == 1:
						tmpLen = "0" + tmpLen
					endStr = f"{endStr}{tmpLen}{tmp}"
				## logic ops
			fin.append(endStr)


			for item in argSpec:
				arg = self.getType(item)
				fin.append(arg)
		else:
			fin.append("NULL")

		if len(fin[0]) == 0:
			del fin[0]
		tmpRemove = ["[", "]", " ", "'"]
		clean_fin = str(fin)

		for item in tmpRemove:
			clean_fin = clean_fin.replace(item, "")

		return {"cmd": self.OpCode, "args": clean_fin,"nested": nested, "argRange": len(fin) if fin[0] != "NULL" else None }



