filename_c = "graph.c"

file = open(filename_c, 'r')
text = file.read()
file.close()

import re
r = re.compile(r"[a-z, A-Z]")

lines_all = text.split("\n")
lines = []
for line in lines_all:
	if len(line)>0 and r.search(line[0]) and line[:8] != "int main":
		if line[-2:] == " {":
			line = line[:-2] + ";"
		lines.append(line)

filename_h = filename_c[:-2] + ".h"
file = open(filename_h, 'wb')
filename_h = filename_h.upper()
file.write("#ifndef " + filename_h[:-2] + "_H\r\n")
file.write("#define " + filename_h[:-2] + "_H\r\n")
for line in lines:
	file.write(line + "\r\n")
file.write("#endif")

print "done!"