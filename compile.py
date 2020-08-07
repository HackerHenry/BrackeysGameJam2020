#!/usr/bin/python3
import os
import time
os.system("g++ -c main.cpp -Wall")
print("[!] compiled")
os.system("g++ -o main main.o -lsfml-system -lsfml-audio -lsfml-window -lsfml-graphics -Wall")
print("[!] linked")
print("[!] run\n\n")
tm=time.time()
os.system("./main")
print("Sec: "+str(time.time()-tm))
