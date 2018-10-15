import sys

def new_bst_type(content_type, label):
	with open('templates/bst_base.c', 'r') as f:
		f_data = f.read()
	f_data = f_data.replace('<<LABEL>>', label).replace('<<TYPE>>', content_type)
	h_data, _, c_data = f_data.partition('// <<SPLIT>> //');
	with open('source/' + label + '_bst.h', 'w') as h_new:
		h_new.write(h_data);
	with open('source/' + label + '_bst.c', 'w') as c_new:
		c_new.write(c_data)

if __name__ == "__main__":
	assert(len(sys.argv)==3)
	content_type, label = sys.argv[1:3]
	new_bst_type(content_type, label)