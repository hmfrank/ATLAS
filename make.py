#!/usr/bin/python3
#
# SYNOPSIS:
# ./make.py [executable]
#
# SUMMRAY:
# Run this script every time you wanna compile and run your C/C++ code,
# and it will: generate a makefile, run make and run your program.
# Adjust the constants below for your needs.
from multiprocessing import cpu_count
import os

# c compiler flags
CC = 'gcc'
CFLAGS = '-std=c99 -Wall -Wextra'
LDFLAGS = ''

# c++ compiler flags
XCC = 'g++'
XCFLAGS = '-std=c++11 ' + CFLAGS[9:]
XLDFLAGS = LDFLAGS

TARGETS = [
	# format: ('executable', [excluded files], (True for C++ False for C))
	('atlas', ['src/test.cpp'], False),
	('test', ['src/main.c'], True)
]

SRCDIR = 'src/'
OBJDIR = 'bin/'


def find_files():
	files = os.listdir(SRCDIR)
	files = [(SRCDIR + file, OBJDIR + replace_file_ext(file, '.o')) for file in files]

	return files


def get_extension(filename):
	return os.path.splitext(filename)[1]


def make_run(exe):
	if os.system('make -j {} {}'.format(cpu_count(), exe)) == 0:
		r = os.system('./' + exe)
		print('{} returned exit code {}.'.format(exe, r))


def replace_file_ext(filename, new_ext):
	return os.path.splitext(filename)[0] + new_ext


def write_clean(f):
	f.write('clean:\n\trm -r {}*'.format(OBJDIR))

	for exe, exclude, cpp in TARGETS:
		f.write(' ' + exe)

	f.write('\n\n')


def write_header(f):
	f.write('# this file was automatically generated\n\n')


def write_link(f, files):
	for exe, exclude, cpp in TARGETS:
		cc = XCC if cpp else CC
		cflags = XCFLAGS if cpp else CFLAGS
		ldflags = XLDFLAGS if cpp else LDFLAGS

		filtered = [(src, obj) for (src, obj) in files if src not in exclude]

		f.write(exe + ':')

		for src, obj in filtered:
			f.write(' ' + obj)

		f.write('\n\t{} {}'.format(cc, cflags))

		for src, obj in filtered:
			f.write(' ' + obj)

		f.write('{} -o {}\n\n'.format(ldflags, exe))


def write_rules(f, files):
	for src, obj in files:
		cpp = get_extension(src) == '.cpp'

		cc = XCC if cpp else CC
		cflags = XCFLAGS if cpp else CFLAGS

		command = '{} {} -MM {} -MT {}'.format(cc, cflags, src, obj)

		f.write(os.popen(command).read())
		f.write('\t')
		f.write('{} {} -c {} -o {}\n\n'.format(cc, cflags, src, obj))


def main():
	files = find_files()

	with open('Makefile', mode='w', encoding='ascii') as f:
		write_header(f)
		write_link(f, files)
		write_rules(f, files)
		write_clean(f)

	print('generated new makefile')

	if len(os.sys.argv) > 1:
		make_run(os.sys.argv[1])
	else:
		make_run(TARGETS[0][0])


if __name__ == '__main__':
	main()
