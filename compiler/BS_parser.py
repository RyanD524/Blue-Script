import BS_opcode
import os

cgen_Guide = { 
	"NULL"       : [0],
	"SAVE_VAR"   : [1],
	"CALL_FUNC"  : [2,3,7],
	"LOGIC_START": [4],
	"LOGIC_END"  : [5],
	"JUMP_TO"    : [11],
	"RETURN_VAL" : [9],
	"ARRAY"      : [6],
	"INCLUDE_EXT": [10]

}
class codeGen:
	def __init__(self, tokens, out):
		self.tokens = tokens
		self.endLines = []
		self.cmd_id = 0

		self.out = out.replace(".blue" if out.endswith('.blue') else ".blu", ".blc")

	def CodeWrite(self):
		with open(self.out, "w+") as BCS_Writer:
			for item in self.endLines:
				if item.startswith("INCLUDE_EXT"):
					continue
				BCS_Writer.write(f'{item}\n')

	def genCode(self):
		for ns in self.tokens.keys():
			currentNS = self.tokens[ns]
			#self.cmd_id = 0
			self.endLines.append(f"NAMESPACE-{ns}")

			for line in currentNS:
				  
				cmd = line['cmd']

				for key in cgen_Guide.keys():
					if cmd in cgen_Guide[key]:
						cmd = key

				self.endLines.append(f"{cmd}:{line['cmd']}~args:{line['args']}~nest:{line['nested']}")


		self.CodeWrite()


			
		


class Tokenizer: ## deals with parsing and tokenizing passed to BS_opcode

	def __init__(self,line, out):
		self.lines = line
		self.out = out
		self.tokens = {}

	def passTokens(self, tmpLines):
		CG = codeGen(tmpLines, self.out)
		CG.genCode()

	def makeTokens(self):
		tmpLines = {}
		for i in self.lines.keys():
			tmpList = self.lines[i]['lines']

			for line in tmpList:
				#lineDict = {}
				BSOP = BS_opcode.BS_opcode(line, tmpList.index(line), i)
				opCmd = BSOP.getOpCode()

				tmpList[tmpList.index(line)] = opCmd

			tmpLines[i] = tmpList

		self.passTokens(tmpLines)