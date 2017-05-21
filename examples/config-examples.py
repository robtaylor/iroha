#! /usr/bin/python

# Run this to generate Makefile, then run 'make'
EXAMPLES = {
    'minimum' : {'minimum'},
    'copy' : {'copy'},
    'loop' : {'loop', 'example_common'},
    'xorshift' : {'xorshift', 'example_common'},
}
EXAMPLE_OBJS = ['example_common', 'copy', 'loop',
                'minimum', 'xorshift']
OUTPUT = 'Makefile'

ofh = open(OUTPUT, 'w')

ofh.write('# Generated by config-examples.py\n\n')

ofh.write('all\t: ' + ' '.join(EXAMPLES) + '\n\n')

ofh.write('clean\t:\n')
ofh.write('\trm -f *.o\n')
ofh.write('\trm -f ' + ' '.join(EXAMPLES) + '\n')

for e in EXAMPLE_OBJS:
    ofh.write(e + '.o\t: ' + e + '.cpp\n')
    ofh.write('\tg++ -std=c++11 -Wall -g -I../src -c ' + e + '.cpp\n\n')

for k, v in EXAMPLES.iteritems():
    objs = []
    for o in v:
        objs.append(o + '.o')
    obj_lst = ' '.join(objs)
    ofh.write(k + '\t: ../src/out/Default/obj.target/src/libiroha.a ' + obj_lst + '\n')
    ofh.write('\tg++ -o ' + k + ' ' + obj_lst + ' -L../src/out/Default/obj.target/src/ -liroha -lverilog_writer -lnumeric -liroha\n')

print('Generated Makefile. Please run \'make\'')
