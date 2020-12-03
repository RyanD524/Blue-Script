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

	def getType(self, item):
		if item.startswith(" "):
			item = item[1:]
		if item.endswith(" "):
			item = item[:1]
			

		numReturn = self.isNumber(item)

		if numReturn != "2":
			if numReturn == "1":
				return ((int(item), "int"))
			elif numReturn == "0":
				return ((float(item), "float"))

		if item.startswith('"') and item.endswith('"'):
			item = item.replace('"', "")
			return ((item,"string"))

		elif self.str2bool(item):
			return ((item, "bool"))

		elif self.OpCode == 1 or self.OpCode == 3:
			varkeys.append(item)
			return ((item, "var"))
		elif item in opers:
			return ((item, "oper"))
		elif item in varkeys:
			return ((item, "var"))

		elif item in namespaces or item.endswith(".blf"):
			return ((item, "func"))

		else:
			raise Exception("BS ERROR 0020 Incorrect Type declaration")

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
					fin.append(((ops[0], "math_op")))
				else:
					argSpec.append(self.args)
			else:
				for item in logic_ops:
					if item in self.args:
						argSpec = self.args.split(item)
						logicMode = item

				fin.append(((logicMode, "logicOp")))


			for item in argSpec:
				arg = self.getType(item)
				fin.append(arg)
		else:
			fin.append("NULL")

			
		return {"cmd": self.OpCode, "args": fin,"nested": nested, "argRange": len(fin) if fin[0] != "NULL" else None }



