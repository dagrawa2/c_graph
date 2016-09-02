filename = "object.h"

file = open(filename, 'r')
text = file.read()
file.close()

lines = text.split("\n")
for i in range(len(lines)):
	if lines[i][0] != "#":
		lines[i] = "__declspec(dllexport) " + lines[i]

filename_dll = filename[:-2] + "_dll.h"
file = open(filename_dll, 'wb')
for line in lines[:-1]:
	file.write(line + "\r\n")
file.write(lines[-1])
file.close()

print "Done!"