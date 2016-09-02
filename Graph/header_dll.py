filename = "graph.h"

file = open(filename, 'r')
text = file.read()
file.close()

lines = text.split("\n")
lines_dll = []
lines_dll.append(lines[0][:-2] + "_DLL_H")
lines_dll.append(lines[1][:-2] + "_DLL_H")
for line in lines[2:]:
	if line[0:6] == "struct" and line[-1] == ";":
		lines_dll.append(line)
	elif line[0:7] == "typedef" and line[-1] == ";":
		lines_dll.append(line)
	elif line[0] in ["\t", "}", "#", "/"]:
		lines_dll.append(line)
	else:
		lines_dll.append("__declspec(dllexport) " + line)

filename_dll = filename[:-2] + "_dll.h"
file = open(filename_dll, 'wb')
for line in lines_dll[:-1]:
	file.write(line + "\r\n")
file.write(lines[-1])
file.close()

print "Done!"