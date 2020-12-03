import BS_parser
import error
import memory
import sys
import os

class BS_main:
	def __init__(self,mode,filename):
		self.mode = mode
		self.filename = filename

	def readLines(self):
		sendLines = {}
		def readFile(filename):
			if os.path.exists(filename):
				with open(filename, 'r') as BS_Reader:
					return BS_Reader.readlines()
			else:
				raise Exception(f"File '{filename}' not found")

		def partialParse(lines:list, namespace):
			i = 0
			if namespace not in memory.namespaces:
				memory.namespaces.append(namespace)
			while i != len(lines):

				if lines[i].endswith("\n"):
					lines[i] = lines[i].rstrip("\n")
					continue

				if lines[i].startswith("//") or lines[i] == '':
					lines.remove(lines[i])
					continue

				if lines[i].startswith("use"):
					## for preparsing external files
					tmp = lines[i].split(" ", 1)
					if tmp[1].endswith(".blf"):
						tmpName = tmp[1].replace(".blf", "")
						partialParse(readFile(tmp[1]),tmpName)
						#lines.remove(lines[i])
				i += 1

			sendLines[namespace] = {"lines" : lines, "length": len(lines)}

		partialParse(readFile(self.filename),"main")
		tokenClass = BS_parser.Tokenizer(sendLines, sys.argv[1])
		tokenClass.makeTokens()

	def execute(self):
		if mode == "FILE":
			self.readLines()

if __name__ == '__main__':
	mode = "FILE"
	file = "NONE"
	
	if sys.argv[1] != None and sys.argv[1].endswith(".blue") or sys.argv[1].endswith(".blu"):
		mode = "FILE"
		file = sys.argv[1]

	main = BS_main(mode,file)
	main.execute()
