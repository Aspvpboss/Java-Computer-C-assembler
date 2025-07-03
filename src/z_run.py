import os
import subprocess



def normal_run():
    current_path = os.path.dirname(os.path.abspath(__file__))
    os.chdir(current_path)

    os.system("gcc main.c init.c tokenize.c parse.c arguments.c get_bytes.c generate.c -o compiled/assembler.exe -l regex")


    exe_path = os.path.join("compiled", "assembler.exe")
    subprocess.run(exe_path, cwd="compiled")


def build_assembly():
    current_path = os.path.dirname(os.path.abspath(__file__))
    os.chdir(current_path)

    os.system("gcc main.c init.c tokenize.c parse.c arguments.c get_bytes.c generate.c -o compiled/assembler.exe -lregex")
    os.system("objdump -d -M intel compiled/assembler.exe > compiled/disassembly.asm")








normal_run()
# build_assembly()