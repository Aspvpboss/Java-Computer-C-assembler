import os
import subprocess



def normal_run():

    current_path = os.path.dirname(os.path.abspath(__file__))
    os.chdir(current_path)
    current_path = os.getcwd()


    os.system("gcc -O2 -Wall -Werror -Wpedantic src/*.c -o compiled/assembler.exe -Iinclude -lregex")

    os.chdir(os.path.join(current_path, "compiled"))

    subprocess.run(["assembler.exe"])



def build_assembly():
    current_path = os.path.dirname(os.path.abspath(__file__))
    os.chdir(current_path)

    os.system("gcc -O2 src/*.c -o compiled/assembler.exe -Iinclude -lregex")
    os.system("objdump -d -M intel compiled/assembler.exe > compiled/disassembly.asm")








normal_run()

# build_assembly()