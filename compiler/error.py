
class Error:
	def __init__(self, error_name, details):
		self.error_name = error_name
		self.details = details

	def as_string(self):
		raise  Exception(f'{self.error_name}: {self.details}')

class IllegalCharError(Error):
	def __init__(self, details):
		super().__init__("Illegal Character", details)

class fileNotfound(Error):
	def __init__(self,details):
		super().__init__("File not found", details)

