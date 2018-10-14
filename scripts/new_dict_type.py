import sys

def new_dict_type(content_type, label):
	with open('templates/dict_base.c', 'r') as f:
		f_data = f.read()
	f_data = f_data.replace('<<LABEL>>', label).replace('<<TYPE>>', content_type)
	h_data, _, c_data = f_data.partition('// <<SPLIT>> //');
	with open(label + '_dict.h', 'w') as h_new:
		h_new.write(h_data);
	with open(label + '_dict.c', 'w') as c_new:
		c_new.write(c_data)

if __name__ == "__main__":
	assert(len(sys.argv)==3)
	content_type, label = sys.argv[1:3]
	new_dict_type(content_type, label)

# to use scripts, call python scripts/new_dict_type.py LABEL TYPE from the
# cutils directory