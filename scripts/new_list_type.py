import sys

def new_list_type(content_type, label):
	for ext in ['.c', '.h']:
		with open('templates/list_base' + ext, 'r') as f:
			f_data = f.read()
		f_data = f_data.replace('<<LABEL>>', label).replace('<<TYPE>>', content_type)
		with open(label + '_list' + ext, 'w') as f_new:
			f_new.write(f_data)

if __name__ == "__main__":
	assert(len(sys.argv)==3)
	content_type, label = sys.argv[1:3]
	new_list_type(content_type, label)