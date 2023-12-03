import os

print('bulding project...')

if(os.path.exists(os.getcwd() + '/../build')):
    os.chdir('../build')
else:
    os.chdir('../')
    os.system('mkdir build')
    os.chdir('build')

os.system('g++ -std=c++11 ../src/io/IO.cpp ../src/huffman/Huffman.cpp ../src/huffman/HuffmanTree.cpp ../src/jabberwocky/JabberWocky.cpp ../src/main.cpp -o main')
print('build complete')